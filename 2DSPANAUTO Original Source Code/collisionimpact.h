#ifndef COLLISIONIMPACT_H
#define COLLISIONIMPACT_H

#include "matrix.h"

template <typename T>
class CollisionImpact {
public:

    CollisionImpact(const Matrix<T>& dt, const Matrix<T>& bin)
        : dt(dt), bin(bin), r(dt.getRows()), c(dt.getCols()) {}


    inline void computeCI(Matrix<T>& CI) {
        double cost;
        for (int j = 0; j < c; j++) {
            for (int i = 0; i < r; i++) {
                if (dt.at(i, j).getValue() == 0) continue;

                double maxVal = 0.0;

                for (int p = -1; p <= 1; ++p) {
                    for (int q = -1; q <= 1; ++q) {
                        int ni = i + p;
                        int nj = j + q;

                        if (ni >= 0 && ni < r && nj >= 0 && nj < c) {
                            cost = (p != 0 && q != 0) ? 4 : 3;


                            double val = (double)(dt.at(ni, nj).getValue() - dt.at(i, j).getValue()) / cost;
                            maxVal = std::max(maxVal, val);
                        }
                    }
                }

                if (maxVal > 1) maxVal = 1;
                if (maxVal < 0) maxVal = 0;


                CI.at(i, j).setValue((1 - maxVal) * 255);
            }
        }
    }

private:
    Matrix<T> dt;
    Matrix<T> bin;
    int r, c;
};

#endif
