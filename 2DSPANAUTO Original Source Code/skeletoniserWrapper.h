#ifndef SKELETONISERWRAPPER_H
#define SKELETONISERWRAPPER_H
#include "matrix.h"

template <typename T>
class Skeletoniser {
public:
    Skeletoniser(Matrix<T> &currDT, Matrix<T> &currCI)
        : currDT(currDT), currCI(currCI) {
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
        Matrix<T> skel(r, c, 0), bin;
        for (int j = 1; j < c - 1; j++) {
            for (int i = 1; i < r - 1; i++) {
                val = currDT.at(i, j).getValue();
                if (val) skel.at(i, j).setValue(255);
            }
        }
        bin = skel;

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
        }

        return skel;
    }

    Matrix<T> finalSkeletonization(Matrix<T> primarySkel) {

        int r = currDT.getRows(), c = currDT.getCols();
        int prevPrunableDT = 0, curPrunableDT = 0, val;
        Matrix<T> skel(primarySkel), bin(r, c, 0);
        for (int j = 1; j < c - 1; j++) {
            for (int i = 1; i < r - 1; i++) {
                val = currDT.at(i, j).getValue();
                if (val) bin.at(i, j).setValue(255);
            }
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
        }
        return skel;
    }

    int DTMAX = 0;

private:
    Matrix<T> &currDT;
    Matrix<T> &currCI;
    double zoom;

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
#endif // SKELETONISERWRAPPER_H
