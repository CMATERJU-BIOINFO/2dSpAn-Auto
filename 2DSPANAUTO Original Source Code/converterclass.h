#ifndef CONVERTER_H
#define CONVERTER_H

#include "image.h"
#include "matrix.h"

#include <QPixmap>

template <typename T>
class Converter {
public:
    static Matrix<T> imageToMatrix(const Image& image) {
        Matrix<T> matrix(image.getHeight(), image.getWidth(), Pixel());
        for (int y = 0; y < image.getHeight(); ++y) {
            for (int x = 0; x < image.getWidth(); ++x) {
                // Assign the Pixel directly to the Cell
                matrix.at(y, x).setValue(image.getPixel(x, y)); // Ensure setValue is used
            }
        }
        return matrix;
    }

    static Image matrixToImage(const Matrix<Pixel>& matrix) {
        Image image(matrix.getCols(), matrix.getRows());
        for (int y = 0; y < matrix.getRows(); ++y) {
            for (int x = 0; x < matrix.getCols(); ++x) {
                // Set the Pixel value from the Cell
                image.getPixel(x, y) = matrix.at(y, x).getValue(); // Assign the value properly
            }
        }
        return image;
    }
    static QPixmap imageToPixmap(const Image& image) {
        // Get the dimensions of the Image
        int width = image.getWidth(); // Assuming you have a method getWidth()
        int height = image.getHeight(); // Assuming you have a method getHeight()

        // Create a QImage with the same dimensions
        QImage qImage(width, height, QImage::Format_RGB32);

        // Fill the QImage with pixel data from the Image object
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Pixel pixel = image.getPixel(x, y); // Assuming you have a method getPixel(x, y)
                QColor color(pixel.getRed(), pixel.getGreen(), pixel.getBlue()); // Assuming Pixel has r, g, b members
                qImage.setPixel(x, y, color.rgb());
            }
        }

        // Convert QImage to QPixmap
        return QPixmap::fromImage(qImage);
    }
};


#endif // IMAGETOMATRIXCONVERTER_H
