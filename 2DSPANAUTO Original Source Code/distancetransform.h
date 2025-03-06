#ifndef DISTANCETRANSFORM_H
#define DISTANCETRANSFORM_H

#include <cmath>
#include "matrix.h"
#include <omp.h>
template <typename T>
class DistanceTransform {
public:
    static Matrix<T> computeEuclidean(const Matrix<T>& binarizedImage) {
        int rows = binarizedImage.getRows();
        int cols = binarizedImage.getCols();

        Matrix<double> dt(binarizedImage.getRows(),binarizedImage.getCols(),0);


        double weights[8];

        weights[0] = weights[2] = weights[5] = weights[7] = sqrt(2);
        weights[1] = weights[3] = weights[4] = weights[6] = 1.0;


        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int val=binarizedImage.at(i, j).getValue();
                if (val == 255) {
                    dt.at(i, j).setValue(INT_MAX);
                }
            }
        }

        bool changed;
        do {
            changed = false;


            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int val=dt.at(i, j).getValue();
                    if (val > 0) {
                        for (int n = 0; n < 4; ++n) {
                            int p = i + dy[n];
                            int q = j + dx[n];
                            if (p >= 0 && p < rows && q >= 0 && q < cols) {
                                double cost = qMax(weights[n] ,dt.at(p, q).getValue() + weights[n]);
                                if (cost < val) {
                                    dt.at(i, j).setValue(cost);
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }


            for (int i = rows - 1; i >= 0; --i) {
                for (int j = cols - 1; j >= 0; --j) {
                    int val=dt.at(i, j).getValue();
                    if (val > 0) {
                        for (int n = 4; n < 8; ++n) {
                            int p = i + dy[n];
                            int q = j + dx[n];
                            if (p >= 0 && p < rows && q >= 0 && q < cols) {
                                double cost = qMax(weights[n] ,dt.at(p, q).getValue() + weights[n]);
                                if (cost < val) {
                                    dt.at(i, j).setValue(cost);
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        } while (changed);


        // for (int j = 0; j < cols; j++) {
        //     for (int i = 0; i < rows; i++) {
        //         int val=dt.at(i, j).getValue();
        //         if (val == 3) dt.at(i, j).setValue(1);
        //         if (val == 6) dt.at(i, j).setValue(5);
        //     }
        // }
        Matrix<T> dtInteger(dt.getRows(),dt.getCols(),0);
        for (int i = 0; i < dt.getRows(); ++i) {
            for (int j = 0; j < dt.getCols(); ++j) {
                T val=round(pow(dt.at(i,j).getValue(),2));
                dtInteger.at(i,j).setValue(val);
            }
        }

        return dtInteger;

    }
    static Matrix<T> compute(const Matrix<T>& binarizedImage) {
        int rows = binarizedImage.getRows();
        int cols = binarizedImage.getCols();

        Matrix<T> dt(binarizedImage);


        double weights[8];

        weights[0] = weights[2] = weights[5] = weights[7] = 4.0;
        weights[1] = weights[3] = weights[4] = weights[6] = 3.0;


        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int val=binarizedImage.at(i, j).getValue();
                if (val == 255) {
                    dt.at(i, j).setValue(INT_MAX);
                }
            }
        }

        bool changed;
        do {
            changed = false;


            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int val=dt.at(i, j).getValue();
                    if (val > 0) {
                        for (int n = 0; n < 4; ++n) {
                            int p = i + dy[n];
                            int q = j + dx[n];
                            if (p >= 0 && p < rows && q >= 0 && q < cols) {
                                double cost = qMax(weights[n] ,dt.at(p, q).getValue() + weights[n]);
                                if (cost < val) {
                                    dt.at(i, j).setValue(cost);
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }


            for (int i = rows - 1; i >= 0; --i) {
                for (int j = cols - 1; j >= 0; --j) {
                    int val=dt.at(i, j).getValue();
                    if (val > 0) {
                        for (int n = 4; n < 8; ++n) {
                            int p = i + dy[n];
                            int q = j + dx[n];
                            if (p >= 0 && p < rows && q >= 0 && q < cols) {
                                double cost = qMax(weights[n] ,dt.at(p, q).getValue() + weights[n]);
                                if (cost < val) {
                                    dt.at(i, j).setValue(cost);
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        } while (changed);


        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                int val=dt.at(i, j).getValue();
                if (val == 3) dt.at(i, j).setValue(1);
                if (val == 6) dt.at(i, j).setValue(5);
            }
        }

        return dt;
    }

    static Matrix<T> computeFuzzy(const Matrix<T> &grayImage) {
        int rows = grayImage.getRows();
        int cols = grayImage.getCols();
        Matrix<T> dt(rows, cols,0);

        // Find statistics for object pixels (assuming lower intensity is object)
        std::vector<T> objectPixels;
        T minVal = std::numeric_limits<T>::max();
        T maxVal = std::numeric_limits<T>::min();

        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < cols; ++i) {
                T val = grayImage.at(i, j).getValue();
                if (val > 0 && val < 128) {  // Object pixels are typically darker
                    objectPixels.push_back(val);
                    minVal = std::min(minVal, val);
                    maxVal = std::max(maxVal, val);
                }
            }
        }

        // If no object pixels found, return empty matrix
        if (objectPixels.empty()) {
            qDebug() << "No object pixels found";
            return dt;
        }

        // Sort object pixels to get robust statistics
        std::sort(objectPixels.begin(), objectPixels.end());

        // Calculate robust mean and standard deviation for object pixels
        double objectMean = 0.0;
        double objectStdDev = 0.0;
        int start = objectPixels.size() * 0.1;
        int end = objectPixels.size() * 0.9;
        int count = end - start;

        // Calculate mean
        for (int i = start; i < end; ++i) {
            objectMean += objectPixels[i];
        }
        objectMean /= count;

        // Calculate standard deviation
        for (int i = start; i < end; ++i) {
            objectStdDev += std::pow(objectPixels[i] - objectMean, 2);
        }
        objectStdDev = std::sqrt(objectStdDev / count);

        qDebug() << "Object Min:" << minVal << "Max:" << maxVal;
        qDebug() << "Object Mean:" << objectMean << "StdDev:" << objectStdDev;

        // Ensure non-zero standard deviation
        if (objectStdDev < 1.0) objectStdDev = 1.0;

        // Gaussian membership function for objects
        auto objectMembership = [&](T val) -> double {
            if (val >= 128) return 0.0;  // Background pixels
            if (val <= 0) return 0.0;

            // Robust Gaussian membership for object pixels
            double normalized = (val - objectMean) / objectStdDev;
            return std::exp(-0.5 * normalized * normalized);
        };

        // Distance transformation
        std::vector<std::vector<double>> distanceMap(rows, std::vector<double>(cols, std::numeric_limits<double>::max()));

        // Initial distance calculation
        double maxDistance = 0.0;
        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < cols; ++i) {
                T val = grayImage.at(i, j).getValue();

                // Compute membership and distance
                double membership = objectMembership(val);

                // Invert distance for objects
                distanceMap[j][i] = (1.0 - membership) * 255.0;

                maxDistance = std::max(maxDistance, distanceMap[j][i]);
            }
        }

        // Distance propagation
        bool changed;
        int maxPasses = 3;
        for (int pass = 0; pass < maxPasses; ++pass) {
            changed = false;

            // Propagate in 8 directions
            for (int j = 0; j < rows; ++j) {
                for (int i = 0; i < cols; ++i) {
                    for (int n = 0; n < 8; ++n) {
                        int p = i + dx[n];
                        int q = j + dy[n];

                        if (p >= 0 && p < cols && q >= 0 && q < rows) {
                            // Directional weights
                            double weights[8] = {4.0, 3.0, 4.0, 3.0, 3.0, 4.0, 3.0, 4.0};

                            // Potential new distance
                            double newDist = distanceMap[q][p] + weights[n];

                            // Update if shorter path found
                            if (newDist < distanceMap[j][i]) {
                                distanceMap[j][i] = newDist;
                                changed = true;
                            }
                        }
                    }
                }
            }

            if (!changed) break;
        }

        // Normalize and set values
        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < cols; ++i) {
                // Ensure value is in 0-255 range
                int value = static_cast<int>((distanceMap[j][i] / maxDistance) * 255.0);
                value = std::max(0, std::min(255, value));

                // Invert values to show objects brightly
                dt.at(i, j).setValue(255 - value);
            }
        }

        return dt;
    }



private:
    static const int dx[8];
    static const int dy[8];
};


template <typename T>
const int DistanceTransform<T>::dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
template <typename T>
const int DistanceTransform<T>::dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

#endif
