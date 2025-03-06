#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "cell.h"
#include <QVector>
#include <bitset>

template <typename T>
class Matrix;

template <typename T>
class Neighborhood
{
private:
    const Matrix<T>& matrix;
    int x, y;

public:
    Neighborhood(const Matrix<T>& matrix, int x, int y) : matrix(matrix), x(x), y(y) {}


    const Cell<T>* top() const { return (y > 0) ? &matrix.at(x, y - 1) : nullptr; }
    const Cell<T>* bottom() const { return (y < matrix.getCols() - 1) ? &matrix.at(x, y + 1) : nullptr; }
    const Cell<T>* left() const { return (x > 0) ? &matrix.at(x - 1, y) : nullptr; }
    const Cell<T>* right() const { return (x < matrix.getRows() - 1) ? &matrix.at(x + 1, y) : nullptr; }
    const Cell<T>* topLeft() const { return (x > 0 && y > 0) ? &matrix.at(x - 1, y - 1) : nullptr; }
    const Cell<T>* topRight() const { return (x < matrix.getRows() - 1 && y > 0) ? &matrix.at(x + 1, y - 1) : nullptr; }
    const Cell<T>* bottomLeft() const { return (x > 0 && y < matrix.getCols() - 1) ? &matrix.at(x - 1, y + 1) : nullptr; }
    const Cell<T>* bottomRight() const { return (x < matrix.getRows() - 1 && y < matrix.getCols() - 1) ? &matrix.at(x + 1, y + 1) : nullptr; }


    QVector<const Cell<T>*> getAllNeighbors() const {
        return {topLeft(), top(), topRight(), right(), bottomRight(), bottom(), bottomLeft(), left()};
    }

    std::bitset<8> getNeighborsBinary() const {
        std::bitset<8> binary;
        binary[0] = (topLeft() != nullptr);
        binary[1] = (top() != nullptr);
        binary[2] = (topRight() != nullptr);
        binary[3] = (right() != nullptr);
        binary[4] = (bottomRight() != nullptr);
        binary[5] = (bottom() != nullptr);
        binary[6] = (bottomLeft() != nullptr);
        binary[7] = (left() != nullptr);
        return binary;
    }

    std::bitset<8> getNeighborsBinary(int val) const {
        std::bitset<8> binary;
        binary[0] = (topLeft() != nullptr && topLeft()->getValue() == val);
        binary[1] = (top() != nullptr && top()->getValue() == val);
        binary[2] = (topRight() != nullptr && topRight()->getValue() == val);
        binary[3] = (right() != nullptr && right()->getValue() == val);
        binary[4] = (bottomRight() != nullptr && bottomRight()->getValue() == val);
        binary[5] = (bottom() != nullptr && bottom()->getValue() == val);
        binary[6] = (bottomLeft() != nullptr && bottomLeft()->getValue() == val);
        binary[7] = (left() != nullptr && left()->getValue() == val);
        return binary;
    }
    std::bitset<8> getNeighborsBinaryNot(int val) const {
        std::bitset<8> binary;
        binary[0] = (topLeft() != nullptr && topLeft()->getValue() != val);
        binary[1] = (top() != nullptr && top()->getValue() !=val);
        binary[2] = (topRight() != nullptr && topRight()->getValue() !=val);
        binary[3] = (right() != nullptr && right()->getValue() !=val);
        binary[4] = (bottomRight() != nullptr && bottomRight()->getValue() !=val);
        binary[5] = (bottom() != nullptr && bottom()->getValue() !=val);
        binary[6] = (bottomLeft() != nullptr && bottomLeft()->getValue() !=val);
        binary[7] = (left() != nullptr && left()->getValue() != val);
        return binary;
    }
};

#endif
