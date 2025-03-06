#ifndef DENOISING_H
#define DENOISING_H

#include "matrix.h"

template <typename T>
class Denoising {
public:
    static Matrix<T> meanDenoise(const Matrix<T>& imageMatrix, int kernelSize) {
        if (kernelSize % 2 == 0) {

            kernelSize++;
        }

        int rows = imageMatrix.getRows();
        int cols = imageMatrix.getCols();
        Matrix<T> denoisedMatrix(rows, cols, 0);
        int halfKernel = kernelSize / 2;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                T sum = 0;
                int count = 0;
                for (int ki = -halfKernel; ki <= halfKernel; ++ki) {
                    for (int kj = -halfKernel; kj <= halfKernel; ++kj) {
                        int ni = i + ki, nj = j + kj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            sum += imageMatrix.at(ni, nj).getValue();
                            count++;
                        }
                    }
                }
                denoisedMatrix.at(i, j).setValue(count > 0 ? sum / count : 0);
            }
        }
        return denoisedMatrix;
    }

    static Matrix<T> medianDenoise(const Matrix<T>& imageMatrix, int kernelSize) {
        if (kernelSize % 2 == 0) {

            kernelSize++;
        }

        int rows = imageMatrix.getRows();
        int cols = imageMatrix.getCols();
        Matrix<T> denoisedMatrix(rows, cols, 0);
        int halfKernel = kernelSize / 2;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QVector<T> neighborhood;
                neighborhood.reserve(kernelSize * kernelSize);

                for (int ki = -halfKernel; ki <= halfKernel; ++ki) {
                    for (int kj = -halfKernel; kj <= halfKernel; ++kj) {
                        int ni = i + ki, nj = j + kj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            neighborhood.append(imageMatrix.at(ni, nj).getValue());
                        }
                    }
                }
                std::sort(neighborhood.begin(), neighborhood.end());
                T median = neighborhood[neighborhood.size() / 2];
                denoisedMatrix.at(i, j).setValue(median);
            }
        }
        return denoisedMatrix;
    }

    static Matrix<T> gaussianDenoise(const Matrix<T>& imageMatrix, int kernelSize, double sigma) {
        if (kernelSize % 2 == 0) {

            kernelSize++;
        }

        int rows = imageMatrix.getRows();
        int cols = imageMatrix.getCols();
        Matrix<T> denoisedMatrix(rows, cols, 0);
        QVector<QVector<double>> gaussianKernel(kernelSize, QVector<double>(kernelSize));
        int halfKernel = kernelSize / 2;
        double sum = 0.0;

        for (int x = -halfKernel; x <= halfKernel; ++x) {
            for (int y = -halfKernel; y <= halfKernel; ++y) {
                double value = std::exp(-(x * x + y * y) / (2 * sigma * sigma));
                gaussianKernel[x + halfKernel][y + halfKernel] = value;
                sum += value;
            }
        }

        for (int i = 0; i < kernelSize; ++i)
            for (int j = 0; j < kernelSize; ++j)
                gaussianKernel[i][j] /= sum;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double weightedSum = 0.0;
                for (int ki = -halfKernel; ki <= halfKernel; ++ki) {
                    for (int kj = -halfKernel; kj <= halfKernel; ++kj) {
                        int ni = i + ki, nj = j + kj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            weightedSum += gaussianKernel[ki + halfKernel][kj + halfKernel] * imageMatrix.at(ni, nj).getValue();
                        }
                    }
                }
                denoisedMatrix.at(i, j).setValue(static_cast<T>(weightedSum));
            }
        }
        return denoisedMatrix;
    }

    static Matrix<T> bilateralFilter(const Matrix<T>& imageMatrix, int diameter, double sigmaColor, double sigmaSpace) {
        if (diameter % 2 == 0) {

            diameter++;
        }

        int rows = imageMatrix.getRows();
        int cols = imageMatrix.getCols();
        Matrix<T> denoisedMatrix(rows, cols, 0);
        int halfDiameter = diameter / 2;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double pixelSum = 0.0;
                double weightSum = 0.0;

                for (int ki = -halfDiameter; ki <= halfDiameter; ++ki) {
                    for (int kj = -halfDiameter; kj <= halfDiameter; ++kj) {
                        int ni = i + ki, nj = j + kj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            double spatialDist = std::exp(-(ki * ki + kj * kj) / (2 * sigmaSpace * sigmaSpace));
                            double colorDist = imageMatrix.at(i, j).getValue() - imageMatrix.at(ni, nj).getValue();
                            double intensityDist = std::exp(-(colorDist * colorDist) / (2 * sigmaColor * sigmaColor));
                            double weight = spatialDist * intensityDist;

                            pixelSum += weight * imageMatrix.at(ni, nj).getValue();
                            weightSum += weight;
                        }
                    }
                }

                denoisedMatrix.at(i, j).setValue(weightSum > 0 ? static_cast<T>(pixelSum / weightSum) : 0);
            }
        }
        return denoisedMatrix;
    }

    static Matrix<T> noise2void(const Matrix<T>& imageMatrix) {
        Matrix<T> denoisedMatrix(imageMatrix);
        return denoisedMatrix;
    }
};

#endif
