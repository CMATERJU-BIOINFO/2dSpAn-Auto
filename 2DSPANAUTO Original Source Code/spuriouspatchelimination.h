#ifndef SPURIOUSPATCHELIMINATION_H
#define SPURIOUSPATCHELIMINATION_H

#include <QVector>
#include <QStack>
#include "matrix.h"
#include "cell.h"
#include "neighborhood.h"

template <typename T>
class SpuriousPatchElimination {
public:

    static void removeWhiteBlobs(Matrix<T>& binarised, T whiteBlobSize) {
        Matrix<bool> visited(binarised.getRows(), binarised.getCols(), false);
        Matrix<T> newBinary(binarised);
        for (int i = 0; i < binarised.getRows(); ++i) {
            for (int j = 0; j < binarised.getCols(); ++j) {

                if (!visited.at(i, j).getValue() && binarised.at(i, j).getValue() == static_cast<T>(255)) {
                    QVector<Cell<T>> blobCells = floodFill(newBinary, visited, i, j, true);


                    if (blobCells.size() < whiteBlobSize) {
                        for (auto& cell : blobCells) {
                            newBinary.at(cell.getX(), cell.getY()).setValue(static_cast<T>(0));
                        }
                    }
                }
            }
        }


        binarised = newBinary;
    }

    static void removeHoles(Matrix<T>& binarised, T blackHoleSize) {
        Matrix<bool> visited(binarised.getRows(), binarised.getCols(), false);
        Matrix<T> newBinary(binarised);
        for (int i = 0; i < binarised.getRows(); ++i) {
            for (int j = 0; j < binarised.getCols(); ++j) {

                if (!visited.at(i, j).getValue() && binarised.at(i, j).getValue() == static_cast<T>(0)) {
                    QVector<Cell<T>> blobCells = floodFill(newBinary, visited, i, j, false);


                    if (blobCells.size() < blackHoleSize) {
                        for (auto& cell : blobCells) {
                            newBinary.at(cell.getX(), cell.getY()).setValue(static_cast<T>(255));
                        }
                    }
                }
            }
        }


        binarised = newBinary;
    }

private:

    static QVector<Cell<T>> floodFill(Matrix<T>& binarised, Matrix<bool>& visited, int x, int y, bool isWhiteBlob) {
        QVector<Cell<T>> blobCells;
        QStack<QPair<int, int>> s;

        s.push(QPair<int, int>(x, y));
        visited.at(x, y).setValue(true);


        while (!s.isEmpty()) {
            QPair<int, int> current = s.pop();
            int cx = current.first;
            int cy = current.second;
            blobCells.push_back(binarised.at(cx, cy));


            Neighborhood<T> neighborhood(binarised, cx, cy);
            QVector<const Cell<T>*> neighbors = neighborhood.getAllNeighbors();

            for (auto neighbor : neighbors) {

                if (neighbor && !visited.at(neighbor->getX(), neighbor->getY()).getValue() &&
                    binarised.at(neighbor->getX(), neighbor->getY()).getValue() == (isWhiteBlob ? static_cast<T>(255) : static_cast<T>(0))) {
                    visited.at(neighbor->getX(), neighbor->getY()).setValue(true);
                    s.push(QPair<int, int>(neighbor->getX(), neighbor->getY()));
                }
            }
        }
        return blobCells;
    }
};

#endif
