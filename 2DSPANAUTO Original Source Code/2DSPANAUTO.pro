QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# Enable OpenMP
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# INCLUDEPATH += C:/Users/User/Desktop/2DSPAN/2DSPANAUTO/eigen-3.4.0/eigen-3.4.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    savehandler.cpp

HEADERS += \
    advancedspinelabelling.h \
    analysis.h \
    binarization.h \
    cell.h \
    collisionimpact.h \
    dendriteextraction.h \
    denoising.h \
    distancetransform.h \
    imagehandler.h \
    label.h \
    mainwindow.h \
    matrix.h \
    neighborhood.h \
    savehandler.h \
    skeletoniserWrapper.h \
    skeletonizer.h \
    spinelabelling.h \
    spuriouspatchelimination.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
