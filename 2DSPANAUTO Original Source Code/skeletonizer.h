#ifndef SKELETONIZER_H
#define SKELETONIZER_H
// #pragma once
#include "mainwindow.h"
// #include "mainwindow.h"
#include "matrix.h"
template <typename T>
class Skeletonizer {
public:
    Skeletonizer(Matrix<T> &currDT, Matrix<T> &currCI, MainWindow* ui)
        : currDT(currDT), currCI(currCI) , mainWindow(ui){
        DTMAX = 0;
        int r = currDT.getRows(), c = currDT.getCols();
        for (int i = 1; i < r-1; ++i) {
            for (int j = 1; j < c-1; ++j) {
                if (currDT.at(i, j).getValue() > DTMAX) {
                    DTMAX = currDT.at(i, j).getValue();
                }
            }
        }

    }

    Matrix<T> primarySkeletonization() {
        int prevPrunableDT = 0, curPrunableDT = 0;
        int r = currDT.getRows(), c = currDT.getCols();
        int val;
        Matrix<T> skel(r, c, 0), bin,black(r,c,0);
        for (int j = 1; j < c - 1; j++) {
            for (int i = 1; i < r - 1; i++) {
                val = currDT.at(i, j).getValue();
                if (val) skel.at(i, j).setValue(255);
            }
        }
        bin = skel;
        if (mainWindow) {
            mainWindow->display(skel);
            mainWindow->delay(1);
            mainWindow->setProgressBar(DTMAX);
        }
        while (curPrunableDT <= DTMAX) {
            curPrunableDT = INT_MAX;
            for (int j = 1; j < c - 1; j++) {
                for (int i = 1; i < r - 1; i++) {
                    val = currDT.at(i, j).getValue();
                    if (val && prevPrunableDT < val && val < curPrunableDT)
                        curPrunableDT = val;
                }
            }
            prevPrunableDT = curPrunableDT;
            for (int j = 1; j < c - 1; j++) {
                for (int i = 1; i < r - 1; i++) {
                    val = currDT.at(i, j).getValue();
                    if (val == curPrunableDT &&
                        isSimplePoint(skel, i, j, curPrunableDT, 1) &&
                        currCI.at(i, j).getValue() == 0) {
                        skel.at(i, j).setValue(0);
                    }
                }
            }

            if (mainWindow) {
                mainWindow->display(black, skel);
                // mainWindow->delay(1);
                mainWindow->updateProgressBar(curPrunableDT == INT_MAX ? DTMAX : curPrunableDT);
            }
        }
        if (mainWindow) {
            mainWindow->display(bin, skel);
            // mainWindow->delay(1);
            mainWindow->updateProgressBar(curPrunableDT == INT_MAX ? DTMAX : curPrunableDT);
        }
        return skel;
    }

    Matrix<T> finalSkeletonization(Matrix<T> primarySkel) {

        int r = currDT.getRows(), c = currDT.getCols();
        int prevPrunableDT = 0, curPrunableDT = 0, val;
        Matrix<T> skel(primarySkel), bin(r, c, 0),black(r,c,0);
        for (int j = 1; j < c - 1; j++) {
            for (int i = 1; i < r - 1; i++) {
                val = currDT.at(i, j).getValue();
                if (val) bin.at(i, j).setValue(255);
            }
        }
        if (mainWindow) {
            mainWindow->display(bin, skel);
            mainWindow->setProgressBar(DTMAX);
            mainWindow->updateProgressBar(0);
        }
        while (curPrunableDT <= DTMAX) {
            curPrunableDT = INT_MAX;
            for (int j = 1; j < c - 1; j++) {
                for (int i = 1; i < r - 1; i++) {
                    val = currDT.at(i, j).getValue();
                    if (skel.at(i, j).getValue() &&
                        prevPrunableDT < val &&
                        val < curPrunableDT)
                        curPrunableDT = val;
                }
            }
            prevPrunableDT = curPrunableDT;
            for (int j = 1; j < c - 1; j++) {
                for (int i = 1; i < r - 1; i++) {
                    val = currDT.at(i, j).getValue();
                    if (skel.at(i, j).getValue() &&
                        val == curPrunableDT &&
                        isSimplePoint(skel, i, j, curPrunableDT, 0)) {
                        skel.at(i, j).setValue(0);
                    }
                }
            }
            if (mainWindow) {
                mainWindow->display(black, skel);
                // mainWindow->delay(1);
                mainWindow->updateProgressBar(curPrunableDT == INT_MAX ? DTMAX : curPrunableDT);
            }
        }
        if (mainWindow) {
            mainWindow->display(bin, skel);
            // mainWindow->delay(1);
            mainWindow->updateProgressBar(curPrunableDT == INT_MAX ? DTMAX : curPrunableDT);
        }
        return skel;
    }

    int DTMAX = 0;

    // Matrix<T> findMainDendrite(Matrix<T> finalSkel){
    //     Matrix<T> copy=finalSkel;
    //     detectJunctionsAndEndPoints(copy);
    //     for (int i = 0; i < copy.getRows(); ++i) {
    //         for (int j = 0; j < copy.getCols(); ++j) {
    //             T val=finalSkel.at(i,j).getValue();
    //             if(val!=0){
    //                 //perform ant-colony optimisation
    //                 //place ants at random different __sse__
    //                 //place food at random different __jp__
    //                 //after many iterations ants' most traversed path is kept
    //             }
    //         }
    //     }

    //     return copy;
    // }

private:
    Matrix<T> &currDT;
    Matrix<T> &currCI;
    MainWindow *mainWindow;
    double zoom;
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

            }
            if (mainWindow && i%10==0) {
                mainWindow->display(skel);
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
    inline bool isSimplePoint(Matrix<T> mat, int i, int j, int curDT, int psf) {
        if (!has4BGNeighbor(mat, i, j)) return false;
        if (!has8ObNeighbor(mat, i, j)) return false;
        if (!isObNeighbor8Connected(mat, i, j)) return false;
        return forsinglepixelwidth(mat, i, j, curDT, psf);
    }

    inline bool has4BGNeighbor(Matrix<T> mat, int i, int j) {
        Neighborhood<T> A = mat.getNeighborhood(i, j);
        return (A.top()->getValue() == 0 || A.right()->getValue() == 0 || A.left()->getValue() == 0 || A.bottom()->getValue() == 0);
    }

    inline bool has8ObNeighbor(Matrix<T> mat, int i, int j) {
        Neighborhood<T> A = mat.getNeighborhood(i, j);
        return A.getNeighborsBinary().any();
    }

    inline bool isObNeighbor8Connected(Matrix<T> mat, int i, int j) {
        int p = 0, q = 0, x = 0, y = 0;
        Matrix<T> temparr(3, 3, 0);
        for (q = j - 1; q <= j + 1; q++) {
            x = 0;
            for (p = i - 1; p <= i + 1; p++) {
                if (p == i && q == j)
                    temparr.at(x, y).setValue(0);
                else if (mat.at(p, q).getValue() > 0)
                    temparr.at(x, y).setValue(100);
                else
                    temparr.at(x, y).setValue(0);
                x++;
            }
            y++;
        }
        int curlabel = 0;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (temparr.at(x, y).getValue() == 100) {
                    curlabel++;
                    dfs88(temparr, x, y, curlabel);
                }
            }
        }

        return (curlabel == 1);
    }

    inline bool forsinglepixelwidth(Matrix<T> mat, int i, int j, int curDT, int psf) {
        int p, q, count = 0;
        for (q = j - 1; q <= j + 1; q++) {
            for (p = i - 1; p <= i + 1; p++) {
                if (q == j && p == i) continue;
                if (psf == 1) {
                    if (mat.at(p, q).getValue() > 0 || currDT.at(p, q).getValue() == curDT)
                        count++;
                }
                else {
                    if (mat.at(p, q).getValue() > 0)
                        count++;
                }
            }
        }
        if (count == 1) return false;
        else return true;
    }

    inline void dfs88(Matrix<T> &temparr, int x, int y, int curlabel) {
        if (temparr.at(x, y).getValue() != 100) return;
        temparr.at(x, y).setValue(curlabel);
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i >= 0 && j >= 0 && i < 3 && j < 3)
                    dfs88(temparr, i, j, curlabel);
            }
        }
    }


};
#endif
