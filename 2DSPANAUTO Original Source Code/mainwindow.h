#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "advancedspinelabelling.h"
#include "analysis.h"
#include "matrix.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
    void display(Matrix<int> mat,double zoom=1);
    void display(Matrix<int> bg, Matrix<int> overlay,double zoom=1);
    void delay(int milliseconds);
    void setProgressBar(int maxLimit);
    void updateProgressBar(int level);
    bool eventFilter(QObject *obj, QEvent *event) override;
    void setText(QString str);
    void displayN(Matrix<int> bg, Matrix<int> overlay, double zoom, const QMap<QPair<int, int>, int> &spineNumbers = QMap<QPair<int, int>, int>());
private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_actionLoad_Image_triggered();

    void on_otsuBinarise_clicked();

    void on_globalThresholdingBinarize_clicked();

    void on_btnMeanDenoise_clicked();

    void on_btnMedianDenoise_clicked();

    void on_btnGaussianDenoise_clicked();

    void on_btnBilateralFilter_clicked();

    void on_unetBinarize_clicked();

    void on_zoomBar_valueChanged(int value);

    void on_whiteBlobRemoval_clicked();

    void on_holeRemoval_clicked();

    void on_actionLoad_Image_Folder_triggered();

    void on_actionSave_Current_Image_triggered();

    void on_actionNext_Image_triggered();

    void on_primarySkel_clicked();

    void on_finalSkel_clicked();

    void on_btnComputeCI_clicked();

    void on_spotRemoval_clicked();

    void on_actionBinary_triggered();

    void on_actionOriginal_triggered();

    void on_btnNoise2Void_clicked();

    //SPINE LOCALISATION
    void on_dendriteExtraction_clicked();

    void on_completeSkel_clicked();

    void on_btnComputeDT_clicked();

    void on_rBtnPrimarySegmentation_clicked();

    void on_sbpSlider_valueChanged(int value);

    void on_twoMeansBinarize_clicked();

    void on_flip_clicked();

    void on_spineFiller_valueChanged(int value);

    void on_showCHP_clicked();

    void on_filopodiumSTD_valueChanged(int value);

    void on_hnjSlider_valueChanged(int value);

    void on_displayNetStats_clicked();

    void on_displayIndividualSpineInformation_clicked();

    void on_useCurrentImage_clicked();

    void on_displaySpineNumber_clicked();

    // void on_pushButton_clicked();

    // void on_number_valueChanged(int arg1);

    void on_browse_clicked();

    void on_saveNet_clicked();

    void on_saveAllSpines_clicked();

    void on_BreakLoop_clicked();

    void on_selectPoints_clicked();

    void on_setManualDE_clicked();

    void on_performDefaultSpineLocalisation_clicked();

    void on_resolution_valueChanged(double arg1);

    void on_actionAuto_triggered();

private:
    double resolution=1.0;
    bool statComputed=false;
    QPoint currCoordinate;
    int dendriteLength=0;
    double spineDensity=0;
    Ui::MainWindow *ui;
    QStringList imagePaths;
    int currentImageIndex = -1;
    Matrix<int> image,
        input,
        currDenoised,
        currBinarised,
        currDisplay,
        currOverlay,
        currDT,
        currCIT/*for thresholded CI*/,
        currCI,
        currPrimarySkel,
        currFinalSkel,
        currDendrite,
        currDendriteEndsPruned,
        currCombinedSkel;
    Matrix<int> key;
    SpineLabel<int> labelskel;
    SpineMass<int> labelledCHP;
    QVector<QPoint> filo,stubby,mushroom;
    QHash<QPoint, QSet<QPoint>> mapping;
    QVector<SpineStats> table;
    double zoomFactor=1.0;
    void formTable();
    QVector<QPoint> bresenham(QPoint p1,QPoint p2);
    bool clickedAuto=false;
    bool usedDefaultParametersButton=false;
    QString
        binarizationLog,
        denoisingLog

        ;
    void processSingleImage(Matrix<int> &imageMatrix, const QString &imagePath, const QString &saveDir);
};

#endif
