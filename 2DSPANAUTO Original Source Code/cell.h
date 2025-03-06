#ifndef CELL_H
#define CELL_H

#include <cmath>
#include <QDebug>
#include <omp.h>
#define note qDebug()

template <typename T>
class Cell
{
private:
    int x;
    int y;
    T value;

public:

    Cell() : x(0), y(0), value(T()) {}
    Cell(int xCoord, int yCoord, T val) : x(xCoord), y(yCoord), value(val) {}

    int getX() const { return x; }
    void setX(int xCoord) { x = xCoord; }

    int getY() const { return y; }
    void setY(int yCoord) { y = yCoord; }

    inline T getValue() const { return value; }
    inline void setValue(T val) { value = val; }

    bool operator==(const Cell<T>& other) const {
        return (x == other.x && y == other.y && value == other.value);
    }


    bool operator!=(const Cell<T>& other) const {
        return !(*this == other);
    }


    inline Cell(const Cell<T>& other) {
        this->value = other.value;
        this->x = other.x;
        this->y = other.y;
    }


    inline Cell& operator=(const Cell<T>& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            value = other.value;
        }
        return *this;
    }
};

#endif
