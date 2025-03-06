#ifndef ADVANCEDSPINELABELLING_H
#define ADVANCEDSPINELABELLING_H
#include "collisionimpact.h"
#include "distancetransform.h"
#include "label.h"
#include "matrix.h"
#include "qimage.h"
#include "skeletoniserWrapper.h"
#include <cmath>
#include <QPoint>
#include <QQueue>
#include <QStack>
// #include <Eigen/Dense>
template<typename T>
class SpineLabel {
    Matrix<T> skel, dt, bin, image;
    int rows, cols;
    QHash<QPoint,QSet<QPoint>> mapping;
    QHash<QPoint,QPoint> sbp_to_chp;
public:
    Matrix<T> markingSBP,markingSpine;
    SpineLabel() :rows(0),cols(0){}
    SpineLabel(const Matrix<T> skel_,const Matrix<T> dt_,const Matrix<T> bin_,const Matrix<T> image_):
        skel(skel_),dt(dt_),bin(bin_),image(image_){
        rows=skel.getRows();
        cols=skel.getCols();
        markingSpine=markingSBP=skel;
    }
    void markSBP(double alpha) {
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                T val=skel.at(i,j).getValue();
                if(val==__jp__ || val ==__ddj__ || val == __de__) {
                    QPair<QVector<QPoint>,QVector<QPoint>> path=findMultipleSBP(i,j,alpha);
                    QVector<QPoint> sbpPts=path.first, dendriteInterior=path.second;
                    foreach (auto e, dendriteInterior) {
                        markingSBP.at(e.x(),e.y()).setValue(__spinebase__);
                    }
                    foreach (auto e, sbpPts) {
                        markingSBP.at(e.x(),e.y()).setValue(__sbp__);
                    }
                }
            }
        }
    }
    void markSpine(double beta=1){
        markingSpine=Matrix<T>(rows,cols,0);
        Matrix<T> temp=markingSpine;
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                T val=markingSBP.at(i,j).getValue();
                if(val == __sbp__){
                    // count++;
                    QPoint sbp=QPoint(i,j);
                    QVector<QPoint> spineSkel=getSpinePointsReachableFrom(sbp);
                    QSet<QPoint> set;
                    foreach (auto e, spineSkel) {
                        double radius = (dt.at(e.x(), e.y()).getValue() * beta) / 3.0;
                        drawFilledCircle(e, static_cast<int>(radius),set);
                    }
                    applyBinaryMask(set);
                    foreach (auto e, set) {
                        Neighborhood<T> nb=bin.getNeighborhood(e.x(),e.y());
                        std::bitset<8> nearBG=nb.getNeighborsBinary(0);
                        if(nearBG.any() && !nearBG.all())continue;
                        else
                            set.remove(e);
                    }
                    // Find all connected components
                    QHash<QPoint, QSet<QPoint>> components;
                    QSet<QPoint> visited;
                    int maxSize = 0;
                    QSet<QPoint> largestComponent;

                    // For each point in the set that hasn't been visited
                    foreach(auto point, set) {
                        if (!visited.contains(point)) {
                            // Start a new component
                            QSet<QPoint> currentComponent;
                            QQueue<QPoint> queue;
                            queue.enqueue(point);
                            visited.insert(point);
                            currentComponent.insert(point);

                            // BFS to find all connected points
                            while (!queue.isEmpty()) {
                                QPoint current = queue.dequeue();

                                // Check all 8 neighbors
                                QVector<QPoint> neighbors = getNeighbors(current);
                                foreach(auto neighbor, neighbors) {
                                    if (set.contains(neighbor) && !visited.contains(neighbor)) {
                                        queue.enqueue(neighbor);
                                        visited.insert(neighbor);
                                        currentComponent.insert(neighbor);
                                    }
                                }
                            }

                            // Update largest component if current one is bigger
                            if (currentComponent.size() > maxSize) {
                                maxSize = currentComponent.size();
                                largestComponent = currentComponent;
                            }
                        }
                    }

                    // Replace set with only the largest component
                    set = largestComponent;
                    foreach (auto e, set) {
                        markingSpine.at(e.x(),e.y()).setValue(__dendrite__);
                    }
                    // // foreach (auto pt, set) {
                    // //     temp.at(pt.x(),pt.y()).setValue(__dendrite__);
                    // // }
                    // // foreach (auto e, set) {
                    // //     Neighborhood<T> nb=temp.getNeighborhood(e.x(),e.y());
                    // //     std::bitset<8> insidePt=nb.getNeighborsBinary(__dendrite__);
                    // //     Neighborhood<T> nb1=bin.getNeighborhood(e.x(),e.y());
                    // //     std::bitset<8> nearBG=nb1.getNeighborsBinaryNot(0);
                    // //     if(nearBG.all() && insidePt.all())
                    // //         set.remove(e);
                    // // }
                    // // foreach (auto e, set) {
                    // //     markingSpine.at(e.x(),e.y()).setValue(__dendrite__);
                    // // }
                    // QSet<QPoint> endPts;
                    // //FIND END PTS OF THE FRAGMENTS PRESENT IN SET

                    set.insert(QPoint(i,j));
                    QSet<QPoint> convexhull=grahamScan(set);
                    applyBinaryMask(convexhull);
                    mapping[QPoint(i,j)]=convexhull;
                    foreach (auto e, convexhull) {
                        Neighborhood<T> nb=bin.getNeighborhood(e.x(),e.y());
                        std::bitset<8> nearBG=nb.getNeighborsBinary(0);
                        if(nearBG.any())
                            markingSpine.at(e.x(),e.y()).setValue(__spineboundary__);
                        else {
                            markingSpine.at(e.x(),e.y()).setValue(__spine__);
                        }
                    }
                }
            }
        }

    }

    QHash<QPoint, QSet<QPoint> > getMapping() const
    {
        return mapping;
    }

private:
    QSet<QPoint> grahamScan(const QSet<QPoint>& set) {
        // Handle trivial cases
        if (set.size() <= 3) {
            return set;
        }

        // Find the point with the lowest y-coordinate (and leftmost if tied)
        QPoint pivot = *std::min_element(set.begin(), set.end(),
                                         [](const QPoint& a, const QPoint& b) {
                                             if (a.y() == b.y()) return a.x() < b.x();
                                             return a.y() < b.y();
                                         });

        // Sort points based on polar angle from pivot
        QVector<QPoint> sortedPoints(set.begin(), set.end());
        std::sort(sortedPoints.begin(), sortedPoints.end(),
                  [&pivot](const QPoint& a, const QPoint& b) {
                      // Compute cross product to determine angle
                      int crossProduct = (a.x() - pivot.x()) * (b.y() - pivot.y()) -
                                         (a.y() - pivot.y()) * (b.x() - pivot.x());

                      if (crossProduct == 0) {
                          // If points are collinear, keep the point further from pivot
                          int distA = (a.x() - pivot.x()) * (a.x() - pivot.x()) +
                                      (a.y() - pivot.y()) * (a.y() - pivot.y());
                          int distB = (b.x() - pivot.x()) * (b.x() - pivot.x()) +
                                      (b.y() - pivot.y()) * (b.y() - pivot.y());
                          return distA > distB;
                      }

                      return crossProduct > 0;
                  });

        // Remove duplicate points
        sortedPoints.erase(std::unique(sortedPoints.begin(), sortedPoints.end()),
                           sortedPoints.end());

        // Stack to hold convex hull points
        QVector<QPoint> hull;
        hull.push_back(sortedPoints[0]);
        hull.push_back(sortedPoints[1]);

        // Process remaining points
        for (size_t i = 2; i < sortedPoints.size(); ++i) {
            while (hull.size() > 1) {
                QPoint top = hull.back();
                QPoint secondTop = hull[hull.size() - 2];

                // Compute cross product to determine turn direction
                int crossProduct = (top.x() - secondTop.x()) * (sortedPoints[i].y() - secondTop.y()) -
                                   (top.y() - secondTop.y()) * (sortedPoints[i].x() - secondTop.x());

                // Remove points that make a non-left turn
                if (crossProduct <= 0) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.push_back(sortedPoints[i]);
        }

        // Polygon filling using scanline algorithm
        QSet<QPoint> filledHull;

        // Find min and max y coordinates to limit scanline range
        int minY = std::numeric_limits<int>::max();
        int maxY = std::numeric_limits<int>::min();
        for (const auto& p : hull) {
            minY = std::min(minY, p.y());
            maxY = std::max(maxY, p.y());
        }

        // Scanline polygon filling
        for (int y = minY; y <= maxY; ++y) {
            QVector<int> intersections;

            // Find x-intersections of polygon edges with current scanline
            for (size_t i = 0; i < hull.size(); ++i) {
                QPoint p1 = hull[i];
                QPoint p2 = hull[(i + 1) % hull.size()];

                // Check if scanline intersects this edge
                if ((p1.y() <= y && p2.y() > y) || (p2.y() <= y && p1.y() > y)) {
                    // Compute x-coordinate of intersection
                    double x = p1.x() + (y - p1.y()) * 1.0 * (p2.x() - p1.x()) / (p2.y() - p1.y());
                    intersections.push_back(static_cast<int>(std::round(x)));
                }
            }

            // Sort intersections
            std::sort(intersections.begin(), intersections.end());

            // Fill between pairs of intersections
            for (size_t i = 0; i < intersections.size(); i += 2) {
                if (i + 1 < intersections.size()) {
                    for (int x = intersections[i]; x <= intersections[i+1]; ++x) {
                        QPoint point(x, y);
                        if (isValid(point)) {
                            filledHull.insert(point);
                        }
                    }
                }
            }
        }

        return filledHull;
    }
    void drawFilledCircle(const QPoint &center, int radius,QSet<QPoint>& filledPoints) {
        int x0 = center.x();
        int y0 = center.y();

        int x = 0;
        int y = radius;
        int decision = 1 - radius;
        fillHorizontalLine(x0, y0, -radius, radius,filledPoints); // Fill initial diameter line

        while (x <= y) {
            // Draw horizontal lines for each circle "row"
            if (decision <= 0) {
                decision += 2 * x + 3;
            } else {
                decision += 2 * (x - y) + 5;
                y--;
            }
            x++;

            // Fill horizontal spans for each octant
            fillHorizontalLine(x0, y0 + y, -x, x,filledPoints); // Top & Bottom
            fillHorizontalLine(x0, y0 - y, -x, x,filledPoints);
            fillHorizontalLine(x0, y0 + x, -y, y,filledPoints); // Left & Right
            fillHorizontalLine(x0, y0 - x, -y, y,filledPoints);
        }
    }
    void applyBinaryMask(QSet<QPoint> &set) {
        foreach (auto e, set) {
            if (bin.at(e.x(), e.y()).getValue() == 0) {
                set.remove(e);
            }
        }
    }
    void fillHorizontalLine(int cx, int cy, int xStart, int xEnd,QSet<QPoint> &filledPoints) {
        for (int dx = xStart; dx <= xEnd; ++dx) {
            int x = cx + dx;
            int y = cy;
            QPoint point(x, y);
            if(isValid(point) && !filledPoints.contains(point))
                filledPoints.insert(point);
        }
    }

    QVector<QPoint> getSpinePointsReachableFrom(const QPoint& sbp){
        QStack<QPoint> dfs;
        QSet<QPoint> visited;
        dfs.push(sbp);
        while(!dfs.empty()){
            QPoint currPoint=dfs.pop();
            if(visited.contains(currPoint))
                continue;
            visited.insert(currPoint);

            QVector<QPoint> neighbors=getNeighbors(currPoint);
            for (const QPoint& neighbor : neighbors) {
                if (isValid(neighbor) && !visited.contains(neighbor)) {
                    T val = markingSBP.at(neighbor.x(), neighbor.y()).getValue();
                    if (val == __spine__ || val == __ssj__ || val == __sse__ || val == __sbp__) {
                        dfs.push(neighbor);
                    }
                }
            }
        }

        return visited.values();
    }
    QPair<QVector<QPoint>,QVector<QPoint>> findMultipleSBP(int i, int j, double alpha) {
        QPoint jpPoint(i, j);

        int maxDistance = round(dt.at(i, j).getValue() * (alpha / 4));
        QQueue<QPair<QPoint, int>> bfs;
        QSet<QPoint> visited;
        QVector<QPoint> sbpPoints,spinebase;
        bfs.enqueue(qMakePair(jpPoint, maxDistance));
        QPair<QVector<QPoint>,QVector<QPoint>> map;
        while (!bfs.isEmpty()) {
            QPair<QPoint, int> current = bfs.dequeue();
            QPoint currPoint = current.first;
            int remainingDistance = current.second;

            if (visited.contains(currPoint))
                continue;
            visited.insert(currPoint);

            if(currPoint != jpPoint){
                spinebase.append(currPoint);
            }

            if (remainingDistance <= 0) {
                sbpPoints.append(currPoint);
                continue;
            }

            QVector<QPoint> neighbors = getNeighbors(currPoint);
            for (const QPoint& neighbor : neighbors) {
                if (isValid(neighbor) && !visited.contains(neighbor)) {
                    int val = skel.at(neighbor.x(), neighbor.y()).getValue();
                    if (val == __spine__ || val == __ssj__ || val == __sse__ || val == __sbp__ ) {
                        bfs.enqueue(qMakePair(neighbor, remainingDistance - 1));
                    }
                }
            }
        }
        map.first=sbpPoints;
        map.second=spinebase;
        return map;
    }

    QVector<QPoint> getNeighbors(const QPoint& p) {
        return {
            QPoint(p.x()-1, p.y()), QPoint(p.x()+1, p.y()),
            QPoint(p.x(), p.y()-1), QPoint(p.x(), p.y()+1),
            QPoint(p.x()-1, p.y()-1), QPoint(p.x()+1, p.y()-1),
            QPoint(p.x()-1, p.y()+1), QPoint(p.x()+1, p.y()+1)
        };
    }

    bool isValid(const QPoint& p) {
        return p.x() >= 1 && p.x() < rows-1 &&
               p.y() >= 1 && p.y() < cols-1;
    }

};



template<typename T>
class SpineMass{
    Matrix<T> image,markingSBP;
    int rows, cols;
    QHash<QPoint, QSet<QPoint>> mapping;
    QHash<QPoint,Matrix<T>> sbp_SpineMassDT,sbp_SpineImage;
    QHash<QPoint,Matrix<double>> sbp_SpineMassNDT;
    QHash<QPoint,QPoint> sbp_to_chp,sbp_to_hnj;
    QHash<QPoint,QVector<QPoint>> sbp_to_reachableSkelPointsFromSBP;
    QSet<QPoint> filoSBP;
    QHash<QPoint,QImage> sbp_image;
public:
    Matrix<T> markingCHP,markingHNJ;

    SpineMass() : rows(0), cols(0) {}
    SpineMass(const Matrix<T> image_,const Matrix<T> markingSBP_, const QHash<QPoint, QSet<QPoint>> mapping_) :
        image(image_),markingSBP(markingSBP_), mapping(mapping_) {
        rows = image.getRows();
        cols = image.getCols();
        markingCHP=markingSBP_;
    }
    void findCHP(double threshold=__invalid__){
        storeDT_forEachSpine();
        if(threshold!=__invalid__)
            filoSBP=segregateFilopodia(threshold);
        markingCHP=markingSBP;
        QVector<QPoint> sbpPts=mapping.keys();
        foreach (auto sbp, sbpPts) {
            if(!filoSBP.contains(sbp)){
                QSet<QPoint> spineMass=mapping[sbp];
                QPoint chp=findLocalMaximasAndCentroid(sbp,spineMass);
                QVector<QPoint> spineSkel=getSpinePointsReachableFrom(sbp);
                sbp_to_reachableSkelPointsFromSBP[sbp]=spineSkel;
                chp=findNearest(spineSkel,chp);
                markingCHP.at(chp.x(),chp.y()).setValue(__chp__);
                sbp_to_chp[sbp]=chp;
            }
            else {
                QSet<QPoint> spineMass=mapping[sbp];
                QPoint chp=findLocalMaximasAndCentroid(sbp,spineMass);
                foreach (auto e, spineMass) {
                    markingCHP.at(e.x(),e.y()).setValue(__filopodium__);
                }
                QVector<QPoint> spineSkel=getSpinePointsReachableFrom(sbp);
                sbp_to_reachableSkelPointsFromSBP[sbp]=spineSkel;
                chp=findNearest(spineSkel,chp);
                markingCHP.at(chp.x(),chp.y()).setValue(__chp__);
                sbp_to_chp[sbp]=chp;
            }
        }
    }
    void findHNJ(double gamma=1){
        markingHNJ=markingCHP;
        for(auto it=sbp_to_chp.begin();it!=sbp_to_chp.end();it++){
            QPoint sbp=it.key();
            if(filoSBP.contains(sbp))
                continue;
            QPoint chp=it.value();
            QVector<QPoint> spineSkel=sbp_to_reachableSkelPointsFromSBP[sbp];
            QSet<QPoint> spineMass=mapping[sbp];
            int xLow=get_xLow(spineMass);
            int yLow=get_yLow(spineMass);
            // Calculate radius of the circle
            T radius = (sbp_SpineMassDT[sbp].at(chp.x()-xLow+3, chp.y()-yLow+3).getValue() * gamma) / 3.0;

            // Store potential HNJ points
            QVector<QPoint> hnjCandidates;

            // Draw a circle centered at the CHP and find intersections with spine skeleton
            for (const QPoint& skelPoint : spineSkel) {
                // Check if the point is within the circle centered at CHP
                int dx = skelPoint.x() - chp.x();
                int dy = skelPoint.y() - chp.y();
                double distance = std::sqrt(dx * dx + dy * dy);

                if (std::abs(distance - radius) <= 1.0) {  // Allow for pixel-level approximation
                    hnjCandidates.append(skelPoint);
                }
            }

            // If no candidates found, skip this iteration
            if (hnjCandidates.isEmpty()) {
                continue;
            }

            // Find the HNJ point closest to the SBP
            QPoint hnj = *std::min_element(hnjCandidates.begin(), hnjCandidates.end(),
                                           [&sbp](const QPoint& a, const QPoint& b) {
                                               int distA = std::abs(a.x() - sbp.x()) + std::abs(a.y() - sbp.y());
                                               int distB = std::abs(b.x() - sbp.x()) + std::abs(b.y() - sbp.y());
                                               return distA < distB;
                                           });

            // Mark the HNJ point
            markingHNJ.at(hnj.x(), hnj.y()).setValue(__hnj__);
            sbp_to_hnj[sbp]=hnj;
        }
    }

    QHash<QPoint, QPoint> getSbp_to_chp() const
    {
        return sbp_to_chp;
    }

    QHash<QPoint, QPoint> getSbp_to_hnj() const
    {
        return sbp_to_hnj;
    }

    QHash<QPoint, QVector<QPoint> > getSbp_to_reachableSkelPointsFromSBP() const
    {
        return sbp_to_reachableSkelPointsFromSBP;
    }

    QSet<QPoint> getFiloSBP() const
    {
        return filoSBP;
    }

    QHash<QPoint, Matrix<T> > getSbp_SpineImage() const
    {
        return sbp_SpineImage;
    }

    QHash<QPoint, Matrix<T> > getSbp_SpineMassDT() const
    {
        return sbp_SpineMassDT;
    }

    QHash<QPoint, Matrix<double> > getSbp_SpineMassNDT() const
    {
        return sbp_SpineMassNDT;
    }

    QHash<QPoint, QImage> getSbp_image() const
    {
        return sbp_image;
    }

private:
    QPoint findNearest(const QVector<QPoint> &spineSkel, const QPoint &chp){
        QPoint nearest=spineSkel[0];
        int min=(nearest-chp).manhattanLength();
        foreach (auto pt, spineSkel) {
            if(pt==chp){
                nearest=pt;
                break;}
            int dist=(pt-chp).manhattanLength();
            if(dist<min)
            {
                nearest=pt;
                min=dist;
            }

        }
        return nearest;
    }
    Matrix<T> computeBoundingBox(const QSet<QPoint>& set) {
        if (set.isEmpty()) {
            return Matrix<T>(1, 1, 0); // Return a small empty matrix if set is empty
        }

        int xLow = std::numeric_limits<int>::max();
        int xHigh = std::numeric_limits<int>::min();
        int yLow = std::numeric_limits<int>::max();
        int yHigh = std::numeric_limits<int>::min();

        // Find the bounding box coordinates
        for (const auto& e : set) {
            xLow = std::min(xLow, e.x());
            xHigh = std::max(xHigh, e.x());
            yLow = std::min(yLow, e.y());
            yHigh = std::max(yHigh, e.y());
        }

        // Create bounding box with 1-pixel padding
        int boxRows = xHigh - xLow + 7;
        int boxCols = yHigh - yLow + 7;

        Matrix<T> box(boxRows, boxCols, 0);

        // Fill the box with points, translated to the new coordinate system
        for (const auto& e : set) {
            int newX = e.x() - xLow + 3;
            int newY = e.y() - yLow + 3;
            box.at(newX, newY).setValue(255);
        }

        return box;
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

    Matrix<T> computeDT(const QSet<QPoint> &set){
        // int xLow=get_xLow(set);
        // int yLow=get_yLow(set);

        return DistanceTransform<T>::compute(computeBoundingBox(set));
    }
    Matrix<T> computeDTEuclidean(const QSet<QPoint> &set){
        return DistanceTransform<T>::computeEuclidean(computeBoundingBox(set));
    }

    Matrix<T> computeImage(const QSet<QPoint> &set){
        Matrix<T> spineImage=computeBoundingBox(set);
        int xlow=get_xLow(set),ylow=get_yLow(set);
        foreach (auto e, set) {
            int i=e.x()-xlow+3;
            int j=e.y()-ylow+3;

            spineImage.at(i,j).setValue(image.at(e.x(),e.y()).getValue());
        }
        return spineImage;
    }

    void storeDT_forEachSpine(){
        // note<<"in storeDT_forEachSpine";
        for(auto it=mapping.begin();it!=mapping.end();it++){
            QPoint sbp=it.key();
            // note<<"SBP= "<<sbp;
            QSet spineMass=it.value();
            Matrix<T> dt=computeDT/*Euclidean*/(spineMass);
            Matrix<T> spineImage=computeImage(spineMass);

            // note<<"dt matrix size= "<<dt.getRows()<<"*"<<dt.getCols();
            sbp_SpineMassDT[sbp]=dt;
            sbp_SpineImage[sbp]=spineImage;
        }

        normaliseDT();
    }

    void normaliseDT() {
        for(auto it = mapping.begin(); it != mapping.end(); it++) {
            QPoint sbp = it.key();
            Matrix<T> dt = sbp_SpineMassDT[sbp];

            Matrix<double> NDT(dt.getRows(), dt.getCols(), 0);

            // Normalize to probability distribution
            int totalDirt = 0;
            for (int i = 0; i < NDT.getRows(); ++i) {
                for (int j = 0; j < NDT.getCols(); ++j) {
                    totalDirt += /*sqrt*/(dt.at(i,j).getValue());
                }
            }

            // First, normalize values
            for (int i = 0; i < NDT.getRows(); ++i) {
                for (int j = 0; j < NDT.getCols(); ++j) {
                    NDT.at(i,j).setValue(static_cast<double>(/*sqrt*/(dt.at(i,j).getValue()) * 1.0 / totalDirt));
                }
            }

            // Apply adaptive local blurring
            Matrix<double> blurredNDT=NDT;
            // double sigma=1.0/calculateSTD(NDT,mapping[sbp]);
            // note<<sigma;
            // blurredNDT=Denoising<double>::gaussianDenoise(NDT,5,sigma);
            // blurredNDT=Denoising<double>::medianDenoise(NDT,5);
            // blurredNDT=Denoising<double>::meanDenoise(blurredNDT,3);

            sbp_SpineMassNDT[sbp] = blurredNDT;
        }

        initialiseImage();
    }

    void initialiseImage(){
        for(auto it=sbp_SpineMassNDT.begin();it!=sbp_SpineMassNDT.end();it++){
            QPoint sbp=it.key();
            Matrix<double> map=it.value();
            // Create a QImage with the same dimensions as the matrix
            QImage img(map.getCols(), map.getRows(), QImage::Format_RGB32);
            img.fill(Qt::black);  // Start with a black background

            // Convert normalized distance transform to grayscale image
            for (int i = 0; i < map.getRows(); ++i) {
                for (int j = 0; j < map.getCols(); ++j) {
                    int grayValue = static_cast<int>(/*NMAP*/map.at(i,j).getValue() * /*255*/10000);
                    grayValue=grayValue>255?255:grayValue;
                    // note<<grayValue;
                    img.setPixel(j, i, qRgb(grayValue, grayValue, grayValue));
                }
            }
            // note<<"000000000000000";
            sbp_image[sbp] = img;
        }
    }

    QSet<QPoint> segregateFilopodia(double k) {
        QSet<QPoint> set;

        // Iterate through all spine base points in the mapping
        for (auto it = mapping.begin(); it != mapping.end(); ++it) {
            QSet<QPoint> spineMass = it.value();
            QPoint sbp = it.key();
            // Get distance transform for this spine base point
            auto neighborhood=sbp_SpineMassDT[sbp];
            // Find local maximas in the spine mass
            auto localMaximas = findLocalMaximas(sbp, spineMass);


            QImage& currentImage = sbp_image[it.key()];

            // Mark local maximas in the image as blue
            for (int i = 0; i < localMaximas.getRows(); ++i) {
                for (int j = 0; j < localMaximas.getCols(); ++j) {
                    if (localMaximas.at(i, j).getValue() != -1) {
                        currentImage.setPixel(j, i, qRgb(0, 0, 255));
                    }
                }
            }
            //CURRENT SPINE STAT COMPUTATION


            double sum = 0.0,sum_of_squares=0;
            int peakCount = 0;
            // note<<"++++++++++++";
            // Iterate through local maximas to calculate kurtosis
            for (int i = 0; i < localMaximas.getRows(); ++i) {
                for (int j = 0; j < localMaximas.getCols(); ++j) {
                    // Check if this is a local maximum
                    if (localMaximas.at(i, j).getValue() != -1) {
                        peakCount++;
                        // Default neighborhood size, could be parameterized
                        double baseArea= ceil(neighborhood.at(i,j).getValue()/3.0);
                        // note<<baseArea;
                        sum+=baseArea;
                        sum_of_squares+=baseArea*baseArea;
                    }
                }
            }
            double mean=sum/peakCount;
            double variance=sum_of_squares/peakCount-mean*mean;
            double std=sqrt(variance);
            // note<<"---";
            // note<<std;
            if(std<=k)
                set.insert(sbp);

        }

        return set;
    }
    double calculateMean(const Matrix<double>& dt, const QSet<QPoint>& pts) {
        double sum = 0.0;
        int count = 0;
        int xlow=get_xLow(pts);
        int ylow=get_yLow(pts);
        for (const QPoint& pt : pts) {
            sum += dt.at(pt.x()-xlow+3, pt.y()-ylow+3).getValue();
            count++;
        }

        return count > 0 ? sum / count : 0.0;
    }

    // Helper function to calculate standard deviation
    double calculateSTD(const Matrix<double>& dt, const QSet<QPoint>& pts) {
        double mean = calculateMean(dt, pts);
        double sumSquaredDiff = 0.0;
        int count = 0;
        int xlow=get_xLow(pts);
        int ylow=get_yLow(pts);
        for (const QPoint& pt : pts) {
            double diff = dt.at(pt.x()-xlow+3, pt.y()-ylow+3).getValue() - mean;
            sumSquaredDiff += diff * diff;
            count++;
        }

        return count > 0 ? std::sqrt(sumSquaredDiff / count) : 0.0;
    }


    Matrix<int> findLocalMaximas(const QPoint sbp, const QSet<QPoint>& pts) {
        const double EPSILON=1e-3;
        Matrix<int> currDT=sbp_SpineMassDT[sbp];
        Matrix<int> currCI(currDT.getRows(),currDT.getCols(),0);
        Matrix<int> currBin=computeBoundingBox(pts);
        CollisionImpact<int> computer(currDT,currBin);
        computer.computeCI(currCI);
        Skeletoniser<int> skel(currDT,currCI);
        Matrix<int> localMaximaMarker=skel.finalSkeletonization(skel.primarySkeletonization());
        Matrix<double> ndt=sbp_SpineMassNDT[sbp];
        QVector<QPair<QPoint, double>> sortedPixels;
        double totalVolume=0;
        QSet<QPoint> allMaximas;
        for (int i = 0; i < localMaximaMarker.getRows(); ++i) {
            for (int j = 0; j < localMaximaMarker.getCols(); ++j) {
                if(localMaximaMarker.at(i,j).getValue()==0)continue;
                else{
                    //these are local maximas
                    double currVal = static_cast<int>(ndt.at(i, j).getValue());
                    totalVolume+=currVal;
                    allMaximas.insert(QPoint(i,j));
                    sortedPixels.push_back(qMakePair(QPoint(i, j), currVal));
                }
            }
        }
        // Sort in ascending order of values
        std::sort(sortedPixels.begin(), sortedPixels.end(),
                  [](const QPair<QPoint, double>& a, const QPair<QPoint, double>& b) {
                      return a.second < b.second;
                  });

        // Accumulate volume and find pixels contributing to 50% of total volume
        double accumulatedVolume = 0;
        QSet<QPoint> lesserMaximas;
        for (const auto& pixel : sortedPixels) {
            lesserMaximas.insert(pixel.first);
            accumulatedVolume += pixel.second;
            // Stop when we've accumulated at least 20% of the total volume
            if (accumulatedVolume >= totalVolume * 0.2) {
                break;
            }
        }
        QSet<QPoint> majorMaximas=allMaximas.subtract(lesserMaximas);
        localMaximaMarker=Matrix<int>(localMaximaMarker.getRows(),localMaximaMarker.getCols(),-1);
        foreach (auto pt, majorMaximas) {
            localMaximaMarker.at(pt.x(),pt.y()).setValue(1);
        }
        return localMaximaMarker;
    }

    QPoint findLocalMaximasAndCentroid(const QPoint sbp, const QSet<QPoint>& pts) {
        // note << "CENTROID CALCULATION";
        Matrix<int> localMaximas = findLocalMaximas(sbp, pts);
        auto dt = sbp_SpineMassNDT[sbp];

        double sumWeights = 0.0;
        QPointF centroid(0.0, 0.0);

        for (int i = 0; i < localMaximas.getRows(); ++i) {
            for (int j = 0; j < localMaximas.getCols(); ++j) {
                if (localMaximas.at(i, j).getValue() != -1) {
                    double wt = dt.at(i, j).getValue();
                    sumWeights += wt;
                    centroid += QPointF(i, j) * wt;
                }
            }
        }

        // Prevent division by zero
        if (sumWeights > 0) {
            centroid /= sumWeights;
        }

        // note << "____" << centroid;

        int xLow = get_xLow(pts);
        int yLow = get_yLow(pts);

        // Convert back to integer QPoint and adjust
        return QPoint(std::round(centroid.x()) + xLow - 3,
                      std::round(centroid.y()) + yLow - 3);
    }

    QVector<QPoint> getNeighbors(const QPoint& p) {
        return {
            QPoint(p.x()-1, p.y()), QPoint(p.x()+1, p.y()),
            QPoint(p.x(), p.y()-1), QPoint(p.x(), p.y()+1),
            QPoint(p.x()-1, p.y()-1), QPoint(p.x()+1, p.y()-1),
            QPoint(p.x()-1, p.y()+1), QPoint(p.x()+1, p.y()+1)
        };
    }

    QVector<QPoint> getSpinePointsReachableFrom(const QPoint& sbp){
        QStack<QPoint> dfs;
        QSet<QPoint> visited;
        dfs.push(sbp);
        while(!dfs.empty()){
            QPoint currPoint=dfs.pop();
            if(visited.contains(currPoint))
                continue;
            visited.insert(currPoint);

            QVector<QPoint> neighbors=getNeighbors(currPoint);
            for (const QPoint& neighbor : neighbors) {
                if (isValid(neighbor) && !visited.contains(neighbor)) {
                    T val = markingSBP.at(neighbor.x(), neighbor.y()).getValue();
                    if (val == __spine__ || val == __ssj__ || val == __sse__ || val == __sbp__) {
                        dfs.push(neighbor);
                    }
                }
            }
        }

        return visited.values();
    }
    bool isValid(const QPoint& p) {
        return p.x() >= 1 && p.x() < rows-1 &&
               p.y() >= 1 && p.y() < cols-1;
    }
};



#endif // ADVANCEDSPINELABELLING_H
