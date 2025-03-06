#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "label.h"
#include "matrix.h"
#include <QHash>
#include <QPoint>
#include <QQueue>
#include <QSet>

struct SpineStats {
    QPoint sbp;
    double headWidth;
    double neckLength;
    double spineLength;
    double avgNeckWidth;
    double minNeckWidth;
    double maxNeckWidth;
    double area;
    int type;

    SpineStats(QPoint sbp, int hw, int nl, int sl, double anw, int mnw, int mxw, int a, int t)
        : sbp(sbp), headWidth(hw), neckLength(nl), spineLength(sl),
        avgNeckWidth(anw), minNeckWidth(mnw), maxNeckWidth(mxw), area(a), type(t) {}

    // Equality operator
    bool operator==(const SpineStats& other) const {
        return sbp == other.sbp &&
               headWidth == other.headWidth &&
               neckLength == other.neckLength &&
               spineLength == other.spineLength &&
               qFuzzyCompare(avgNeckWidth, other.avgNeckWidth) &&
               minNeckWidth == other.minNeckWidth &&
               maxNeckWidth == other.maxNeckWidth &&
               area == other.area &&
               type == other.type;
    }

    static double mean(const QVector<SpineStats>& stats, const std::function<double(const SpineStats&)>& getter) {
        double sum = 0.0;
        for (const auto& s : stats) {
            sum += getter(s);
        }
        return sum / stats.size();
    }

    static double stddev(const QVector<SpineStats>& stats, const std::function<double(const SpineStats&)>& getter) {
        double m = mean(stats, getter);
        double variance = 0.0;
        for (const auto& s : stats) {
            double diff = getter(s) - m;
            variance += diff * diff;
        }
        return std::sqrt(variance / stats.size());
    }

    QString toString() const {
        return QString("SBP: (%1, %2)\n"
                       "Head Width: %3\n"
                       "Neck Length: %4\n"
                       "Spine Length: %5\n"
                       "Avg Neck Width: %6\n"
                       "Min Neck Width: %7\n"
                       "Max Neck Width: %8\n"
                       "Area: %9\n"
                       "Type: %10")
            .arg(sbp.x()).arg(sbp.y())
            .arg(headWidth, 0, 'f', 2)
            .arg(neckLength, 0, 'f', 2)
            .arg(spineLength, 0, 'f', 2)
            .arg(avgNeckWidth, 0, 'f', 2)
            .arg(minNeckWidth, 0, 'f', 2)
            .arg(maxNeckWidth, 0, 'f', 2)
            .arg(area, 0, 'f', 2)
            .arg(type);
    }
};

template<typename T>
class Analyse{
    QHash<QPoint,QPoint> sbp_to_chp,sbp_to_hnj;
    QHash<QPoint,QVector<QPoint>> sbp_to_reachableSkelPointsFromSBP;
    QHash<QPoint,Matrix<T>> sbp_SpineMassDT;
    QHash<QPoint,QSet<QPoint>> mapping;
    QHash<QPoint,QVector<QPoint>> pathSBPtoHNJ;
    QSet<QPoint> filoSbp;
    Matrix<T> completeDT;

    QHash<QPoint,int> sbp_to_keyVal;
    /////////////////////////
    QSet<QPoint> sbpPoints;
public:
    Analyse(const QHash<QPoint,QPoint> &sbp_to_chp_,
            const QHash<QPoint,QPoint> &sbp_to_hnj_,
            const QHash<QPoint,QVector<QPoint>> &sbp_to_reachableSkelPointsFromSBP_,
            const QHash<QPoint,Matrix<T>> &sbp_SpineMassDT_,
            const QHash<QPoint,QSet<QPoint>> &mapping_,
            const QSet<QPoint> &filoSbp_,
            const Matrix<T> dt):
        sbp_to_chp(sbp_to_chp_),
        sbp_to_hnj(sbp_to_hnj_),
        sbp_to_reachableSkelPointsFromSBP(sbp_to_reachableSkelPointsFromSBP_),
        sbp_SpineMassDT(sbp_SpineMassDT_),
        mapping(mapping_),
        filoSbp(filoSbp_),
        completeDT(dt){

        for(auto it=sbp_to_chp_.begin();it!=sbp_to_chp_.end();it++){
            sbpPoints.insert(it.key());

            pathSBPtoHNJ[it.key()]=findPathfromSBPtoHNJ(it.key(),sbp_to_hnj_[it.key()]);

        }

    }
    QVector<SpineStats> analyse() {
        int count=0;
        for (const auto& sbp : sbpPoints) {
            double headWidth = 0,neckLength = 0,spineLength = 0;
            double avgNeckWidth = 0;
            int minNeckWidth = 0,maxNeckWidth = 0,area = 0,type = 0;
            if(!filoSbp.contains(sbp)){
                headWidth = findHeadWidth(sbp);
                neckLength = findNeckLength(sbp);
                spineLength = findSpineLength(sbp);
                avgNeckWidth = findAvgNeckWidth(sbp);
                minNeckWidth = findMinNeckWidth(sbp);
                maxNeckWidth = findMaxNeckWidth(sbp);
            }
            else{
                spineLength =findFilopodiaLength(sbp);
            }
            area = findArea(sbp);
            type = findLabel(sbp);
            SpineStats record(sbp, headWidth, neckLength, spineLength, avgNeckWidth, minNeckWidth, maxNeckWidth, area, type);
            note<<record.toString();
            table.emplace_back(record);
            sbp_to_keyVal[sbp]=count;
            count++;

        }
        return table;
    }
    Matrix<T> getKeys(int r,int c){
        Matrix<T> keys(r,c,0);
        for(auto it=mapping.begin();it!=mapping.end();it++)
        {
            QPoint sbp=it.key();
            auto points=it.value();
            foreach (auto pt, points) {
                keys.at(pt.x(),pt.y()).setValue(sbp_to_keyVal[sbp]);
            }
        }
        return keys;
    }


private:

    QVector<SpineStats> table;
    double findFilopodiaLength(QPoint sbp){
        return findFarthestPointfrom(sbp).length();
    }
    QVector<QPoint> findFarthestPointfrom(QPoint sbp) {
        QVector<QPoint> pointsReachableFromSBP = sbp_to_reachableSkelPointsFromSBP[sbp];
        QQueue<QPoint> q;
        QHash<QPoint, int> pathCost;
        QSet<QPoint> visited;

        // Initialize starting point
        q.enqueue(sbp);
        pathCost[sbp] = 0;
        visited.insert(sbp);

        QPoint farthestPoint = sbp;
        int maxPathCost = 0;

        while (!q.isEmpty()) {
            QPoint curr = q.dequeue();

            // Explore neighbors
            QVector<QPoint> neighbors = getNeighbors(curr);
            for (const QPoint& neighbor : neighbors) {
                // Check if the neighbor is in reachable points and not visited
                if (pointsReachableFromSBP.contains(neighbor) && !visited.contains(neighbor)) {
                    // Compute path cost (increment by 1 for each step)
                    int newPathCost = pathCost[curr] + 1;

                    q.enqueue(neighbor);
                    visited.insert(neighbor);
                    pathCost[neighbor] = newPathCost;

                    // Update farthest point if current path cost is greater
                    if (newPathCost > maxPathCost) {
                        maxPathCost = newPathCost;
                        farthestPoint = neighbor;
                    }
                }
            }
        }

        // Reconstruct the path from sbp to the farthest point
        QVector<QPoint> path;
        QPoint current = farthestPoint;
        while (current != sbp) {
            path.prepend(current);
            // Find the predecessor with the lowest path cost
            QVector<QPoint> predecessors = getNeighbors(current);
            QPoint predecessor = current;
            for (const QPoint& pred : predecessors) {
                if (pointsReachableFromSBP.contains(pred) &&
                    pathCost.contains(pred) &&
                    pathCost[pred] == pathCost[current] - 1) {
                    predecessor = pred;
                    break;
                }
            }
            current = predecessor;
        }
        path.prepend(sbp);

        return path;
    }
    double findArea(QPoint sbp) {
        // Implement findArea logic
        return mapping[sbp].size();
    }

    int findLabel(QPoint sbp) {
        if (filoSbp.contains(sbp)) {
            return __filopodium__;
        } else if (findNeckLength(sbp) == 0) {
            return __stubby__;
        } else {
            return __mushroom__;
        }
    }
    double findHeadWidth(QPoint sbp){
        QPoint chp=sbp_to_chp[sbp];
        note<<"SBP= "<<sbp<<"CHP= "<<chp;
        Matrix<T> dt= completeDT;
        return static_cast<double>(dt.at(chp.x()/*-xLow+3*/,chp.y()/*-yLow+3*/).getValue()*2.0/3.0);
    }

    double findNeckLength(QPoint sbp){
        QVector<QPoint> path=pathSBPtoHNJ[sbp];
        return path.length();
    }

    double findMinNeckWidth(QPoint sbp){
        QVector<QPoint> path=pathSBPtoHNJ[sbp];
        Matrix<T> dt=completeDT;
        T minDt=1;
        foreach (auto e, path) {
            minDt=std::min(minDt,dt.at(e.x()/*-xLow+3*/,e.y()/*-yLow+3*/).getValue());
        }
        return (minDt/3.0);
    }
    double findMaxNeckWidth(QPoint sbp){
        QVector<QPoint> path=pathSBPtoHNJ[sbp];
        Matrix<T> dt=completeDT;
        T maxDt=0;
        foreach (auto e, path) {
            maxDt=std::max(maxDt,dt.at(e.x()/*-xLow+3*/,e.y()/*-yLow+3*/).getValue());
        }
        return (maxDt/3.0);
    }
    double findAvgNeckWidth(QPoint sbp){
        QVector<QPoint> path=pathSBPtoHNJ[sbp];
        if(path.length()==0)
            return 0;
        Matrix<T> dt=completeDT;
        double avgDt=0;
        foreach (auto e, path) {
            avgDt+=std::max(0,dt.at(e.x()/*-xLow+3*/,e.y()/*-yLow+3*/).getValue());
        }
        avgDt/=path.length();
        return (avgDt/3.0);
    }

    double findSpineLength(QPoint sbp){
        int necklength=findNeckLength(sbp),
            headWidth=findHeadWidth(sbp);
        return necklength+2*headWidth;
    }
    QVector<QPoint> findPathfromSBPtoHNJ(QPoint sbp, QPoint hnj){
        // If SBP and HNJ are the same point, return an empty path
        if (sbp == hnj) {
            return QVector<QPoint>();
        }

        QVector<QPoint> traceableArea = sbp_to_reachableSkelPointsFromSBP[sbp];

        // If HNJ is not in the traceable area, return an empty path
        if (!traceableArea.contains(hnj)) {
            return QVector<QPoint>();
        }

        // Use BFS to find the shortest path
        QHash<QPoint, QPoint> parent;
        QSet<QPoint> visited;
        QQueue<QPoint> queue;

        queue.enqueue(sbp);
        visited.insert(sbp);
        parent[sbp] = QPoint(-1, -1);  // Mark start point

        while (!queue.isEmpty()) {
            QPoint current = queue.dequeue();

            // If we've reached the HNJ, reconstruct and return the path
            if (current == hnj) {
                QVector<QPoint> path;
                while (current != QPoint(-1, -1)) {
                    path.prepend(current);
                    current = parent[current];
                }
                return path;
            }
            QVector<QPoint> neighbors=getNeighbors(current);
            // Explore neighboring points in the traceable area
            for (const QPoint& neighbor : neighbors) {
                // Check if the neighbor is adjacent to the current point and not visited
                if (!visited.contains(neighbor) && traceableArea.contains(neighbor)) {
                    queue.enqueue(neighbor);
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                }
            }
        }

        // No path found
        return QVector<QPoint>();
    }


    int get_xLow(const QSet<QPoint> &set){
        int xLow = std::numeric_limits<int>::max();
        for (const auto& e : set) {
            xLow = std::min(xLow, e.x());
        }
        return xLow;
    }

    int get_yLow(const QSet<QPoint> &set){
        int yLow = std::numeric_limits<int>::max();
        for (const auto& e : set) {
            yLow = std::min(yLow, e.y());
        }
        return yLow;
    }
    QVector<QPoint> getNeighbors(const QPoint& p) {
        return {
            QPoint(p.x()-1, p.y()), QPoint(p.x()+1, p.y()),
            QPoint(p.x(), p.y()-1), QPoint(p.x(), p.y()+1),
            QPoint(p.x()-1, p.y()-1), QPoint(p.x()+1, p.y()-1),
            QPoint(p.x()-1, p.y()+1), QPoint(p.x()+1, p.y()+1)
        };
    }

};

#endif // ANALYSIS_H
