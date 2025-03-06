#include "mainwindow.h"
#include "advancedspinelabelling.h"
#include "analysis.h"
#include "qpainter.h"
#include "savehandler.h"
#include "skeletonizer.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QImage>
#include <QMessageBox>
#include <QStack>
#include <QMouseEvent>
#include "distancetransform.h"
#include "binarization.h"
#include "denoising.h"
#include "imagehandler.h"
#include "spuriouspatchelimination.h"
#include "collisionimpact.h"
#include "label.h"
#include "dendriteextraction.h"
#include "spinelabelling.h"

#define wait delay(1000);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    zoomFactor(1.0) {
    ui->setupUi(this);
    ui->lblImage->installEventFilter(this);
    ui->lblImage->setMouseTracking(true);
}



MainWindow::~MainWindow() {
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief UTILITY FUNCTIONS
///
void MainWindow::display(Matrix<int> mat, double zoom) {
    int rows = mat.getRows();
    int cols = mat.getCols();
    QImage img(cols, rows, QImage::Format_Grayscale8);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int grayValue = mat.at(i, j).getValue();
            img.setPixel(j, i, qRgb(grayValue, grayValue, grayValue));
        }
    }
    QPixmap p=QPixmap::fromImage(img);
    p=p.scaled(rows*zoom,cols*zoom,Qt::KeepAspectRatioByExpanding);
    ui->lblImage->setPixmap(p);
    currDisplay = currBinarised.isEmpty()?image:currBinarised;
    currOverlay = mat;
}

void MainWindow::display(Matrix<int> bg, Matrix<int> overlay, double zoom) {
    int rows = bg.getRows();
    int cols = bg.getCols();
    QImage image(cols, rows, QImage::Format_RGB888);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int bgVal = bg.at(i, j).getValue();
            int overlayVal = overlay.at(i, j).getValue();
            int grayValue = bgVal;
            image.setPixel(j, i, qRgb(grayValue, grayValue, grayValue));
            switch (overlayVal) {
            case 255:
            case __dendrite__:
                image.setPixel(j, i, qRgb(0, 255, 0));
                break;
            case __ep__:
            case __de__:
            case __sse__:
                image.setPixel(j, i, qRgb(255, 255, 0));
                break;
            case __jp__:
                image.setPixel(j, i, qRgb(0, 0, 255));
                break;
            case __spine__:
                image.setPixel(j,i, qRgb(255,0,0));
                break;
            case __sbp__:
                image.setPixel(j,i, qRgb(0,0,127));
                break;
            case __spinebase__:
                image.setPixel(j,i,qRgb(127,127,0));
                break;
            case __spinebaseline__:
                image.setPixel(j,i,qRgb(255,127,0));
                break;
            case __spineboundary__:
                image.setPixel(j,i,qRgb(127,255,0));
                break;
            case __ssj__:
                image.setPixel(j,i, qRgb(127,0,127));
                break;
            case __ddj__:
                image.setPixel(j,i, qRgb(255,0,255));
                break;
            case __di__:
                image.setPixel(j,i, qRgb(255,127,255));
                break;
            case __chp__:
                image.setPixel(j,i, qRgb(0,127,255));
                break;
            case __hnj__:
                image.setPixel(j,i, qRgb(127,0,255));
                break;
            case __filopodium__:
                image.setPixel(j,i, qRgba(255, 255, 127,25));
                break;
            case __stubby__:
                image.setPixel(j,i, qRgba(255, 127, 127,25));
                break;
            case __mushroom__:
                image.setPixel(j,i, qRgba(127, 255, 255,25));
                break;
            default:
                break;
            }

        }
    }
    QPixmap p=QPixmap::fromImage(image);
    p=p.scaled(rows*zoom,cols*zoom,Qt::KeepAspectRatioByExpanding);
    ui->lblImage->setPixmap(p);
    currDisplay = bg;
    currOverlay = overlay;
}

void MainWindow::on_zoomBar_valueChanged(int value)
{
    zoomFactor = value / 100.0;

    int newWidth = static_cast<int>(currDisplay.getCols() * zoomFactor);
    int newHeight = static_cast<int>(currDisplay.getRows() * zoomFactor);


    QImage image(newWidth, newHeight, QImage::Format_RGB888);

    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {


            int originalX = static_cast<int>(j / zoomFactor);
            int originalY = static_cast<int>(i / zoomFactor);

            if (originalX < currDisplay.getCols() && originalY < currDisplay.getRows()) {

                int bgVal = currDisplay.at(originalY, originalX).getValue();


                image.setPixel(j, i, qRgb(bgVal, bgVal, bgVal));


                if (!currOverlay.isEmpty()) {
                    int overlayVal = currOverlay.at(originalY, originalX).getValue();
                    switch (overlayVal) {
                    case 255:
                    case __dendrite__:
                        image.setPixel(j, i, qRgb(0, 255, 0));
                        break;
                    case __ep__:
                    case __de__:
                    case __sse__:
                        image.setPixel(j, i, qRgb(255, 255, 0));
                        break;
                    case __jp__:
                        image.setPixel(j, i, qRgb(0, 0, 255));
                        break;
                    case __spine__:
                        image.setPixel(j,i, qRgb(255,0,0));
                        break;
                    case __sbp__:
                        image.setPixel(j,i, qRgb(0,0,127));
                        break;
                    case __spinebase__:
                        image.setPixel(j,i,qRgb(127,127,0));
                        break;
                    case __spinebaseline__:
                        image.setPixel(j,i,qRgb(255,127,0));
                        break;
                    case __spineboundary__:
                        image.setPixel(j,i,qRgb(127,255,0));
                        break;
                    case __ssj__:
                        image.setPixel(j,i, qRgb(127,0,127));
                        break;
                    case __ddj__:
                        image.setPixel(j,i, qRgb(255,0,255));
                        break;
                    case __di__:
                        image.setPixel(j,i, qRgb(255,127,255));
                        break;
                    case __chp__:
                        image.setPixel(j,i, qRgb(0,127,255));
                        break;
                    case __hnj__:
                        image.setPixel(j,i, qRgb(127,0,255));
                        break;
                    case __filopodium__:
                        image.setPixel(j,i, qRgba(255, 255, 127,25));
                        break;
                    case __stubby__:
                        image.setPixel(j,i, qRgba(255, 127, 127,25));
                        break;
                    case __mushroom__:
                        image.setPixel(j,i, qRgba(127, 255, 255,25));
                        break;
                    default:
                        break;
                    }

                }
            }
        }
    }


    ui->lblImage->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_actionBinary_triggered()
{
    display(currBinarised,currOverlay,zoomFactor);
}

void MainWindow::on_actionOriginal_triggered()
{
    display(image,currOverlay,zoomFactor);
}

void MainWindow::setProgressBar(int maxLimit)
{
    ui->progressBar->setMaximum(maxLimit);
}

void MainWindow::updateProgressBar(int level)
{
    ui->progressBar->setValue(level);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lblImage && event->type() == QEvent::MouseMove) {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x() /zoomFactor;
        int y = cursor->pos().y() /zoomFactor;

        QString labelText = "X: " + QString::number(y) + " ,Y: " + QString::number(x);

        ui->coordinates->setText(labelText);
        if(statComputed){
            setText(QString::number(key.at(y,x).getValue()));
        }
        return true;
    }
    if (obj == ui->lblImage && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *cursor = static_cast<QMouseEvent*>(event);
        int x = cursor->pos().x() /zoomFactor;
        int y = cursor->pos().y() /zoomFactor;
        currCoordinate=QPoint(y,x);
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setText(QString str)
{
    ui->spineNum->setText(str);
}

void MainWindow::delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::on_actionLoad_Image_Folder_triggered() {
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Select Image Folder"));
    if (folderPath.isEmpty()) return;

    QDir directory(folderPath);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    QStringList files = directory.entryList(filters, QDir::Files);

    imagePaths.clear();
    for (const QString &fileName : files) {
        imagePaths.append(directory.absoluteFilePath(fileName));
    }

    if (imagePaths.isEmpty()) {
        QMessageBox::warning(this, tr("Load Images"), tr("No images found in the selected folder."));
    } else {
        QMessageBox::information(this, tr("Load Images"), tr("%1 images loaded.").arg(imagePaths.size()));
        currentImageIndex = -1;
    }
}

void MainWindow::on_actionAuto_triggered() {
    if (imagePaths.isEmpty()) {
        QMessageBox::warning(this, "Error", "No images loaded. Please load a folder first.");
        return;
    }

    QString saveDir = ui->folderPath->text();
    if (saveDir.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a save directory first.");
        on_browse_clicked();
        saveDir = ui->folderPath->text();
        if (saveDir.isEmpty()) return;
    }

    int startIdx = currentImageIndex + 1;
    if (startIdx >= imagePaths.size()) startIdx = 0;

    setProgressBar(imagePaths.size() - startIdx);

    // Disable UI elements during batch processing
    setEnabled(false);
    QApplication::processEvents();

    for (int i = startIdx; i < imagePaths.size(); ++i) {
        updateProgressBar(i - startIdx);
        QString imagePath = imagePaths[i];

        // Load image
        Matrix<int> imageMatrix;
        ImageHandler<int> imageHandler;
        if (!imageHandler.loadImage(imagePath, imageMatrix)) {
            QMessageBox::warning(this, tr("Load Image"), tr("Failed to load image: ") + imagePath);
            continue;
        }

        // Process image
        processSingleImage(imageMatrix, imagePath, saveDir);

        // Update current index
        currentImageIndex = i;
    }

    setEnabled(true);
    QMessageBox::information(this, "Complete", "Batch processing finished!");
    updateProgressBar(0);
}

void MainWindow::processSingleImage(Matrix<int>& imageMatrix, const QString& imagePath, const QString& saveDir) {
    // Denoising
    Matrix<int> denoised;
    if (denoisingLog == "Mean") {
        int kernelSize = ui->spnMean->value();
        denoised = Denoising<int>::meanDenoise(imageMatrix, kernelSize);
    } else if (denoisingLog == "Median") {
        int kernelSize = ui->spnMedian->value();
        denoised = Denoising<int>::medianDenoise(imageMatrix, kernelSize);
    } else if (denoisingLog == "Gaussian Denoise") {
        int kernelSize = ui->spnGaussian->value();
        double sigma = ui->spnSigma->value();
        denoised = Denoising<int>::gaussianDenoise(imageMatrix, kernelSize, sigma);
    } else if (denoisingLog == "Bilateral Filter") {
        int diameter = ui->spnDiameter->value();
        double sigmaColor = ui->spnSigmaColor->value();
        double sigmaSpace = ui->spnSigmaSpace->value();
        denoised = Denoising<int>::bilateralFilter(imageMatrix, diameter, sigmaColor, sigmaSpace);
    } else {
        denoised = imageMatrix;
    }

    // Binarization
    Matrix<int> binarized;
    if (binarizationLog == "OTSU") {
        binarized = Binarization<int>::otsuBinarize(denoised);
    } else if (binarizationLog == "Global Thresholding") {
        int threshold = ui->spnThreshold->value();
        binarized = Binarization<int>::globalThresholdBinarize(denoised, threshold);
    } else if (binarizationLog == "Two Means") {
        binarized = Binarization<int>::clusteringBinarize(denoised);
    } else if (binarizationLog == "UNET") {
        binarized = Binarization<int>::unetBinarize(denoised);
    } else {
        binarized = denoised;
    }

    // Spot removal
    SpuriousPatchElimination<int>::removeHoles(binarized, ui->blackHoleSize->value());
    SpuriousPatchElimination<int>::removeWhiteBlobs(binarized, ui->whiteBlobSize->value());

    // Compute DT
    Matrix<int> dt = DistanceTransform<int>::compute(binarized);

    // Compute CI
    Matrix<int> CI(dt.getRows(), dt.getCols(), 0);
    CollisionImpact<int> collisionImpact(dt, binarized);
    collisionImpact.computeCI(CI);
    Matrix<int> CIT = CI;
    int ciThreshold = ui->horizontalSlider->value();
    for(int y = 0; y < CIT.getRows(); y++) {
        for(int x = 0; x < CIT.getCols(); x++) {
            if(CIT.at(y, x).getValue() < ciThreshold)
                CIT.at(y, x).setValue(0);
        }
    }

    // Skeletonization
    Skeletonizer<int> skeletonizer(dt, CIT, this);
    Matrix<int> primarySkel = skeletonizer.primarySkeletonization();
    Matrix<int> finalSkel = skeletonizer.finalSkeletonization(primarySkel);

    // Dendrite extraction
    DendriteExtraction<int> dendriteExtractor(this,finalSkel, dt, binarized, zoomFactor);
    dendriteExtractor.extractDendrite(ui->dbSpnAlpha->value(), ui->spnPruningIter->value());
    Matrix<int> dendriteSkel = dendriteExtractor.skeleton();

    // Spine labeling and analysis
    Matrix<int> combinedSkel = SpineLabelling<int>::primarySegmentation(finalSkel, dendriteSkel);
    combinedSkel = SpineLabelling<int>::finalSegmentation(combinedSkel);

    SpineLabel<int> spineLabel(combinedSkel, dt, binarized, imageMatrix);
    spineLabel.markSBP(ui->sbpSlider->value() / 100.0);
    spineLabel.markSpine(ui->spineFiller->value() / 100.0);

    SpineMass<int> spineCHP(imageMatrix, spineLabel.markingSBP, spineLabel.getMapping());
    spineCHP.findCHP(ui->filopodiumSTD->value() / 100.0);
    spineCHP.findHNJ(ui->hnjSlider->value() / 100.0);
    //Compute Stats

    auto sbpChp=spineCHP.getSbp_to_chp();
    auto sbpHnj=spineCHP.getSbp_to_hnj();
    auto sbpSpineSkel=spineCHP.getSbp_to_reachableSkelPointsFromSBP();
    auto sbpSpineDT=spineCHP.getSbp_SpineMassDT();
    auto map=spineLabel.getMapping();
    key.clear();
    key=Matrix<int>(currBinarised.getRows(),currBinarised.getCols(),0);
    for(auto it=map.begin();it!=map.end();it++){
        QPoint sbp=it.key();
        auto points=it.value();
        mapping[sbp]=points;
    }
    auto filoSbp=labelledCHP.getFiloSBP();

    Analyse<int> anal(sbpChp,sbpHnj,sbpSpineSkel,sbpSpineDT,map,filoSbp,currDT);
    QVector<SpineStats> dataset=anal.analyse();
    key=anal.getKeys(currBinarised.getRows(),currBinarised.getCols());



    QFileInfo fileInfo(imagePath);
    QString baseName = fileInfo.completeBaseName();
    SaveHandler handler(dataset, resolution);
    QString netPath = QDir(saveDir).filePath(baseName + "_net.csv");
    QString spinesPath = QDir(saveDir).filePath(baseName + "_spines.csv");

    handler.saveNet(netPath);
    handler.saveAllIndividual(spinesPath);
}

void MainWindow::on_actionNext_Image_triggered() {
    /////////////////////
    /// Clearing all previous Matrices
    image.clear(),
        input.clear(),
        currDenoised.clear(),
        currBinarised.clear(),
        currDisplay.clear(),
        currOverlay.clear(),
        currDT.clear(),
        currCIT.clear()/*for thresholded CI*/,
        currCI.clear(),
        currPrimarySkel.clear(),
        currFinalSkel.clear(),
        currDendrite.clear(),
        currDendriteEndsPruned.clear(),
        currCombinedSkel.clear();
    /// /////////////////////
    ///
    if (imagePaths.isEmpty()) {
        QMessageBox::warning(this, tr("Next Image"), tr("No images loaded. Please load a folder first."));
        return;
    }

    currentImageIndex = (currentImageIndex + 1) % imagePaths.size();
    QString nextImagePath = imagePaths[currentImageIndex];


    qDebug() << "Attempting to load image from path:" << nextImagePath;

    Matrix<int> imageMatrix;
    ImageHandler<int> imageHandler;

    if (!imageHandler.loadImage(nextImagePath, imageMatrix)) {
        QMessageBox::warning(this, tr("Load Image"), tr("Failed to load image: ") + nextImagePath);
        return;
    }
    ui->filename->setText(nextImagePath);

    display(imageMatrix,zoomFactor);
    input = image = imageMatrix;

}

void MainWindow::on_actionSave_Current_Image_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"), "", tr("Images (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty()) {
        ImageHandler<int> imageHandler;
        if (!imageHandler.saveImage(fileName, ui->lblImage->pixmap().toImage())) {
            QMessageBox::warning(this, tr("Save Image"), tr("Failed to save image."));
        }
    }
}

void MainWindow::on_actionLoad_Image_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Images (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty()) {
        ImageHandler<int> imageHandler;
        Matrix<int> imageMatrix;

        if (!imageHandler.loadImage(fileName, imageMatrix)) {
            QMessageBox::warning(this, tr("Load Image"), tr("Failed to load image."));
            return;
        }
        ui->filename->setText(fileName);
        display(imageMatrix,zoomFactor);
        input = image = imageMatrix;

    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief DENOISING IMAGE
void MainWindow::on_useCurrentImage_clicked()
{
    input=currDenoised;
}
void MainWindow::on_btnMeanDenoise_clicked() {
    int kernelSize = ui->spnMean->value();
    Matrix<int> denoisedMatrix = Denoising<int>::meanDenoise(image, kernelSize);
    display(denoisedMatrix,zoomFactor);
    currDenoised = denoisedMatrix;
    denoisingLog="Mean";
}

void MainWindow::on_btnMedianDenoise_clicked() {
    int kernelSize = ui->spnMedian->value();
    Matrix<int> denoisedMatrix = Denoising<int>::medianDenoise(image, kernelSize);
    display(denoisedMatrix,zoomFactor);
    currDenoised = denoisedMatrix;
    denoisingLog="Median";
}

void MainWindow::on_btnGaussianDenoise_clicked() {
    int kernelSize = ui->spnGaussian->value();
    double sigma = ui->spnSigma->value();
    Matrix<int> denoisedMatrix = Denoising<int>::gaussianDenoise(image, kernelSize, sigma);
    display(denoisedMatrix,zoomFactor);
    currDenoised = denoisedMatrix;
    denoisingLog="Gaussian Denoise";
}

void MainWindow::on_btnBilateralFilter_clicked() {
    int diameter = ui->spnDiameter->value();
    double sigmaColor = ui->spnSigmaColor->value();
    double sigmaSpace = ui->spnSigmaSpace->value();

    Matrix<int> denoisedMatrix = Denoising<int>::bilateralFilter(image, diameter, sigmaColor, sigmaSpace);

    display(denoisedMatrix,zoomFactor);
    currDenoised = denoisedMatrix;
    denoisingLog="Bilateral Filter";
}

void MainWindow::on_btnNoise2Void_clicked()
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief BINARIZATION MODULE
///


void MainWindow::on_otsuBinarise_clicked() {
    Matrix<int> mat=input;
    Matrix<int> binarizedMatrix = Binarization<int>::otsuBinarize(mat);
    display(binarizedMatrix,zoomFactor);
    currBinarised=binarizedMatrix;
    on_spotRemoval_clicked();
    binarizationLog="OTSU";
}
void MainWindow::on_globalThresholdingBinarize_clicked() {
    int threshold = ui->spnThreshold->value();
    Matrix<int> mat=input;
    Matrix<int> binarizedMatrix = Binarization<int>::globalThresholdBinarize(mat, threshold);
    display(binarizedMatrix,zoomFactor);
    currBinarised=binarizedMatrix;
    on_spotRemoval_clicked();
    binarizationLog="Global Thresholding";
}

void MainWindow::on_twoMeansBinarize_clicked()
{
    Matrix<int> mat=input;
    Matrix<int> binarizedMatrix = Binarization<int>::clusteringBinarize(mat);
    display(binarizedMatrix,zoomFactor);
    currBinarised=binarizedMatrix;
    on_spotRemoval_clicked();
    binarizationLog="Two Means";
}
void MainWindow::on_flip_clicked()
{
    int r=currBinarised.getRows(),c=currBinarised.getCols();
    for (int i = 0; i < r-1; ++i) {
        for (int j = 0; j < c-1; ++j) {
            int val=currBinarised.at(i,j).getValue();
            currBinarised.at(i,j).setValue(255-val);
        }
    }
    display(currBinarised,zoomFactor);
}

void MainWindow::on_unetBinarize_clicked()
{
    Matrix<int> mat=input;
    Matrix<int> binarizedMatrix = Binarization<int>::unetBinarize(mat);
    display(binarizedMatrix,zoomFactor);
    currBinarised=binarizedMatrix;
    binarizationLog="UNET";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief SPOT REMOVAL
///
void MainWindow::on_whiteBlobRemoval_clicked() {

    int whiteBlobSize = ui->whiteBlobSize->value();
    SpuriousPatchElimination<int>::removeWhiteBlobs(currBinarised, whiteBlobSize);
    display(currBinarised,zoomFactor);
}

void MainWindow::on_holeRemoval_clicked() {

    int blackHoleSize = ui->blackHoleSize->value();
    SpuriousPatchElimination<int>::removeHoles(currBinarised, blackHoleSize);
    display(currBinarised,zoomFactor);
}

void MainWindow::on_spotRemoval_clicked()
{
    on_holeRemoval_clicked();
    on_whiteBlobRemoval_clicked();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief DISTANCE TRANSFORM AND COLLISION IMPACT
///
///
void MainWindow::on_btnComputeDT_clicked() {
    Matrix<int> dt;
    dt= DistanceTransform<int>::compute/*Euclidean*/(currBinarised);
    // for (int i = 0; i < dt.getRows(); ++i) {
    //     for (int j = 0; j < dt.getCols(); ++j) {
    //         dt.at(i,j).setValue(sqrt(dt.at(i,j).getValue()));
    //     }
    // }
    // if(ui->rbnGray->isChecked())
    //     dt = DistanceTransform<int>::computeFuzzy(input);
    display(dt,zoomFactor);
    currDT = dt;
}

void MainWindow::on_btnComputeCI_clicked()
{
    on_btnComputeDT_clicked();
    int r = currDT.getRows(), c = currDT.getCols();
    Matrix<int> bin(image), CI(r, c, 0);
    CollisionImpact<int> collisionImpact(currDT, bin);
    collisionImpact.computeCI(CI);
    currCI = currCIT = CI;
    display(currCI,zoomFactor);
    on_horizontalSlider_valueChanged(ui->horizontalSlider->value());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(!currCI.isEmpty()){
        int r = currDT.getRows(), c = currDT.getCols();
        currCIT=currCI;
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(currCI.at(i,j).getValue()<value)
                    currCIT.at(i,j).setValue(0);
            }
        }
        display(currCIT,zoomFactor);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief SKELETONIZATION MODULE
///
void MainWindow::on_primarySkel_clicked() {
    Skeletonizer<int> skeletonizer(currDT, currCIT,this);
    Matrix<int> skel = skeletonizer.primarySkeletonization();
    display(currBinarised,skel,zoomFactor);
    currPrimarySkel=skel;
}

void MainWindow::on_finalSkel_clicked()
{
    Skeletonizer<int> skeletonizer(currDT, currCIT,this);
    Matrix<int> skel = skeletonizer.finalSkeletonization(currPrimarySkel);
    display(currBinarised,skel,zoomFactor);
    currFinalSkel=skel;
}
void MainWindow::on_completeSkel_clicked()
{
    on_primarySkel_clicked();
    on_finalSkel_clicked();
}
void MainWindow::on_BreakLoop_clicked()
{
    QListWidget* list_of_cut_Points = ui->loopCutList;
    //parse the list of coordinates and insert in set
    QSet<QPoint> set_of_cut_points;
    QSet<QPoint> cutLine;

    // Parse all points from the list widget
    for(int i = 0; i < list_of_cut_Points->count(); i++) {
        QString pointStr = list_of_cut_Points->item(i)->text();
        // Remove parentheses and split by comma
        pointStr = pointStr.mid(1, pointStr.length() - 2);
        QStringList coords = pointStr.split(", ");
        if(coords.size() == 2) {
            set_of_cut_points.insert(QPoint(coords[0].toInt(), coords[1].toInt()));
        }
    }

    // Convert set to list for sequential access
    QList<QPoint> points = set_of_cut_points.values();

    // Generate lines between consecutive points
    for(int i = 0; i < points.size() - 1; i++) {
        QVector<QPoint> linePoints = bresenham(points[i], points[i + 1]);
        for(const QPoint& pt : linePoints) {
            cutLine.insert(pt);
        }
    }

    // If there are at least 2 points, connect the last point to the first point
    if(points.size() >= 2) {
        QVector<QPoint> linePoints = bresenham(points.last(), points.first());
        for(const QPoint& pt : linePoints) {
            cutLine.insert(pt);
        }
    }

    // Clear the skeleton at cut points
    foreach(auto pt, cutLine) {
        currFinalSkel.at(pt.x(), pt.y()).setValue(0);
    }
    display(currBinarised,currFinalSkel,zoomFactor);
    ui->loopCutList->clear();
}

void MainWindow::on_selectPoints_clicked()
{
    ui->loopCutList->addItem(QString("(%1, %2)").arg(currCoordinate.x()).arg(currCoordinate.y()));
}

QVector<QPoint> MainWindow::bresenham(QPoint p1, QPoint p2)
{
    QVector<QPoint> points;

    int x1 = p1.x(), y1 = p1.y();
    int x2 = p2.x(), y2 = p2.y();

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(true) {
        points.append(QPoint(x1, y1));

        if(x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return points;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief DENDRITE EXTRACTION
///

void MainWindow::on_setManualDE_clicked()
{
    QPoint curr=currCoordinate;
    int neighborsize=7;
    QSet<QPoint> skel;
    for (int i = qMax(0,curr.x()-neighborsize); i < qMin(curr.x()+neighborsize,currFinalSkel.getRows()); ++i) {
        for (int j = qMax(0,curr.y()-neighborsize); j < qMin(curr.y()+neighborsize,currFinalSkel.getRows()); ++j) {
            if(currFinalSkel.at(i,j).getValue()!=0)
                skel.insert(QPoint(i,j));
        }
    }
    int min=INT_MAX;
    foreach (auto pt, skel) {
        if((pt-currCoordinate).manhattanLength()<min)
        {
            min=(pt-currCoordinate).manhattanLength();
            curr=pt;
        }
    }
    currFinalSkel.at(curr.x(),curr.y()).setValue(__de__);
    display(currBinarised,currFinalSkel,zoomFactor);
}

int click=0;
void MainWindow::on_dendriteExtraction_clicked()
{
    if(click==0){
        DendriteExtraction<int> sl(this,currFinalSkel,currDT,currBinarised,zoomFactor);
        int iter=ui->spnPruningIter->value();
        double alpha=ui->dbSpnAlpha->value();
        sl.extractDendrite(alpha,iter);
        Matrix<int> labelledSkel=sl.skeleton();
        display(currDisplay,labelledSkel,zoomFactor);
        currDendrite=labelledSkel;
        currDendriteEndsPruned=sl.getSkel2();
        display(currDisplay,currDendriteEndsPruned,zoomFactor);
    }
    else if(click!=0){
        DendriteExtraction<int> sl(this,currDendriteEndsPruned,currDT,currBinarised,zoomFactor);
        int iter=ui->spnPruningIter->value();
        double alpha=ui->dbSpnAlpha->value();
        sl.extractDendrite(alpha,iter);
        Matrix<int> labelledSkel=sl.skeleton();
        display(currDisplay,labelledSkel,zoomFactor);
        currDendrite=labelledSkel;
        currDendriteEndsPruned=sl.getSkel2();
        display(currDisplay,currDendriteEndsPruned,zoomFactor);
    }
    click++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief PRIMARY SEGMENTATION
///
void MainWindow::on_rBtnPrimarySegmentation_clicked()
{
    Matrix<int> combinedSkelPrimary=SpineLabelling<int>::primarySegmentation(currFinalSkel,currDendrite);
    display(currDisplay,combinedSkelPrimary,zoomFactor);
    currCombinedSkel=combinedSkelPrimary;
    Matrix<int> combinedSkelFinal=SpineLabelling<int>::finalSegmentation(currCombinedSkel);
    display(currDisplay,combinedSkelFinal,zoomFactor);
    currPrimarySkel=combinedSkelFinal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_sbpSlider_valueChanged(int value)
{
    currCombinedSkel=currPrimarySkel;
    double alpha=value/100.0;
    labelskel=SpineLabel<int>(currCombinedSkel,currDT,currBinarised,image);
    labelskel.markSBP(alpha);
    display(currDisplay,labelskel.markingSBP,zoomFactor);
}


void MainWindow::on_spineFiller_valueChanged(int value)
{
    double beta=value/100.0;
    labelskel.markSpine(beta);
    display(currDisplay,labelskel.markingSpine,zoomFactor);
}

void MainWindow::on_showCHP_clicked()
{
    mapping=labelskel.getMapping();
    SpineMass<int> spineCHP(image,labelskel.markingSBP,mapping);
    spineCHP.findCHP();
    display(currDisplay,spineCHP.markingCHP,zoomFactor);
    labelledCHP=spineCHP;
}

void MainWindow::on_filopodiumSTD_valueChanged(int value)
{
    auto mapping=labelskel.getMapping();
    SpineMass<int> spineCHP(image,labelskel.markingSBP,mapping);
    spineCHP.findCHP(value/100.0);
    display(currDisplay,spineCHP.markingCHP,zoomFactor);
    labelledCHP=spineCHP;
}


void MainWindow::on_hnjSlider_valueChanged(int value)
{
    labelledCHP.findHNJ(value/100.0);
    display(currDisplay,labelledCHP.markingHNJ,zoomFactor);
}

void MainWindow::on_performDefaultSpineLocalisation_clicked()
{
    usedDefaultParametersButton=true;
    on_dendriteExtraction_clicked();
    on_rBtnPrimarySegmentation_clicked();
    on_sbpSlider_valueChanged(40);
    on_spineFiller_valueChanged(130);
    on_showCHP_clicked();
    on_filopodiumSTD_valueChanged(10);
    on_hnjSlider_valueChanged(100);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MORPHOANALYSER
///
void MainWindow::formTable(){
    auto sbpChp=labelledCHP.getSbp_to_chp();
    auto sbpHnj=labelledCHP.getSbp_to_hnj();
    auto sbpSpineSkel=labelledCHP.getSbp_to_reachableSkelPointsFromSBP();
    auto sbpSpineDT=labelledCHP.getSbp_SpineMassDT();
    auto map=labelskel.getMapping();
    key.clear();
    key=Matrix<int>(currBinarised.getRows(),currBinarised.getCols(),0);
    for(auto it=map.begin();it!=map.end();it++){
        QPoint sbp=it.key();
        auto points=it.value();
        mapping[sbp]=points;
    }
    auto filoSbp=labelledCHP.getFiloSBP();

    Analyse<int> anal(sbpChp,sbpHnj,sbpSpineSkel,sbpSpineDT,map,filoSbp,currDT);
    table=anal.analyse();
    key=anal.getKeys(currBinarised.getRows(),currBinarised.getCols());

}


void MainWindow::on_displayNetStats_clicked()
{
    // Form the table of spine statistics
    formTable();

    statComputed=true;
    Matrix<int> classified(currCombinedSkel);
    // Separate spines by type
    QVector<SpineStats> filoSpines, stubbySpines, mushroomSpines;
    for (const auto& stat : table) {
        switch (stat.type) {
        case __filopodium__:
            filoSpines.push_back(stat);
            foreach (auto pt, mapping[stat.sbp]) {
                classified.at(pt.x(),pt.y()).setValue(__filopodium__);
            }
            break;
        case __stubby__:
            stubbySpines.push_back(stat);
            foreach (auto pt, mapping[stat.sbp]) {
                classified.at(pt.x(),pt.y()).setValue(__stubby__);
            } break;
        case __mushroom__:
            mushroomSpines.push_back(stat);
            foreach (auto pt, mapping[stat.sbp]) {
                classified.at(pt.x(),pt.y()).setValue(__mushroom__);
            } break;
        }
    }
    display(currDisplay,classified,zoomFactor);
    // Lambda to create detailed statistics text
    auto computeStats = [this](const QVector<SpineStats>& stats, const QString& typeName) {
        if (stats.isEmpty()) return QString();

        QString statsText = typeName + " Spine Statistics:\n";

        // Define statistics computation for each attribute
        struct StatComputer {
            QString name;
            std::function<double(const SpineStats&)> getter;
        };

        std::vector<StatComputer> attributes = {
            {"Head Width", [](const SpineStats& s) { return s.headWidth; }},
            {"Neck Length", [](const SpineStats& s) { return s.neckLength; }},
            {"Spine Length", [](const SpineStats& s) { return s.spineLength; }},
            {"Avg Neck Width", [](const SpineStats& s) { return s.avgNeckWidth; }},
            {"Area", [](const SpineStats& s) { return s.area; }}
        };

        // Compute and add statistics for each attribute
        for (const auto& attr : attributes) {
            double mean = SpineStats::mean(stats, attr.getter);
            double stddev = SpineStats::stddev(stats, attr.getter);

            // Find spine with max and min values
            int maxIndex = -1, minIndex = -1;
            double maxVal = std::numeric_limits<double>::lowest();
            double minVal = std::numeric_limits<double>::max();

            for (int i = 0; i < stats.size(); ++i) {
                double val = attr.getter(stats[i]);
                if (val > maxVal) {
                    maxVal = val;
                    maxIndex = i;
                }
                if (val < minVal) {
                    minVal = val;
                    minIndex = i;
                }
            }

            // Format the statistics string
            statsText += QString("%1 - Mean: %2, StdDev: %3\n")
                             .arg(attr.name)
                             .arg(mean, 0, 'f', 2)
                             .arg(stddev, 0, 'f', 2);

            // Add max and min spine details if found
            if (maxIndex != -1) {
                statsText += QString("  Max %1: %2 (Spine %3)\n")
                .arg(attr.name)
                    .arg(maxVal, 0, 'f', 2)
                    .arg(table.indexOf(stats[maxIndex]));
            }
            if (minIndex != -1) {
                statsText += QString("  Min %1: %2 (Spine %3)\n")
                .arg(attr.name)
                    .arg(minVal, 0, 'f', 2)
                    .arg(table.indexOf(stats[minIndex]));
            }
        }

        statsText += "\n";
        return statsText;
    };

    for (int i = 1; i < currCombinedSkel.getRows()-1; ++i) {
        for (int j = 0; j < currCombinedSkel.getCols()-1; ++j) {
            int val=currCombinedSkel.at(i,j).getValue();
            if(val==__jp__ || val==__dendrite__ || val== __ddj__ || val==__de__)
            {
                dendriteLength++;
            }
        }
    }

    spineDensity=(static_cast<double>(table.size()/dendriteLength))/0.07;
    // Compute overall statistics
    QString overallStatsText = "Overall Spine Statistics:\n";
    overallStatsText += QString("Total Spines: %1\n")
                            .arg(table.size());
    overallStatsText += QString("Total Dendrite Length: %1\n")
                            .arg(dendriteLength);
    overallStatsText += QString("Spine Density: %1\n")
                            .arg(spineDensity, 0, 'f', 2);
    overallStatsText += QString("Filopodia: %1, Stubby: %2, Mushroom: %3\n\n")
                            .arg(filoSpines.size())
                            .arg(stubbySpines.size())
                            .arg(mushroomSpines.size());

    // Compute and add type-specific and overall statistics
    QString statsText = overallStatsText +
                        computeStats(filoSpines, "Filopodia") +
                        computeStats(stubbySpines, "Stubby") +
                        computeStats(mushroomSpines, "Mushroom");

    // Display the statistics
    ui->wholeStats->setText(statsText);
}
// Function to display detailed information for a selected spine
void MainWindow::on_displayIndividualSpineInformation_clicked()
{
    // Get the selected spine index from the UI
    ui->spineKey->setMaximum(table.size()); // Adjust for 0-based indexing
    int spineIndex = ui->spineKey->value();

    // Validate the selected spine index
    if (spineIndex < 0 || spineIndex >= table.size()) {
        ui->individualStats->setText("Invalid spine selected.");
        return;
    }

    // Retrieve the selected spine's statistics
    const SpineStats& selectedSpine = table[spineIndex];
    QSet<QPoint> spinePoints = mapping[selectedSpine.sbp];

    // Create a copy of the marking matrix to highlight the selected spine
    Matrix<int> mark = labelledCHP.markingHNJ;
    for (const auto& pt : spinePoints) {
        mark.at(pt.x(), pt.y()).setValue(__spine__);
    }

    // Display the highlighted spine with the current zoom factor
    display(currDisplay, mark, zoomFactor);

    // Determine the spine type as a human-readable string
    QString spineType;
    switch (selectedSpine.type) {
    case __filopodium__: spineType = "Filopodia"; break;
    case __stubby__: spineType = "Stubby"; break;
    default: spineType = "Mushroom"; break;
    }

    // Format the individual spine information
    QString individualSpineInfo = QString(
                                      "<b>Spine %1 Details:</b><br>"
                                      "<b>Type:</b> %2<br>"
                                      "<b>SBP Location:</b> (%3, %4)<br>"
                                      "<b>Head Width:</b> %5 pixels (%6 µm)<br>"
                                      "<b>Neck Length:</b> %7 pixels (%8 µm)<br>"
                                      "<b>Spine Length:</b> %9 pixels (%10 µm)<br>"
                                      "<b>Avg Neck Width:</b> %11 pixels (%12 µm)<br>"
                                      "<b>Min Neck Width:</b> %13 pixels (%14 µm)<br>"
                                      "<b>Max Neck Width:</b> %15 pixels (%16 µm)<br>"
                                      "<b>Area:</b> %17 pixels² (%18 µm²)")
                                      .arg(spineIndex)
                                      .arg(spineType)
                                      .arg(selectedSpine.sbp.x())
                                      .arg(selectedSpine.sbp.y())
                                      .arg(selectedSpine.headWidth).arg(selectedSpine.headWidth * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.neckLength).arg(selectedSpine.neckLength * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.spineLength).arg(selectedSpine.spineLength * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.avgNeckWidth, 0, 'f', 2).arg(selectedSpine.avgNeckWidth * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.minNeckWidth).arg(selectedSpine.minNeckWidth * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.maxNeckWidth).arg(selectedSpine.maxNeckWidth * resolution, 0, 'f', 2)
                                      .arg(selectedSpine.area).arg(selectedSpine.area * resolution, 0, 'f', 2);

    // Display the formatted information in the UI
    ui->individualStats->setText(individualSpineInfo);
}

void MainWindow::on_displaySpineNumber_clicked()
{
    // Ensure we have spine data
    if (table.isEmpty() || mapping.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("No spine data available. Please complete spine analysis first."));
        return;
    }

    // Create a deep copy of the current display for overlay
    Matrix<int> displayMatrix = currDisplay;

    // Create a QImage for drawing at full resolution
    int rows = displayMatrix.getRows();
    int cols = displayMatrix.getCols();
    QImage baseImage(cols, rows, QImage::Format_RGB888);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int grayValue = displayMatrix.at(i, j).getValue();
            baseImage.setPixel(j, i, qRgb(grayValue, grayValue, grayValue));
        }
    }

    // Create a QPainter for drawing annotations
    QPainter painter(&baseImage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // Prepare font for spine numbers (use a fixed size that doesn't depend on zoom)
    QFont numberFont("Arial", 10, QFont::Bold);
    painter.setFont(numberFont);

    // Process each spine
    for (int spineIndex = 0; spineIndex < table.size(); ++spineIndex) {
        const SpineStats& spine = table[spineIndex];
        QSet<QPoint> spinePoints = mapping[spine.sbp];

        // Find bounding box for the spine
        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();

        for (const QPoint& pt : spinePoints) {
            minX = std::min(minX, pt.x());
            minY = std::min(minY, pt.y());
            maxX = std::max(maxX, pt.x());
            maxY = std::max(maxY, pt.y());
        }

        // Expand bounding box slightly for better visibility
        int padding = 2;
        minX = std::max(0, minX - padding);
        minY = std::max(0, minY - padding);
        maxX = std::min(cols - 1, maxX + padding);
        maxY = std::min(rows - 1, maxY + padding);

        // Draw transparent blue bounding box
        QPen boxPen(QColor(0, 0, 255, 180), 2, Qt::SolidLine);
        painter.setPen(boxPen);
        painter.setBrush(QColor(0, 0, 255, 50));
        painter.drawRect(minY, minX, maxY - minY, maxX - minX);

        // Draw spine number in top-right corner
        painter.setPen(QColor(255, 0, 0, 255)); // Red text with full opacity
        QString spineNumberText = QString::number(spineIndex);

        // Use a fixed-size text rectangle independent of zoom
        QRect textRect(minY, maxX - 30, 20, 30);
        painter.drawText(textRect, Qt::AlignRight | Qt::AlignTop, spineNumberText);
    }

    painter.end();

    // Scale the image based on zoom factor
    QPixmap annotatedPixmap = QPixmap::fromImage(baseImage);
    annotatedPixmap = annotatedPixmap.scaled(
        static_cast<int>(cols * zoomFactor),
        static_cast<int>(rows * zoomFactor),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
        );

    // Display the annotated image
    ui->lblImage->setPixmap(annotatedPixmap);
}

#include <QImage>
#include <QDir>
#include <QDebug>



void MainWindow::on_browse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Save Directory",
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly |
                                                        QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty()) {
        ui->folderPath->setText(dir);
    }
}
#include <QFileInfo>

void MainWindow::on_saveNet_clicked()
{
    QString saveDir = ui->folderPath->text();
    if (saveDir.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a save location first.");
        return;
    }

    QString originalImagePath = ui->filename->text();
    QFileInfo fileInfo(originalImagePath);
    QString baseName = fileInfo.completeBaseName(); // Extract filename without extension

    QString filePath = QDir(saveDir).filePath(baseName + "_net_summary.csv");
    SaveHandler handler(table, resolution);  // Pass resolution here
    if (!handler.saveNet(filePath)) {
        QMessageBox::critical(this, "Error", "Failed to save net summary.");
    } else {
        QMessageBox::information(this, "Success", "Net summary saved successfully.");
    }
}

void MainWindow::on_saveAllSpines_clicked()
{
    QString saveDir = ui->folderPath->text();
    if (saveDir.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a save location first.");
        return;
    }

    QString originalImagePath = ui->filename->text();
    QFileInfo fileInfo(originalImagePath);
    QString baseName = fileInfo.completeBaseName(); // Extract filename without extension

    QString filePath = QDir(saveDir).filePath(baseName + "_all_spines_summary.csv");
    SaveHandler handler(table, resolution);  // Pass resolution here
    if (!handler.saveAllIndividual(filePath)) {
        QMessageBox::critical(this, "Error", "Failed to save all spines summary.");
    } else {
        QMessageBox::information(this, "Success", "All spines summary saved successfully.");
    }
}

void MainWindow::on_resolution_valueChanged(double arg1)
{
    resolution=arg1;
}


