#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QString>
#include <QImage>
#include <QColor>
#include <QFileDialog>
#include <QMessageBox>
#include "matrix.h"
#include "neighborhood.h"

template <typename T>
class ImageHandler {
public:
    ImageHandler() = default;


    bool loadImage(const QString &filePath, Matrix<T> &imageMatrix) {
        QImage img(filePath);
        if (img.isNull()) {
            qDebug() << "Failed to load image:" << filePath;
            return false;
        }
        img = img.scaled(img.width() * 0.75, img.height() * 0.75, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int rows = img.height();
        int cols = img.width();
        imageMatrix = Matrix<T>(rows + 6, cols + 6, static_cast<T>(0));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QColor pixelColor(img.pixel(j, i));
                int grayValue = qGray(pixelColor.red(), pixelColor.green(), pixelColor.blue());
                imageMatrix.at(i + 3, j + 3).setValue(static_cast<T>(grayValue));
            }
        }
        return true;
    }

    bool saveImage(const QString &filePath, const QImage &image, double scaleFactor = 4.0) {
        QSize newSize = image.size() * scaleFactor;
        QImage scaledImage = image.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if (scaledImage.save(filePath)) {
            return true;
        } else {
            qDebug() << "Failed to save image:" << filePath;
            return false;
        }
    }
};

#endif
