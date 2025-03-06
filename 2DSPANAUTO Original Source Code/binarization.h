#ifndef BINARIZATION_H
#define BINARIZATION_H

#include "matrix.h"
#include <cmath>


template <typename T>
class Binarization {
private:

public:

    static Matrix<T> clusteringBinarize(const Matrix<T>& imageMatrix,int maxIterations = 100, float tolerance = 1e-4){
        int rows = imageMatrix.getRows();
        int cols = imageMatrix.getCols();

        // Step 1: Initialize centroids randomly (using two random pixel values from the image)
        T centroid1 = imageMatrix.at(rows/2, cols/4).getValue();
        T centroid2 = imageMatrix.at(cols/4, rows/2).getValue();

        // Random initialization, just taking two different random pixels for centroids
        // (In a real implementation, you might want to make sure centroids are different.)
        for (int i = 1; i < rows-1 && (centroid1 == centroid2); ++i) {
            for (int j = 1; j < cols-1 && (centroid1 == centroid2); ++j) {
                centroid1 = imageMatrix.at(i, j).getValue();
                centroid2 = imageMatrix.at(i, j + 1).getValue(); // Ensure different values
            }
        }

        T prevCentroid1 = 0, prevCentroid2 = 0;
        int cluster1Size = 0, cluster2Size = 0;

        // Step 2: Iteratively perform clustering
        std::vector<int> labels(rows * cols);  // stores the cluster assignment for each pixel
        for (int iter = 0; iter < maxIterations; ++iter) {
            // Step 2a: Assign each pixel to the closest centroid
            cluster1Size = 0;
            cluster2Size = 0;
            T sumCluster1 = 0, sumCluster2 = 0;

            for (int i = 1; i < rows-1; ++i) {
                for (int j = 1; j < cols-1; ++j) {
                    T value = imageMatrix.at(i, j).getValue();
                    T dist1 = std::abs(value - centroid1);
                    T dist2 = std::abs(value - centroid2);

                    // Assign to the nearest centroid
                    if (dist1 < dist2) {
                        labels[i * cols + j] = 0;  // cluster 1
                        sumCluster1 += value;
                        ++cluster1Size;
                    } else {
                        labels[i * cols + j] = 1;  // cluster 2
                        sumCluster2 += value;
                        ++cluster2Size;
                    }
                }
            }

            // Step 2b: Update centroids
            if (cluster1Size > 0) {
                centroid1 = sumCluster1 / cluster1Size;
            }
            if (cluster2Size > 0) {
                centroid2 = sumCluster2 / cluster2Size;
            }

            // Step 2c: Check for convergence (if centroids don't change significantly)
            if (std::abs(centroid1 - prevCentroid1) < tolerance && std::abs(centroid2 - prevCentroid2) < tolerance) {
                break;
            }

            // Update previous centroids
            prevCentroid1 = centroid1;
            prevCentroid2 = centroid2;
        }

        // Step 3: Binarize the image based on the final clusters
        Matrix<T> binarizedMatrix(rows, cols, 0);
        for (int i = 1; i < rows-1; ++i) {
            for (int j = 1; j < cols-1; ++j) {
                // Assign 255 if pixel belongs to cluster 1, else 0 for cluster 2
                binarizedMatrix.at(i, j).setValue(labels[i * cols + j] == 0 ? 255 : 0);
            }
        }

        return binarizedMatrix;
    }


    static Matrix<T> otsuBinarize(const Matrix<T>& imageMatrix) {
        int histogram[256] = {0};
        for (int i = 0; i < imageMatrix.getRows(); ++i) {
            for (int j = 0; j < imageMatrix.getCols(); ++j) {
                T value = imageMatrix.at(i, j).getValue();
                histogram[static_cast<int>(value)]++;
            }
        }

        int totalPixels = imageMatrix.getRows() * imageMatrix.getCols();
        int sum = 0;
        for (int t = 0; t < 256; ++t) {
            sum += t * histogram[t];
        }

        int wB = 0;
        float sumB = 0;
        float maxVariance = 0.0f;
        float threshold = 0.0f;

        for (int t = 0; t < 256; ++t) {
            wB += histogram[t];
            if (wB == 0) continue;

            int wF = totalPixels - wB;
            if (wF == 0) break;

            sumB += t * histogram[t];
            float mB = sumB / wB;
            float mF = (sum - sumB) / wF;


            float betweenVariance = static_cast<float>(wB) * static_cast<float>(wF) * (mB - mF) * (mB - mF);
            if (betweenVariance > maxVariance) {
                maxVariance = betweenVariance;
                threshold = static_cast<float>(t);
            }
        }


        Matrix<T> binarizedMatrix(imageMatrix.getRows(), imageMatrix.getCols(), 0);
        for (int i = 0; i < imageMatrix.getRows(); ++i) {
            for (int j = 0; j < imageMatrix.getCols(); ++j) {
                binarizedMatrix.at(i, j).setValue(imageMatrix.at(i, j).getValue() > threshold ? 255 : 0);
            }
        }
        return binarizedMatrix;
    }


    static Matrix<T> globalThresholdBinarize(const Matrix<T>& imageMatrix, T threshold) {
        Matrix<T> binarizedMatrix(imageMatrix.getRows(), imageMatrix.getCols(), 0);

        for (int i = 0; i < imageMatrix.getRows(); ++i) {
            for (int j = 0; j < imageMatrix.getCols(); ++j) {
                T value = imageMatrix.at(i, j).getValue();
                binarizedMatrix.at(i, j).setValue(value > threshold ? 255 : 0);
            }
        }
        return binarizedMatrix;
    }


    static Matrix<T> unetBinarize(const Matrix<T>& imageMatrix) {
        Matrix<T> binarizedMatrix(imageMatrix.getRows(), imageMatrix.getCols(), 0);
        return binarizedMatrix;
    }
};

#endif
