#ifndef DENDRITEEXTRACTION_H
#define DENDRITEEXTRACTION_H
#include "label.h"
#include "neighborhood.h"
#include "matrix.h"
#include "mainwindow.h"
#include <QSet>
#include <QVector>
#include <omp.h>
#include <QStatusBar>
template <typename T>
class DendriteExtraction {
public:
    DendriteExtraction(MainWindow* ui,const Matrix<T>& skeleton,const Matrix<T> dt,const Matrix<T> img,int zoomfactor) :mainWindow(ui), dt_(dt),skeleton_(skeleton),image(img),zoom(zoomfactor) {
    }
    void extractDendrite(double alpha,int iterations){
        skel2=skeleton_;

        int rows=skeleton_.getRows(),cols=skeleton_.getCols();
        if (mainWindow) {
            mainWindow->display(image, skeleton_,zoom);
            mainWindow->setProgressBar(rows*cols);
            mainWindow->updateProgressBar(0);
            mainWindow->statusBar()->showMessage("Dendrite Extraction Started...");
            mainWindow->delay(1);
        }
        detectJunctionsAndEndPoints(skeleton_);
        if (mainWindow) {
            mainWindow->display(image, skeleton_,zoom);
            mainWindow->setProgressBar(rows*cols);
            mainWindow->updateProgressBar(0);
            mainWindow->statusBar()->showMessage("Junction Points and End Points detected...");
            mainWindow->delay(1);
        }
        pathDelete(skeleton_,alpha);
        if (mainWindow) {
            mainWindow->display(image, skeleton_,zoom);
            mainWindow->setProgressBar(rows*cols);
            mainWindow->updateProgressBar(0);
            mainWindow->statusBar()->showMessage(QString("Iteration %1 of Prunning done...").arg(1));
            mainWindow->delay(1);
        }
        editIsolatedGreenOrBluePoints(skeleton_);
        if(mainWindow){
            mainWindow->statusBar()->showMessage("Iteration Done = 1");
            mainWindow->delay(1);
        }
        iterativeDelete(skeleton_,alpha,iterations);
        if(mainWindow){
            mainWindow->statusBar()->showMessage("Primary Dendrite Extraction Done");
            mainWindow->delay(1);
        }
    }

    Matrix<T> skeleton() const
    {
        return skeleton_;
    }

    Matrix<T> getSkel2()  {
        int rows = skeleton_.getRows(), cols = skeleton_.getCols();
        Matrix<T> temp(rows, cols, 0);

        // First pass: Mark dendrite endpoints
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                T val = skeleton_.at(i,j).getValue();
                if(val) {
                    std::bitset<8> nb = skeleton_.getNeighborhood(i,j).getNeighborsBinaryNot(0);
                    if(nb.count() == 1)
                        temp.at(i,j).setValue(__de__);
                }
            }
        }

        // Second pass: Copy non-overlapping points from skel2
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                int val = skel2.at(i,j).getValue();
                if(val && !skeleton_.at(i,j).getValue())
                    temp.at(i,j).setValue(val);
            }
        }
        Matrix<T> result(rows, cols, 0);
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                T val=temp.at(i,j).getValue();
                if(val==__de__){
                    QQueue<QPoint> q;
                    q.enqueue(QPoint(i,j));
                    QSet<QPoint> visited;
                    while(!q.isEmpty()){
                        QPoint curr=q.dequeue();
                        if(visited.contains(curr))continue;
                        visited.insert(curr);
                        T val=temp.at(curr.x(),curr.y()).getValue();
                        result.at(curr.x(),curr.y()).setValue(val);

                        QVector<QPoint> neighbors=getNeighbors(curr);
                        foreach (auto neighbor, neighbors) {
                            if(temp.at(neighbor.x(),neighbor.y()).getValue())
                                q.enqueue(neighbor);
                        }
                    }
                }
            }
        }
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                T val=result.at(i,j).getValue();
                if(val==__de__)
                    result.at(i,j).setValue(__jp__);
                if(!val){
                    result.at(i,j).setValue(skeleton_.at(i,j).getValue());
                }
            }
        }
        return result;
    }

private:
    int zoom=1;
    MainWindow* mainWindow;
    Matrix<T> dt_,skeleton_,image,skel2;
    QStringList patternlist={
        "11000000",
        "01100000",
        "00110000",
        "00011000",
        "00001100",
        "00000110",
        "00000011",
        "10000001",
    };
    QVector<QPoint> getNeighbors(QPoint p) {
        QVector<QPoint> neighbors;
        neighbors.reserve(8); // Reserve space for efficiency

        // All 8 directions: top-left, top, top-right, right, bottom-right, bottom, bottom-left, left
        const int dx[] = {-1, -1, -1,  0,  1, 1, 1, 0};
        const int dy[] = {-1,  0,  1,  1,  1, 0, -1, -1};

        for(int i = 0; i < 8; ++i) {
            neighbors.append(QPoint(p.x() + dx[i], p.y() + dy[i]));
        }

        return neighbors;
    }
    inline void detectJunctionsAndEndPoints(Matrix<T> &skeleton_){
        int rows=skeleton_.getRows(),cols=skeleton_.getCols();
        Matrix<T> skel(skeleton_);
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                int val=skeleton_.at(i,j).getValue();
                if(val==255){
                    Neighborhood<T> n=skeleton_.getNeighborhood(i,j);
                    QVector<const Cell<T>*> nb=n.getAllNeighbors();
                    int count=0;
                    foreach (auto e, nb) {
                        if(e->getValue()>0)
                            count++;
                    }
                    if(count==1)
                        skel.at(i,j).setValue(__ep__);
                    else if (count>=3) {
                        skel.at(i,j).setValue(__jp__);
                    }
                    else if(count==2 && (isSpineEnd(n.getNeighborsBinaryNot(0))))
                        skel.at(i,j).setValue(__ep__);
                }
                if(val==__de__){
                    note<<"dendrite found";
                }

            }
            if (mainWindow && i%10==0) {
                mainWindow->display(image, skel);
                mainWindow->updateProgressBar(i*cols);
            }
        }
        skeleton_=skel;
    }

    inline bool isSpineEnd(std::bitset<8> neighborhood){
        QString nb=QString::fromStdString(neighborhood.to_string());
        foreach (auto e, patternlist) {
            if(nb==e)
                return true;
        }
        return false;
    }

    inline void pathDelete(Matrix<T> &skeleton_,double alpha){
        int rows=skeleton_.getRows(),cols=skeleton_.getCols();
        int epno=0;
        Matrix<int> visited(rows,cols,-1);
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                if(skeleton_.at(i,j).getValue()==__ep__){
                    epno++;
                    EPtoJP(skeleton_,visited,i,j,alpha,epno);
                }
            }
            if (mainWindow && i%10==0) {
                mainWindow->display(image, skeleton_);
                mainWindow->updateProgressBar(i*cols);
            }
        }
    }

    inline void EPtoJP(Matrix<T> &skel, Matrix<int> &visited, int startI, int startJ, double alpha, int epno) {
        int rows = skel.getRows();
        int cols = skel.getCols();

        // Boundary checks
        if (startI < 1 || startI >= rows-1 || startJ < 1 || startJ >= cols-1) {
            return;
        }

        // Already visited check
        if (visited.at(startI, startJ).getValue() == epno) {
            return;
        }

        // Mark start point as visited
        visited.at(startI, startJ).setValue(epno);

        // Path tracking
        QVector<QPoint> path;
        path.append(QPoint(startI, startJ));

        int currentX = startI;
        int currentY = startJ;
        int junctionFoundFlag = 0;
        int dtVal = 0;

        // Prevent infinite loops
        const int MAX_PATH_LENGTH = rows * cols;

        while (path.size() < MAX_PATH_LENGTH) {
            bool pixelFound = false;

            // Search in 3x3 neighborhood
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    // Skip center pixel
                    if (dx == 0 && dy == 0) continue;

                    int newX = currentX + dx;
                    int newY = currentY + dy;

                    // Boundary check
                    if (newX < 1 || newX >= rows-1 || newY < 1 || newY >= cols-1) {
                        continue;
                    }

                    // Skip already visited points in this iteration
                    if (visited.at(newX, newY).getValue() == epno) {
                        continue;
                    }

                    // Check if pixel is part of skeleton
                    if (skel.at(newX, newY).getValue() > 0) {
                        // Mark as visited
                        visited.at(newX, newY).setValue(epno);

                        // Junction point found
                        if (skel.at(newX, newY).getValue() == __jp__ /*|| skel.at(newX, newY).getValue() == __de__*/ ) {
                            junctionFoundFlag = 1;
                            dtVal = dt_.at(newX, newY).getValue();
                            path.append(QPoint(newX, newY));
                            break;
                        }

                        // Continue path traversal
                        path.append(QPoint(newX, newY));
                        currentX = newX;
                        currentY = newY;
                        pixelFound = true;
                        break;
                    }
                }

                // Exit outer loop if junction found or pixel found
                if (junctionFoundFlag || pixelFound) {
                    break;
                }
            }

            // Exit conditions
            if (junctionFoundFlag) {
                break;
            }

            // No neighboring pixels found
            if (!pixelFound) {
                break;
            }
        }

        // Path pruning based on distance transform value
        int pathLength = path.size();
        int pruneCutoff = std::max(0, pathLength - static_cast<int>(std::ceil(dtVal * alpha / 3)));

        if (pruneCutoff <= 0) {
            // Remove path points that are not junction points
            for (const auto& point : path) {
                int px = point.x();
                int py = point.y();

                // Preserve junction points
                if (skel.at(px, py).getValue() != __jp__ /*|| skel.at(px, py).getValue() != __de__*/) {
                    skel.at(px, py).setValue(0);
                }
            }
        }
    }
    inline void editIsolatedGreenOrBluePoints(Matrix<T> &skeleton_){
        int rows=skeleton_.getRows(),cols=skeleton_.getCols();
        for (int i = 2; i < rows-2; ++i) {
            for (int j = 2; j < cols-2; ++j) {
                if(skeleton_.at(i,j).getValue()==__jp__){

                    if(skeleton_.at(i+1,j).getValue()==255 || skeleton_.at(i+1,j).getValue()==__jp__){

                        if(
                            (skeleton_.at(i+1,j-1).getValue()==0 || skeleton_.at(i+1,j-1).getValue()==__ep__)   &&
                            (skeleton_.at(i+2,j-1).getValue()==0 || skeleton_.at(i+2,j-1).getValue()==__ep__)   &&
                            (skeleton_.at(i+2,j).getValue()==0   || skeleton_.at(i+2,j).getValue()==__ep__)     &&
                            (skeleton_.at(i+2,j+1).getValue()==0 || skeleton_.at(i+2,j+1).getValue()==__ep__)   &&
                            (skeleton_.at(i+1,j+1).getValue()==0 || skeleton_.at(i+1,j+1).getValue()==__ep__)
                            ){
                            skeleton_.at(i+1,j).setValue(0);
                        }

                    }
                    if(skeleton_.at(i-1,j).getValue()==255 || skeleton_.at(i-1,j).getValue()==__jp__){

                        if(
                            (skeleton_.at(i-1,j-1).getValue()==0 || skeleton_.at(i-1,j-1).getValue()==__ep__) &&
                            (skeleton_.at(i-2,j-1).getValue()==0 || skeleton_.at(i-2,j-1).getValue()==__ep__) &&
                            (skeleton_.at(i-2,j).getValue()==0   || skeleton_.at(i-2,j).getValue()==__ep__) &&
                            (skeleton_.at(i-2,j+1).getValue()==0 || skeleton_.at(i-2,j+1).getValue()==__ep__) &&
                            (skeleton_.at(i-1,j+1).getValue()==0 || skeleton_.at(i-1,j+1).getValue()==__ep__)
                            ){
                            skeleton_.at(i-1,j).setValue(0);
                        }
                    }

                    if(skeleton_.at(i,j+1).getValue()==255 || skeleton_.at(i,j+1).getValue()==__jp__){

                        if(
                            (skeleton_.at(i-1,j+1).getValue()==0 || skeleton_.at(i-1,j+1).getValue()==__ep__) &&
                            (skeleton_.at(i-1,j+2).getValue()==0 || skeleton_.at(i-1,j+2).getValue()==__ep__) &&
                            (skeleton_.at(i,j+2).getValue()==0   || skeleton_.at(i,j+2).getValue()==__ep__) &&
                            (skeleton_.at(i+1,j+2).getValue()==0 || skeleton_.at(i+1,j+2).getValue()==__ep__) &&
                            (skeleton_.at(i+1,j+1).getValue()==0 || skeleton_.at(i+1,j+1).getValue()==__ep__)
                            ){
                            skeleton_.at(i,j+1).setValue(0);
                        }
                    }

                    if(skeleton_.at(i,j-1).getValue()==255 || skeleton_.at(i,j-1).getValue()==__jp__){

                        if(
                            (skeleton_.at(i-1,j-1).getValue()==0 || skeleton_.at(i-1,j-1).getValue()==__ep__) &&
                            (skeleton_.at(i-1,j-2).getValue()==0 || skeleton_.at(i-1,j-2).getValue()==__ep__) &&
                            (skeleton_.at(i,j-2).getValue()==0   || skeleton_.at(i,j-2).getValue()==__ep__) &&
                            (skeleton_.at(i+1,j-2).getValue()==0 || skeleton_.at(i+1,j-2).getValue()==__ep__) &&
                            (skeleton_.at(i+1,j-1).getValue()==0 || skeleton_.at(i+1,j-1).getValue()==__ep__)
                            ){
                            skeleton_.at(i,j-1).setValue(0);
                        }
                    }

                    if(skeleton_.at(i+1, j).getValue() == __jp__){

                        if(skeleton_.at(i+1, j-1).getValue() == __jp__ && skeleton_.at(i, j+1).getValue() == __jp__){
                            skeleton_.at(i+1, j-1).setValue(255);
                            skeleton_.at(i, j+1).setValue(255);
                        }
                        if(skeleton_.at(i, j-1).getValue() == __jp__ && skeleton_.at(i+1, j+1).getValue() == __jp__){
                            skeleton_.at(i, j-1).setValue(255);
                            skeleton_.at(i+1, j+1).setValue(255);
                        }
                    }

                    if(skeleton_.at(i-1, j).getValue() == __jp__){

                        if(skeleton_.at(i-1, j-1).getValue() == __jp__ && skeleton_.at(i, j+1).getValue() == __jp__){
                            skeleton_.at(i-1, j-1).setValue(255);
                            skeleton_.at(i, j+1).setValue(255);
                        }
                        if(skeleton_.at(i-1, j+1).getValue() == __jp__ && skeleton_.at(i, j-1).getValue() == __jp__){
                            skeleton_.at(i-1, j+1).setValue(255);
                            skeleton_.at(i, j-1).setValue(255);
                        }
                    }


                    if(skeleton_.at(i, j+1).getValue() == __jp__){

                        if(skeleton_.at(i-1, j+1).getValue() == __jp__ && skeleton_.at(i+1, j).getValue() == __jp__){
                            skeleton_.at(i-1, j+1).setValue(255);
                            skeleton_.at(i+1, j).setValue(255);
                        }
                        if(skeleton_.at(i+1, j+1).getValue() == __jp__ && skeleton_.at(i-1, j).getValue() == __jp__){
                            skeleton_.at(i+1, j+1).setValue(255);
                            skeleton_.at(i-1, j).setValue(255);
                        }
                    }


                    if(skeleton_.at(i, j-1).getValue() == __jp__){

                        if(skeleton_.at(i-1, j-1).getValue() == __jp__ && skeleton_.at(i+1, j).getValue() == __jp__){
                            skeleton_.at(i-1, j-1).setValue(255);
                            skeleton_.at(i+1, j).setValue(255);
                        }
                        if(skeleton_.at(i+1, j-1).getValue() == __jp__ && skeleton_.at(i-1, j).getValue() == __jp__){
                            skeleton_.at(i+1, j-1).setValue(255);
                            skeleton_.at(i-1, j).setValue(255);
                        }
                    }


                    if(skeleton_.at(i-1, j).getValue() == __jp__ && skeleton_.at(i, j+1).getValue() == __jp__){
                        skeleton_.at(i-1, j).setValue(255);
                        skeleton_.at(i, j+1).setValue(255);
                    }

                    if(skeleton_.at(i+1, j).getValue() == __jp__ && skeleton_.at(i, j+1).getValue() == __jp__){
                        skeleton_.at(i+1, j).setValue(255);
                        skeleton_.at(i, j+1).setValue(255);
                    }

                    if(skeleton_.at(i-1, j).getValue() == __jp__ && skeleton_.at(i, j-1).getValue() == __jp__){
                        skeleton_.at(i-1, j).setValue(255);
                        skeleton_.at(i, j-1).setValue(255);
                    }

                    if(skeleton_.at(i+1, j).getValue() == __jp__ && skeleton_.at(i, j-1).getValue() == __jp__){
                        skeleton_.at(i+1, j).setValue(255);
                        skeleton_.at(i, j-1).setValue(255);
                    }

                }
            }
            if (mainWindow && i%10==0) {
                mainWindow->display(image, skeleton_);
                mainWindow->updateProgressBar(i*cols);
            }
        }
        if (mainWindow) {
            mainWindow->display(image, skeleton_);
            mainWindow->setProgressBar(rows*cols);
            mainWindow->updateProgressBar(0);
        }
    }

    inline void iterativeDelete(Matrix<T> &skeleton_,double alpha,int iterations){

        int rows=skeleton_.getRows(),cols=skeleton_.getCols();
        for (int iter = 2; iter <= iterations; ++iter) {
            if(mainWindow){
                mainWindow->statusBar()->showMessage("Iteration Started = "+QString::number(iter));
                mainWindow->delay(1);
            }
            detectJunctionsAndEndPoints(skeleton_);
            if (mainWindow) {
                mainWindow->display(image, skeleton_);
                mainWindow->setProgressBar(rows*cols);
                mainWindow->updateProgressBar(0);
                mainWindow->statusBar()->showMessage("Junction Points and End Points detected...");
                mainWindow->delay(1);
            }
            Matrix<T> copy(skeleton_);

            for(int j=1;j<cols-1;j++)
            {
                for(int i=1;i<rows-1;i++)
                {
                    if(skeleton_.at(i,j).getValue()==__jp__){
                        QVector<const Cell<T>*> nb=skeleton_.getNeighborhood(i,j).getAllNeighbors();
                        int count=0;
                        foreach (auto e, nb) {
                            if(e->getValue()!=0)
                                count++;
                        }

                        if(count==1){
                            copy.at(i,j).setValue(__ep__);
                        }
                    }
                }
            }
            if (mainWindow) {
                mainWindow->display(image, copy);
                mainWindow->setProgressBar(rows*cols);
                mainWindow->updateProgressBar(0);
                mainWindow->statusBar()->showMessage("Junction Points with exactly 1 neighbor turned to End Point...");
                mainWindow->delay(1);
            }
            pathDelete(copy,alpha);
            skeleton_=copy;
            if (mainWindow) {
                mainWindow->display(image, skeleton_);
                mainWindow->setProgressBar(rows*cols);
                mainWindow->updateProgressBar(0);
                mainWindow->statusBar()->showMessage(QString("Iteration %1 of Pruning done...").arg(iter));
                mainWindow->delay(1);
            }
            for(int j=1;j<cols-1;j++)
            {
                for(int i=1;i<rows-1;i++)
                {
                    if(copy.at(i,j).getValue()==__ep__){
                        skeleton_.at(i,j).setValue(0);
                    }
                }
            }
            editIsolatedGreenOrBluePoints(skeleton_);
        }
    }

};

#endif
