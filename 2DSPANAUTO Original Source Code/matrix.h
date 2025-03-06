#ifndef MATRIX_H
#define MATRIX_H

#include "cell.h"
#include "neighborhood.h"
#include <QVector>

template <typename T>
class Matrix
{
private:
    int rows, cols;
    QVector<QVector<Cell<T>>> grid;

public:

    Matrix() : rows(0), cols(0), grid(QVector<QVector<Cell<T>>>() ) {}


    Matrix(int rows, int cols, T initialValue)
        : rows(rows), cols(cols), grid(rows, QVector<Cell<T>>(cols, Cell<T>(0, 0, initialValue)))
    {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = Cell<T>(i, j, initialValue);
            }
        }
    }


    inline Matrix(const Matrix<T>& other)
        : rows(other.rows), cols(other.cols), grid(other.grid)
    {
    }


    inline Matrix<T>& operator=(const Matrix<T>& other)
    {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            grid = other.grid;
        }
        return *this;
    }


    inline Matrix<T> operator*(const Matrix<T>& other) const {
        // Check if matrices have the same dimensions
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for element-wise multiplication");
        }

        // Create a new matrix to store the result
        Matrix<T> result(rows, cols, T());

        // Perform element-wise multiplication
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Multiply the values of corresponding cells
                result.at(i, j).setValue(at(i, j).getValue() * other.at(i, j).getValue());
            }
        }

        return result;
    }

    inline Cell<T>& at(int x, int y) {/*
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            throw std::out_of_range("Matrix indices out of bounds");
        }*/
        return grid[x][y];
    }

    inline const Cell<T>& at(int x, int y) const {/*
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            throw std::out_of_range("Matrix indices out of bounds");
        }*/
        return grid[x][y];
    }


    inline Neighborhood<T> getNeighborhood(int x, int y) const {/*
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            throw std::out_of_range("Neighborhood indices out of bounds");
        }*/
        return Neighborhood<T>(*this, x, y);
    }


    int getRows() const { return rows; }
    int getCols() const { return cols; }


    bool isEmpty() const {
        return rows == 0 || cols == 0;
    }


    void clear() {
        rows = 0;
        cols = 0;
        grid.clear();
    }
};

#endif
