/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Image;
    QAction *actionLoad_Image_Folder;
    QAction *actionClear;
    QAction *actionSave_Current_Image;
    QAction *actionBinary;
    QAction *actionOriginal;
    QAction *actionNext_Image;
    QAction *actionAuto;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget1;
    QWidget *Image_Processing;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *Denoising;
    QGridLayout *gridLayout_5;
    QPushButton *useCurrentImage;
    QToolBox *toolBox_3;
    QWidget *meanFilter;
    QFormLayout *formLayout_4;
    QLabel *label_2;
    QSpinBox *spnMean;
    QPushButton *btnMeanDenoise;
    QWidget *medianFilter;
    QFormLayout *formLayout_5;
    QLabel *label_3;
    QSpinBox *spnMedian;
    QPushButton *btnMedianDenoise;
    QWidget *gaussianFilter;
    QFormLayout *formLayout_6;
    QLabel *label_4;
    QSpinBox *spnGaussian;
    QLabel *label_5;
    QDoubleSpinBox *spnSigma;
    QPushButton *btnGaussianDenoise;
    QWidget *bilateralFilter;
    QFormLayout *formLayout_7;
    QLabel *label_6;
    QSpinBox *spnDiameter;
    QLabel *label_7;
    QDoubleSpinBox *spnSigmaColor;
    QLabel *label_8;
    QDoubleSpinBox *spnSigmaSpace;
    QPushButton *btnBilateralFilter;
    QWidget *n2v;
    QFormLayout *formLayout_8;
    QPushButton *btnNoise2Void;
    QFrame *line;
    QWidget *Binarization;
    QGridLayout *gridLayout_4;
    QToolBox *toolBox_2;
    QWidget *globalThresholding;
    QGridLayout *gridLayout_17;
    QSpinBox *spnThreshold;
    QLabel *label;
    QPushButton *globalThresholdingBinarize;
    QWidget *otsu;
    QGridLayout *gridLayout_15;
    QPushButton *otsuBinarise;
    QWidget *otherTechniques;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_18;
    QPushButton *twoMeansBinarize;
    QPushButton *flip;
    QWidget *unet;
    QFormLayout *formLayout_3;
    QPushButton *unetBinarize;
    QWidget *SpuriousPatchElimination;
    QFormLayout *formLayout_11;
    QSpinBox *whiteBlobSize;
    QPushButton *whiteBlobRemoval;
    QSpinBox *blackHoleSize;
    QPushButton *holeRemoval;
    QPushButton *spotRemoval;
    QWidget *Settings;
    QGridLayout *gridLayout_6;
    QToolBox *toolBox_4;
    QWidget *basicPreprocessing;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_10;
    QLabel *label_10;
    QPushButton *btnComputeCI;
    QSlider *horizontalSlider;
    QGroupBox *dt;
    QGridLayout *gridLayout_7;
    QPushButton *btnComputeDT;
    QRadioButton *rbnBin;
    QWidget *skeletonization;
    QGridLayout *gridLayout_20;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_16;
    QPushButton *selectPoints;
    QListWidget *loopCutList;
    QPushButton *completeSkel;
    QPushButton *finalSkel;
    QPushButton *primarySkel;
    QFrame *line_8;
    QPushButton *BreakLoop;
    QWidget *spineLocalisation;
    QGridLayout *gridLayout_10;
    QTabWidget *spinelocalisation;
    QWidget *dendriteExtractionTab;
    QGridLayout *gridLayout_19;
    QFrame *line_9;
    QLabel *label_9;
    QSpinBox *spnPruningIter;
    QDoubleSpinBox *dbSpnAlpha;
    QLabel *label_12;
    QPushButton *dendriteExtraction;
    QPushButton *setManualDE;
    QWidget *segmentation;
    QGridLayout *gridLayout_14;
    QPushButton *rBtnPrimarySegmentation;
    QToolBox *showSpine;
    QWidget *showSpinePage1;
    QFormLayout *formLayout_9;
    QLabel *label_13;
    QLabel *label_18;
    QSlider *sbpSlider;
    QFrame *line_2;
    QFrame *line_5;
    QWidget *page;
    QGridLayout *gridLayout_12;
    QLabel *label_15;
    QFrame *line_3;
    QFrame *line_4;
    QSlider *spineFiller;
    QPushButton *showCHP;
    QLabel *label_19;
    QSpacerItem *verticalSpacer;
    QWidget *page_2;
    QFormLayout *formLayout_13;
    QSlider *filopodiumSTD;
    QSlider *hnjSlider;
    QFrame *line_6;
    QFrame *line_7;
    QLabel *label_16;
    QLabel *label_20;
    QLabel *label_14;
    QLabel *label_21;
    QPushButton *performDefaultSpineLocalisation;
    QWidget *Results;
    QGridLayout *gridLayout_21;
    QToolBox *toolBox;
    QWidget *page_4;
    QGridLayout *gridLayout_22;
    QLabel *wholeStats;
    QPushButton *displayNetStats;
    QPushButton *displaySpineNumber;
    QWidget *page_5;
    QFormLayout *formLayout;
    QLabel *label_17;
    QSpinBox *spineKey;
    QLabel *individualStats;
    QPushButton *displayIndividualSpineInformation;
    QScrollBar *zoomBar;
    QGroupBox *mouseInfo;
    QGridLayout *gridLayout_9;
    QLabel *filename;
    QLabel *label_24;
    QProgressBar *progressBar;
    QLabel *coordinates;
    QLabel *spineNum;
    QLabel *label_22;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_23;
    QDoubleSpinBox *resolution;
    QLabel *label_23;
    QFrame *line_10;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *lblImage;
    QLabel *label_11;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_13;
    QLineEdit *folderPath;
    QPushButton *browse;
    QPushButton *saveNet;
    QPushButton *saveAllSpines;
    QMenuBar *menubar;
    QMenu *menuView;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1227, 789);
        MainWindow->setMinimumSize(QSize(1000, 0));
        MainWindow->setStyleSheet(QString::fromUtf8("/* Main Application Styling */\n"
"QMainWindow {\n"
"    background-color: #2D2D30;\n"
"}\n"
"\n"
"QWidget {\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 12px;\n"
"    color: #DCDCDC;\n"
"}\n"
"\n"
"/* Tab Widget Styling */\n"
"QTabWidget::pane {\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 4px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #404040;\n"
"    color: #B0B0B0;\n"
"    padding: 8px 15px;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    border: 1px solid #3F3F46;\n"
"    margin-right: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #007ACC;\n"
"    color: white;\n"
"    border-color: #005FAB;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #505050;\n"
"}\n"
"\n"
"/* Button Styling */\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #505050, stop:1 #404040);\n"
"    border: 1px solid #3F3F46;\n"
"    border-ra"
                        "dius: 4px;\n"
"    color: #E0E0E0;\n"
"    padding: 5px 10px;\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #606060, stop:1 #505050);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #404040, stop:1 #303030);\n"
"}\n"
"\n"
"/* Group Box Styling */\n"
"QGroupBox {\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 4px;\n"
"    margin-top: 10px;\n"
"    padding-top: 15px;\n"
"    color: #B0B0B0;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 0 5px;\n"
"    left: 10px;\n"
"}\n"
"\n"
"/* Spin Box & Slider Styling */\n"
"QSpinBox, QDoubleSpinBox {\n"
"    background: #404040;\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 3px;\n"
"    padding: 3px;\n"
"    color: #E0E0E0;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
""
                        "    height: 6px;\n"
"    background: #404040;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #007ACC;\n"
"    width: 14px;\n"
"    margin: -4px 0;\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #007ACC;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"/* List Widget Styling */\n"
"QListWidget {\n"
"    background: #404040;\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 4px;\n"
"    color: #E0E0E0;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background: #505050;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background: #007ACC;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Progress Bar Styling */\n"
"QProgressBar {\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 3px;\n"
"    text-align: center;\n"
"    background: #404040;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background: #00CC00;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"/* Tool Box Styling */\n"
"QToolBox::tab {\n"
"    background: #404040;\n"
""
                        "    color: #B0B0B0;\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QToolBox::tab:selected {\n"
"    background: #007ACC;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Line Edit Styling */\n"
"QLineEdit {\n"
"    background: #404040;\n"
"    border: 1px solid #3F3F46;\n"
"    border-radius: 3px;\n"
"    padding: 5px;\n"
"    color: #E0E0E0;\n"
"}\n"
"\n"
"/* Scroll Bar Styling */\n"
"QScrollBar:vertical {\n"
"    width: 12px;\n"
"    background: #404040;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #505050;\n"
"    min-height: 20px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
"/* Status Bar Styling */\n"
"QStatusBar {\n"
"    background: #252526;\n"
"    color: #B0B0B0;\n"
"}\n"
"\n"
"/* Menu Bar Styling */\n"
"QMenuBar {\n"
"    background: #333337;\n"
"    color: #B0B0B0;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"    ba"
                        "ckground: #505050;\n"
"    color: white;\n"
"}\n"
"\n"
"QMenu {\n"
"    background: #333337;\n"
"    border: 1px solid #3F3F46;\n"
"    color: #B0B0B0;\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"    background: #007ACC;\n"
"    color: white;\n"
"}"));
        actionLoad_Image = new QAction(MainWindow);
        actionLoad_Image->setObjectName("actionLoad_Image");
        actionLoad_Image_Folder = new QAction(MainWindow);
        actionLoad_Image_Folder->setObjectName("actionLoad_Image_Folder");
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName("actionClear");
        actionSave_Current_Image = new QAction(MainWindow);
        actionSave_Current_Image->setObjectName("actionSave_Current_Image");
        actionBinary = new QAction(MainWindow);
        actionBinary->setObjectName("actionBinary");
        actionOriginal = new QAction(MainWindow);
        actionOriginal->setObjectName("actionOriginal");
        actionNext_Image = new QAction(MainWindow);
        actionNext_Image->setObjectName("actionNext_Image");
        actionAuto = new QAction(MainWindow);
        actionAuto->setObjectName("actionAuto");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget1 = new QTabWidget(centralwidget);
        tabWidget1->setObjectName("tabWidget1");
        tabWidget1->setEnabled(true);
        tabWidget1->setMinimumSize(QSize(300, 0));
        tabWidget1->setMaximumSize(QSize(400, 16777215));
        Image_Processing = new QWidget();
        Image_Processing->setObjectName("Image_Processing");
        gridLayout_3 = new QGridLayout(Image_Processing);
        gridLayout_3->setObjectName("gridLayout_3");
        tabWidget_2 = new QTabWidget(Image_Processing);
        tabWidget_2->setObjectName("tabWidget_2");
        Denoising = new QWidget();
        Denoising->setObjectName("Denoising");
        gridLayout_5 = new QGridLayout(Denoising);
        gridLayout_5->setObjectName("gridLayout_5");
        useCurrentImage = new QPushButton(Denoising);
        useCurrentImage->setObjectName("useCurrentImage");

        gridLayout_5->addWidget(useCurrentImage, 0, 0, 1, 1);

        toolBox_3 = new QToolBox(Denoising);
        toolBox_3->setObjectName("toolBox_3");
        meanFilter = new QWidget();
        meanFilter->setObjectName("meanFilter");
        meanFilter->setGeometry(QRect(0, 0, 344, 243));
        formLayout_4 = new QFormLayout(meanFilter);
        formLayout_4->setObjectName("formLayout_4");
        label_2 = new QLabel(meanFilter);
        label_2->setObjectName("label_2");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_2);

        spnMean = new QSpinBox(meanFilter);
        spnMean->setObjectName("spnMean");
        spnMean->setMinimum(1);
        spnMean->setSingleStep(2);
        spnMean->setValue(1);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, spnMean);

        btnMeanDenoise = new QPushButton(meanFilter);
        btnMeanDenoise->setObjectName("btnMeanDenoise");

        formLayout_4->setWidget(1, QFormLayout::SpanningRole, btnMeanDenoise);

        toolBox_3->addItem(meanFilter, QString::fromUtf8("Mean Filter"));
        medianFilter = new QWidget();
        medianFilter->setObjectName("medianFilter");
        medianFilter->setGeometry(QRect(0, 0, 126, 83));
        formLayout_5 = new QFormLayout(medianFilter);
        formLayout_5->setObjectName("formLayout_5");
        label_3 = new QLabel(medianFilter);
        label_3->setObjectName("label_3");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_3);

        spnMedian = new QSpinBox(medianFilter);
        spnMedian->setObjectName("spnMedian");
        spnMedian->setMinimum(1);
        spnMedian->setSingleStep(2);
        spnMedian->setValue(1);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, spnMedian);

        btnMedianDenoise = new QPushButton(medianFilter);
        btnMedianDenoise->setObjectName("btnMedianDenoise");

        formLayout_5->setWidget(1, QFormLayout::SpanningRole, btnMedianDenoise);

        toolBox_3->addItem(medianFilter, QString::fromUtf8("Median Filter"));
        gaussianFilter = new QWidget();
        gaussianFilter->setObjectName("gaussianFilter");
        gaussianFilter->setGeometry(QRect(0, 0, 141, 116));
        formLayout_6 = new QFormLayout(gaussianFilter);
        formLayout_6->setObjectName("formLayout_6");
        label_4 = new QLabel(gaussianFilter);
        label_4->setObjectName("label_4");

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_4);

        spnGaussian = new QSpinBox(gaussianFilter);
        spnGaussian->setObjectName("spnGaussian");
        spnGaussian->setMinimum(1);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, spnGaussian);

        label_5 = new QLabel(gaussianFilter);
        label_5->setObjectName("label_5");

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_5);

        spnSigma = new QDoubleSpinBox(gaussianFilter);
        spnSigma->setObjectName("spnSigma");
        spnSigma->setDecimals(1);
        spnSigma->setSingleStep(0.100000000000000);
        spnSigma->setStepType(QAbstractSpinBox::StepType::AdaptiveDecimalStepType);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, spnSigma);

        btnGaussianDenoise = new QPushButton(gaussianFilter);
        btnGaussianDenoise->setObjectName("btnGaussianDenoise");

        formLayout_6->setWidget(2, QFormLayout::SpanningRole, btnGaussianDenoise);

        toolBox_3->addItem(gaussianFilter, QString::fromUtf8("Gaussian Filter"));
        bilateralFilter = new QWidget();
        bilateralFilter->setObjectName("bilateralFilter");
        bilateralFilter->setGeometry(QRect(0, 0, 152, 149));
        formLayout_7 = new QFormLayout(bilateralFilter);
        formLayout_7->setObjectName("formLayout_7");
        label_6 = new QLabel(bilateralFilter);
        label_6->setObjectName("label_6");

        formLayout_7->setWidget(0, QFormLayout::LabelRole, label_6);

        spnDiameter = new QSpinBox(bilateralFilter);
        spnDiameter->setObjectName("spnDiameter");
        spnDiameter->setMinimum(1);
        spnDiameter->setSingleStep(2);

        formLayout_7->setWidget(0, QFormLayout::FieldRole, spnDiameter);

        label_7 = new QLabel(bilateralFilter);
        label_7->setObjectName("label_7");

        formLayout_7->setWidget(1, QFormLayout::LabelRole, label_7);

        spnSigmaColor = new QDoubleSpinBox(bilateralFilter);
        spnSigmaColor->setObjectName("spnSigmaColor");
        spnSigmaColor->setDecimals(1);

        formLayout_7->setWidget(1, QFormLayout::FieldRole, spnSigmaColor);

        label_8 = new QLabel(bilateralFilter);
        label_8->setObjectName("label_8");

        formLayout_7->setWidget(2, QFormLayout::LabelRole, label_8);

        spnSigmaSpace = new QDoubleSpinBox(bilateralFilter);
        spnSigmaSpace->setObjectName("spnSigmaSpace");
        spnSigmaSpace->setDecimals(1);

        formLayout_7->setWidget(2, QFormLayout::FieldRole, spnSigmaSpace);

        btnBilateralFilter = new QPushButton(bilateralFilter);
        btnBilateralFilter->setObjectName("btnBilateralFilter");

        formLayout_7->setWidget(3, QFormLayout::SpanningRole, btnBilateralFilter);

        toolBox_3->addItem(bilateralFilter, QString::fromUtf8("Bilateral Filter"));
        n2v = new QWidget();
        n2v->setObjectName("n2v");
        n2v->setGeometry(QRect(0, 0, 124, 50));
        formLayout_8 = new QFormLayout(n2v);
        formLayout_8->setObjectName("formLayout_8");
        btnNoise2Void = new QPushButton(n2v);
        btnNoise2Void->setObjectName("btnNoise2Void");

        formLayout_8->setWidget(0, QFormLayout::SpanningRole, btnNoise2Void);

        toolBox_3->addItem(n2v, QString::fromUtf8("Noise2Void"));

        gridLayout_5->addWidget(toolBox_3, 2, 0, 1, 1);

        line = new QFrame(Denoising);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_5->addWidget(line, 1, 0, 1, 1);

        tabWidget_2->addTab(Denoising, QString());
        Binarization = new QWidget();
        Binarization->setObjectName("Binarization");
        gridLayout_4 = new QGridLayout(Binarization);
        gridLayout_4->setObjectName("gridLayout_4");
        toolBox_2 = new QToolBox(Binarization);
        toolBox_2->setObjectName("toolBox_2");
        globalThresholding = new QWidget();
        globalThresholding->setObjectName("globalThresholding");
        globalThresholding->setGeometry(QRect(0, 0, 173, 83));
        gridLayout_17 = new QGridLayout(globalThresholding);
        gridLayout_17->setObjectName("gridLayout_17");
        spnThreshold = new QSpinBox(globalThresholding);
        spnThreshold->setObjectName("spnThreshold");
        spnThreshold->setMaximum(250);
        spnThreshold->setSingleStep(10);
        spnThreshold->setValue(70);

        gridLayout_17->addWidget(spnThreshold, 0, 1, 1, 1);

        label = new QLabel(globalThresholding);
        label->setObjectName("label");

        gridLayout_17->addWidget(label, 0, 0, 1, 1);

        globalThresholdingBinarize = new QPushButton(globalThresholding);
        globalThresholdingBinarize->setObjectName("globalThresholdingBinarize");

        gridLayout_17->addWidget(globalThresholdingBinarize, 1, 0, 1, 2);

        toolBox_2->addItem(globalThresholding, QString::fromUtf8("Global Thresholding"));
        otsu = new QWidget();
        otsu->setObjectName("otsu");
        otsu->setGeometry(QRect(0, 0, 124, 50));
        gridLayout_15 = new QGridLayout(otsu);
        gridLayout_15->setObjectName("gridLayout_15");
        otsuBinarise = new QPushButton(otsu);
        otsuBinarise->setObjectName("otsuBinarise");

        gridLayout_15->addWidget(otsuBinarise, 0, 0, 1, 1);

        toolBox_2->addItem(otsu, QString::fromUtf8("OTSU"));
        otherTechniques = new QWidget();
        otherTechniques->setObjectName("otherTechniques");
        otherTechniques->setGeometry(QRect(0, 0, 148, 134));
        gridLayout_11 = new QGridLayout(otherTechniques);
        gridLayout_11->setObjectName("gridLayout_11");
        groupBox_4 = new QGroupBox(otherTechniques);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_18 = new QGridLayout(groupBox_4);
        gridLayout_18->setObjectName("gridLayout_18");
        twoMeansBinarize = new QPushButton(groupBox_4);
        twoMeansBinarize->setObjectName("twoMeansBinarize");

        gridLayout_18->addWidget(twoMeansBinarize, 0, 0, 1, 1);

        flip = new QPushButton(groupBox_4);
        flip->setObjectName("flip");

        gridLayout_18->addWidget(flip, 1, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_4, 0, 0, 1, 1);

        toolBox_2->addItem(otherTechniques, QString::fromUtf8("Clustering Based Thresholding"));
        unet = new QWidget();
        unet->setObjectName("unet");
        unet->setGeometry(QRect(0, 0, 124, 50));
        formLayout_3 = new QFormLayout(unet);
        formLayout_3->setObjectName("formLayout_3");
        unetBinarize = new QPushButton(unet);
        unetBinarize->setObjectName("unetBinarize");

        formLayout_3->setWidget(0, QFormLayout::SpanningRole, unetBinarize);

        toolBox_2->addItem(unet, QString::fromUtf8("UNET Based Binarization"));

        gridLayout_4->addWidget(toolBox_2, 0, 0, 1, 1);

        tabWidget_2->addTab(Binarization, QString());
        SpuriousPatchElimination = new QWidget();
        SpuriousPatchElimination->setObjectName("SpuriousPatchElimination");
        formLayout_11 = new QFormLayout(SpuriousPatchElimination);
        formLayout_11->setObjectName("formLayout_11");
        whiteBlobSize = new QSpinBox(SpuriousPatchElimination);
        whiteBlobSize->setObjectName("whiteBlobSize");
        whiteBlobSize->setMinimum(50);
        whiteBlobSize->setMaximum(1000);
        whiteBlobSize->setSingleStep(20);
        whiteBlobSize->setValue(500);

        formLayout_11->setWidget(0, QFormLayout::SpanningRole, whiteBlobSize);

        whiteBlobRemoval = new QPushButton(SpuriousPatchElimination);
        whiteBlobRemoval->setObjectName("whiteBlobRemoval");

        formLayout_11->setWidget(1, QFormLayout::SpanningRole, whiteBlobRemoval);

        blackHoleSize = new QSpinBox(SpuriousPatchElimination);
        blackHoleSize->setObjectName("blackHoleSize");
        blackHoleSize->setMinimum(50);
        blackHoleSize->setMaximum(1000);
        blackHoleSize->setSingleStep(20);
        blackHoleSize->setValue(500);

        formLayout_11->setWidget(2, QFormLayout::SpanningRole, blackHoleSize);

        holeRemoval = new QPushButton(SpuriousPatchElimination);
        holeRemoval->setObjectName("holeRemoval");

        formLayout_11->setWidget(3, QFormLayout::SpanningRole, holeRemoval);

        spotRemoval = new QPushButton(SpuriousPatchElimination);
        spotRemoval->setObjectName("spotRemoval");

        formLayout_11->setWidget(4, QFormLayout::SpanningRole, spotRemoval);

        tabWidget_2->addTab(SpuriousPatchElimination, QString());

        gridLayout_3->addWidget(tabWidget_2, 0, 0, 1, 1);

        tabWidget1->addTab(Image_Processing, QString());
        Settings = new QWidget();
        Settings->setObjectName("Settings");
        gridLayout_6 = new QGridLayout(Settings);
        gridLayout_6->setObjectName("gridLayout_6");
        toolBox_4 = new QToolBox(Settings);
        toolBox_4->setObjectName("toolBox_4");
        toolBox_4->setEnabled(true);
        toolBox_4->setFrameShape(QFrame::Shape::NoFrame);
        basicPreprocessing = new QWidget();
        basicPreprocessing->setObjectName("basicPreprocessing");
        basicPreprocessing->setGeometry(QRect(0, 0, 374, 378));
        gridLayout_8 = new QGridLayout(basicPreprocessing);
        gridLayout_8->setObjectName("gridLayout_8");
        groupBox_3 = new QGroupBox(basicPreprocessing);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setEnabled(true);
        formLayout_10 = new QFormLayout(groupBox_3);
        formLayout_10->setObjectName("formLayout_10");
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        formLayout_10->setWidget(0, QFormLayout::SpanningRole, label_10);

        btnComputeCI = new QPushButton(groupBox_3);
        btnComputeCI->setObjectName("btnComputeCI");

        formLayout_10->setWidget(2, QFormLayout::SpanningRole, btnComputeCI);

        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMaximum(250);
        horizontalSlider->setSingleStep(10);
        horizontalSlider->setValue(50);
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        formLayout_10->setWidget(1, QFormLayout::SpanningRole, horizontalSlider);


        gridLayout_8->addWidget(groupBox_3, 1, 0, 1, 1);

        dt = new QGroupBox(basicPreprocessing);
        dt->setObjectName("dt");
        gridLayout_7 = new QGridLayout(dt);
        gridLayout_7->setObjectName("gridLayout_7");
        btnComputeDT = new QPushButton(dt);
        btnComputeDT->setObjectName("btnComputeDT");

        gridLayout_7->addWidget(btnComputeDT, 1, 0, 1, 1);

        rbnBin = new QRadioButton(dt);
        rbnBin->setObjectName("rbnBin");
        rbnBin->setChecked(true);

        gridLayout_7->addWidget(rbnBin, 0, 0, 1, 1);


        gridLayout_8->addWidget(dt, 0, 0, 1, 1);

        toolBox_4->addItem(basicPreprocessing, QString::fromUtf8("Preprocessing"));
        skeletonization = new QWidget();
        skeletonization->setObjectName("skeletonization");
        skeletonization->setGeometry(QRect(0, 0, 374, 378));
        gridLayout_20 = new QGridLayout(skeletonization);
        gridLayout_20->setObjectName("gridLayout_20");
        groupBox_2 = new QGroupBox(skeletonization);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_16 = new QGridLayout(groupBox_2);
        gridLayout_16->setObjectName("gridLayout_16");
        selectPoints = new QPushButton(groupBox_2);
        selectPoints->setObjectName("selectPoints");

        gridLayout_16->addWidget(selectPoints, 0, 0, 1, 1);

        loopCutList = new QListWidget(groupBox_2);
        loopCutList->setObjectName("loopCutList");

        gridLayout_16->addWidget(loopCutList, 1, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_2, 3, 0, 1, 2);

        completeSkel = new QPushButton(skeletonization);
        completeSkel->setObjectName("completeSkel");

        gridLayout_20->addWidget(completeSkel, 1, 0, 1, 2);

        finalSkel = new QPushButton(skeletonization);
        finalSkel->setObjectName("finalSkel");

        gridLayout_20->addWidget(finalSkel, 0, 1, 1, 1);

        primarySkel = new QPushButton(skeletonization);
        primarySkel->setObjectName("primarySkel");

        gridLayout_20->addWidget(primarySkel, 0, 0, 1, 1);

        line_8 = new QFrame(skeletonization);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::HLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_20->addWidget(line_8, 2, 0, 1, 2);

        BreakLoop = new QPushButton(skeletonization);
        BreakLoop->setObjectName("BreakLoop");

        gridLayout_20->addWidget(BreakLoop, 4, 0, 1, 2);

        toolBox_4->addItem(skeletonization, QString::fromUtf8("Skeletonization"));
        spineLocalisation = new QWidget();
        spineLocalisation->setObjectName("spineLocalisation");
        spineLocalisation->setGeometry(QRect(0, 0, 372, 412));
        gridLayout_10 = new QGridLayout(spineLocalisation);
        gridLayout_10->setObjectName("gridLayout_10");
        spinelocalisation = new QTabWidget(spineLocalisation);
        spinelocalisation->setObjectName("spinelocalisation");
        spinelocalisation->setTabPosition(QTabWidget::TabPosition::North);
        spinelocalisation->setTabShape(QTabWidget::TabShape::Rounded);
        dendriteExtractionTab = new QWidget();
        dendriteExtractionTab->setObjectName("dendriteExtractionTab");
        gridLayout_19 = new QGridLayout(dendriteExtractionTab);
        gridLayout_19->setObjectName("gridLayout_19");
        line_9 = new QFrame(dendriteExtractionTab);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::HLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_19->addWidget(line_9, 1, 0, 1, 4);

        label_9 = new QLabel(dendriteExtractionTab);
        label_9->setObjectName("label_9");

        gridLayout_19->addWidget(label_9, 2, 0, 1, 1);

        spnPruningIter = new QSpinBox(dendriteExtractionTab);
        spnPruningIter->setObjectName("spnPruningIter");
        spnPruningIter->setMinimum(0);
        spnPruningIter->setMaximum(20);
        spnPruningIter->setValue(3);

        gridLayout_19->addWidget(spnPruningIter, 2, 2, 1, 2);

        dbSpnAlpha = new QDoubleSpinBox(dendriteExtractionTab);
        dbSpnAlpha->setObjectName("dbSpnAlpha");
        dbSpnAlpha->setDecimals(2);
        dbSpnAlpha->setMinimum(1.000000000000000);
        dbSpnAlpha->setMaximum(30.000000000000000);
        dbSpnAlpha->setSingleStep(0.100000000000000);
        dbSpnAlpha->setValue(10.000000000000000);

        gridLayout_19->addWidget(dbSpnAlpha, 4, 2, 1, 2);

        label_12 = new QLabel(dendriteExtractionTab);
        label_12->setObjectName("label_12");
        label_12->setTextFormat(Qt::TextFormat::RichText);

        gridLayout_19->addWidget(label_12, 4, 0, 1, 1);

        dendriteExtraction = new QPushButton(dendriteExtractionTab);
        dendriteExtraction->setObjectName("dendriteExtraction");

        gridLayout_19->addWidget(dendriteExtraction, 5, 0, 1, 4);

        setManualDE = new QPushButton(dendriteExtractionTab);
        setManualDE->setObjectName("setManualDE");

        gridLayout_19->addWidget(setManualDE, 0, 0, 1, 4);

        spinelocalisation->addTab(dendriteExtractionTab, QString());
        segmentation = new QWidget();
        segmentation->setObjectName("segmentation");
        gridLayout_14 = new QGridLayout(segmentation);
        gridLayout_14->setObjectName("gridLayout_14");
        rBtnPrimarySegmentation = new QPushButton(segmentation);
        rBtnPrimarySegmentation->setObjectName("rBtnPrimarySegmentation");

        gridLayout_14->addWidget(rBtnPrimarySegmentation, 0, 0, 1, 1);

        showSpine = new QToolBox(segmentation);
        showSpine->setObjectName("showSpine");
        showSpinePage1 = new QWidget();
        showSpinePage1->setObjectName("showSpinePage1");
        showSpinePage1->setGeometry(QRect(0, 0, 328, 103));
        formLayout_9 = new QFormLayout(showSpinePage1);
        formLayout_9->setObjectName("formLayout_9");
        label_13 = new QLabel(showSpinePage1);
        label_13->setObjectName("label_13");
        label_13->setWordWrap(true);

        formLayout_9->setWidget(1, QFormLayout::LabelRole, label_13);

        label_18 = new QLabel(showSpinePage1);
        label_18->setObjectName("label_18");
        label_18->setFrameShape(QFrame::Shape::Box);

        formLayout_9->setWidget(1, QFormLayout::FieldRole, label_18);

        sbpSlider = new QSlider(showSpinePage1);
        sbpSlider->setObjectName("sbpSlider");
        sbpSlider->setMinimum(1);
        sbpSlider->setMaximum(200);
        sbpSlider->setSingleStep(1);
        sbpSlider->setValue(40);
        sbpSlider->setOrientation(Qt::Orientation::Horizontal);

        formLayout_9->setWidget(3, QFormLayout::SpanningRole, sbpSlider);

        line_2 = new QFrame(showSpinePage1);
        line_2->setObjectName("line_2");
        line_2->setMinimumSize(QSize(100, 0));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        formLayout_9->setWidget(0, QFormLayout::SpanningRole, line_2);

        line_5 = new QFrame(showSpinePage1);
        line_5->setObjectName("line_5");
        line_5->setMinimumSize(QSize(100, 0));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        formLayout_9->setWidget(2, QFormLayout::SpanningRole, line_5);

        showSpine->addItem(showSpinePage1, QString::fromUtf8("Spine Base Point (SBP)"));
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 316, 127));
        gridLayout_12 = new QGridLayout(page);
        gridLayout_12->setObjectName("gridLayout_12");
        label_15 = new QLabel(page);
        label_15->setObjectName("label_15");

        gridLayout_12->addWidget(label_15, 1, 0, 1, 1);

        line_3 = new QFrame(page);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_12->addWidget(line_3, 0, 0, 1, 2);

        line_4 = new QFrame(page);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_12->addWidget(line_4, 3, 0, 1, 2);

        spineFiller = new QSlider(page);
        spineFiller->setObjectName("spineFiller");
        spineFiller->setMinimum(10);
        spineFiller->setMaximum(200);
        spineFiller->setValue(130);
        spineFiller->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_12->addWidget(spineFiller, 6, 0, 1, 2);

        showCHP = new QPushButton(page);
        showCHP->setObjectName("showCHP");

        gridLayout_12->addWidget(showCHP, 7, 0, 1, 2);

        label_19 = new QLabel(page);
        label_19->setObjectName("label_19");
        label_19->setFrameShape(QFrame::Shape::Box);

        gridLayout_12->addWidget(label_19, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_12->addItem(verticalSpacer, 4, 0, 1, 2);

        showSpine->addItem(page, QString::fromUtf8("Central Head Point (CHP)"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setGeometry(QRect(0, -35, 310, 200));
        formLayout_13 = new QFormLayout(page_2);
        formLayout_13->setObjectName("formLayout_13");
        filopodiumSTD = new QSlider(page_2);
        filopodiumSTD->setObjectName("filopodiumSTD");
        filopodiumSTD->setMaximum(500);
        filopodiumSTD->setValue(10);
        filopodiumSTD->setOrientation(Qt::Orientation::Horizontal);

        formLayout_13->setWidget(5, QFormLayout::SpanningRole, filopodiumSTD);

        hnjSlider = new QSlider(page_2);
        hnjSlider->setObjectName("hnjSlider");
        hnjSlider->setMinimum(1);
        hnjSlider->setMaximum(200);
        hnjSlider->setValue(100);
        hnjSlider->setOrientation(Qt::Orientation::Horizontal);
        hnjSlider->setInvertedAppearance(false);

        formLayout_13->setWidget(8, QFormLayout::SpanningRole, hnjSlider);

        line_6 = new QFrame(page_2);
        line_6->setObjectName("line_6");
        line_6->setMinimumSize(QSize(200, 0));
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        formLayout_13->setWidget(0, QFormLayout::SpanningRole, line_6);

        line_7 = new QFrame(page_2);
        line_7->setObjectName("line_7");
        line_7->setMinimumSize(QSize(200, 0));
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        formLayout_13->setWidget(6, QFormLayout::SpanningRole, line_7);

        label_16 = new QLabel(page_2);
        label_16->setObjectName("label_16");
        label_16->setWordWrap(true);

        formLayout_13->setWidget(2, QFormLayout::LabelRole, label_16);

        label_20 = new QLabel(page_2);
        label_20->setObjectName("label_20");
        label_20->setFrameShape(QFrame::Shape::Box);

        formLayout_13->setWidget(2, QFormLayout::FieldRole, label_20);

        label_14 = new QLabel(page_2);
        label_14->setObjectName("label_14");
        label_14->setWordWrap(true);

        formLayout_13->setWidget(7, QFormLayout::LabelRole, label_14);

        label_21 = new QLabel(page_2);
        label_21->setObjectName("label_21");
        label_21->setFrameShape(QFrame::Shape::Box);

        formLayout_13->setWidget(7, QFormLayout::FieldRole, label_21);

        showSpine->addItem(page_2, QString::fromUtf8("Head Neck Junction (HNJ)"));

        gridLayout_14->addWidget(showSpine, 1, 0, 1, 1);

        spinelocalisation->addTab(segmentation, QString());

        gridLayout_10->addWidget(spinelocalisation, 1, 0, 1, 1);

        performDefaultSpineLocalisation = new QPushButton(spineLocalisation);
        performDefaultSpineLocalisation->setObjectName("performDefaultSpineLocalisation");

        gridLayout_10->addWidget(performDefaultSpineLocalisation, 0, 0, 1, 1);

        toolBox_4->addItem(spineLocalisation, QString::fromUtf8("Spine Localisation"));

        gridLayout_6->addWidget(toolBox_4, 0, 0, 1, 1);

        tabWidget1->addTab(Settings, QString());
        Results = new QWidget();
        Results->setObjectName("Results");
        gridLayout_21 = new QGridLayout(Results);
        gridLayout_21->setObjectName("gridLayout_21");
        toolBox = new QToolBox(Results);
        toolBox->setObjectName("toolBox");
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setGeometry(QRect(0, 0, 372, 443));
        gridLayout_22 = new QGridLayout(page_4);
        gridLayout_22->setObjectName("gridLayout_22");
        wholeStats = new QLabel(page_4);
        wholeStats->setObjectName("wholeStats");
        wholeStats->setFrameShape(QFrame::Shape::Box);
        wholeStats->setScaledContents(true);
        wholeStats->setWordWrap(true);

        gridLayout_22->addWidget(wholeStats, 2, 0, 1, 1);

        displayNetStats = new QPushButton(page_4);
        displayNetStats->setObjectName("displayNetStats");

        gridLayout_22->addWidget(displayNetStats, 1, 0, 1, 1);

        displaySpineNumber = new QPushButton(page_4);
        displaySpineNumber->setObjectName("displaySpineNumber");

        gridLayout_22->addWidget(displaySpineNumber, 3, 0, 1, 1);

        toolBox->addItem(page_4, QString::fromUtf8("Global Statistics"));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setGeometry(QRect(0, 0, 176, 108));
        formLayout = new QFormLayout(page_5);
        formLayout->setObjectName("formLayout");
        label_17 = new QLabel(page_5);
        label_17->setObjectName("label_17");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_17);

        spineKey = new QSpinBox(page_5);
        spineKey->setObjectName("spineKey");

        formLayout->setWidget(0, QFormLayout::FieldRole, spineKey);

        individualStats = new QLabel(page_5);
        individualStats->setObjectName("individualStats");
        individualStats->setFrameShape(QFrame::Shape::Box);
        individualStats->setScaledContents(true);
        individualStats->setWordWrap(true);

        formLayout->setWidget(2, QFormLayout::SpanningRole, individualStats);

        displayIndividualSpineInformation = new QPushButton(page_5);
        displayIndividualSpineInformation->setObjectName("displayIndividualSpineInformation");

        formLayout->setWidget(1, QFormLayout::SpanningRole, displayIndividualSpineInformation);

        toolBox->addItem(page_5, QString::fromUtf8("Individual Spine Statistics"));

        gridLayout_21->addWidget(toolBox, 0, 0, 1, 1);

        tabWidget1->addTab(Results, QString());

        gridLayout->addWidget(tabWidget1, 3, 0, 3, 1);

        zoomBar = new QScrollBar(centralwidget);
        zoomBar->setObjectName("zoomBar");
        zoomBar->setStyleSheet(QString::fromUtf8(""));
        zoomBar->setMinimum(100);
        zoomBar->setMaximum(800);
        zoomBar->setValue(100);
        zoomBar->setSliderPosition(100);
        zoomBar->setOrientation(Qt::Orientation::Vertical);
        zoomBar->setInvertedAppearance(true);

        gridLayout->addWidget(zoomBar, 5, 3, 1, 1);

        mouseInfo = new QGroupBox(centralwidget);
        mouseInfo->setObjectName("mouseInfo");
        gridLayout_9 = new QGridLayout(mouseInfo);
        gridLayout_9->setObjectName("gridLayout_9");
        filename = new QLabel(mouseInfo);
        filename->setObjectName("filename");
        filename->setFrameShape(QFrame::Shape::Box);
        filename->setWordWrap(true);

        gridLayout_9->addWidget(filename, 1, 3, 1, 3);

        label_24 = new QLabel(mouseInfo);
        label_24->setObjectName("label_24");

        gridLayout_9->addWidget(label_24, 1, 2, 1, 1);

        progressBar = new QProgressBar(mouseInfo);
        progressBar->setObjectName("progressBar");
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 2px solid #8B8B8B; /* Grey border */\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"    background-color: #E0E0E0; /* Light grey background */\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #2E8B57; /* Sea Green color */\n"
"    width: 20px; /* Optional: Adjusts the width of each chunk */\n"
"}\n"
""));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Orientation::Horizontal);
        progressBar->setTextDirection(QProgressBar::Direction::BottomToTop);

        gridLayout_9->addWidget(progressBar, 2, 2, 1, 4);

        coordinates = new QLabel(mouseInfo);
        coordinates->setObjectName("coordinates");
        coordinates->setFrameShape(QFrame::Shape::Box);

        gridLayout_9->addWidget(coordinates, 0, 3, 1, 1);

        spineNum = new QLabel(mouseInfo);
        spineNum->setObjectName("spineNum");
        spineNum->setEnabled(true);
        spineNum->setFrameShape(QFrame::Shape::Box);

        gridLayout_9->addWidget(spineNum, 0, 5, 1, 1);

        label_22 = new QLabel(mouseInfo);
        label_22->setObjectName("label_22");

        gridLayout_9->addWidget(label_22, 0, 2, 1, 1);

        groupBox_5 = new QGroupBox(mouseInfo);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout_23 = new QGridLayout(groupBox_5);
        gridLayout_23->setObjectName("gridLayout_23");
        resolution = new QDoubleSpinBox(groupBox_5);
        resolution->setObjectName("resolution");
        resolution->setDecimals(3);

        gridLayout_23->addWidget(resolution, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_5, 0, 0, 3, 1);

        label_23 = new QLabel(mouseInfo);
        label_23->setObjectName("label_23");

        gridLayout_9->addWidget(label_23, 0, 4, 1, 1);

        line_10 = new QFrame(mouseInfo);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::Shape::VLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_9->addWidget(line_10, 0, 1, 3, 1);


        gridLayout->addWidget(mouseInfo, 0, 1, 1, 2);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 770, 558));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName("gridLayout_2");
        lblImage = new QLabel(scrollAreaWidgetContents);
        lblImage->setObjectName("lblImage");
        lblImage->setFrameShape(QFrame::Shape::Box);

        gridLayout_2->addWidget(lblImage, 1, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 5, 2, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setFrameShape(QFrame::Shape::NoFrame);
        label_11->setFrameShadow(QFrame::Shadow::Plain);
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_11->setWordWrap(true);

        gridLayout->addWidget(label_11, 6, 2, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout_13 = new QGridLayout(groupBox);
        gridLayout_13->setObjectName("gridLayout_13");
        folderPath = new QLineEdit(groupBox);
        folderPath->setObjectName("folderPath");

        gridLayout_13->addWidget(folderPath, 0, 0, 1, 2);

        browse = new QPushButton(groupBox);
        browse->setObjectName("browse");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        browse->setIcon(icon);

        gridLayout_13->addWidget(browse, 0, 2, 1, 1);

        saveNet = new QPushButton(groupBox);
        saveNet->setObjectName("saveNet");

        gridLayout_13->addWidget(saveNet, 1, 0, 1, 1);

        saveAllSpines = new QPushButton(groupBox);
        saveAllSpines->setObjectName("saveAllSpines");

        gridLayout_13->addWidget(saveAllSpines, 1, 1, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1227, 21));
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menuView->addAction(actionBinary);
        menuView->addAction(actionOriginal);
        menuFile->addAction(actionLoad_Image);
        menuFile->addAction(actionLoad_Image_Folder);
        menuFile->addAction(actionNext_Image);
        menuFile->addAction(actionSave_Current_Image);
        menuFile->addAction(actionAuto);

        retranslateUi(MainWindow);
        QObject::connect(displayNetStats, &QPushButton::clicked, spineNum, qOverload<>(&QLabel::clear));
        QObject::connect(sbpSlider, &QSlider::valueChanged, label_18, qOverload<int>(&QLabel::setNum));
        QObject::connect(spineFiller, &QSlider::valueChanged, label_19, qOverload<int>(&QLabel::setNum));
        QObject::connect(filopodiumSTD, &QSlider::valueChanged, label_20, qOverload<int>(&QLabel::setNum));
        QObject::connect(hnjSlider, &QSlider::valueChanged, label_21, qOverload<int>(&QLabel::setNum));

        tabWidget1->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);
        spinelocalisation->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "2-D SPine ANalysis", nullptr));
        actionLoad_Image->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
        actionLoad_Image_Folder->setText(QCoreApplication::translate("MainWindow", "Load Image Folder", nullptr));
        actionClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        actionSave_Current_Image->setText(QCoreApplication::translate("MainWindow", "Save Current Image", nullptr));
        actionBinary->setText(QCoreApplication::translate("MainWindow", "Binary", nullptr));
        actionOriginal->setText(QCoreApplication::translate("MainWindow", "Original", nullptr));
        actionNext_Image->setText(QCoreApplication::translate("MainWindow", "Next Image", nullptr));
        actionAuto->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        useCurrentImage->setText(QCoreApplication::translate("MainWindow", "Use Current Image", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        btnMeanDenoise->setText(QCoreApplication::translate("MainWindow", "Denoise", nullptr));
        toolBox_3->setItemText(toolBox_3->indexOf(meanFilter), QCoreApplication::translate("MainWindow", "Mean Filter", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        btnMedianDenoise->setText(QCoreApplication::translate("MainWindow", "Denoise", nullptr));
        toolBox_3->setItemText(toolBox_3->indexOf(medianFilter), QCoreApplication::translate("MainWindow", "Median Filter", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Sigma", nullptr));
        btnGaussianDenoise->setText(QCoreApplication::translate("MainWindow", "Denoise", nullptr));
        toolBox_3->setItemText(toolBox_3->indexOf(gaussianFilter), QCoreApplication::translate("MainWindow", "Gaussian Filter", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Diameter", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Sigma Color", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Sigma Space", nullptr));
        btnBilateralFilter->setText(QCoreApplication::translate("MainWindow", "Denoise", nullptr));
        toolBox_3->setItemText(toolBox_3->indexOf(bilateralFilter), QCoreApplication::translate("MainWindow", "Bilateral Filter", nullptr));
        btnNoise2Void->setText(QCoreApplication::translate("MainWindow", "Denoise", nullptr));
        toolBox_3->setItemText(toolBox_3->indexOf(n2v), QCoreApplication::translate("MainWindow", "Noise2Void", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Denoising), QCoreApplication::translate("MainWindow", "Denoising Image", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Cut-Off Threshold", nullptr));
        globalThresholdingBinarize->setText(QCoreApplication::translate("MainWindow", "Binarize", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(globalThresholding), QCoreApplication::translate("MainWindow", "Global Thresholding", nullptr));
        otsuBinarise->setText(QCoreApplication::translate("MainWindow", "Global Otsu Binarize", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(otsu), QCoreApplication::translate("MainWindow", "OTSU", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "2-Means Clustering", nullptr));
        twoMeansBinarize->setText(QCoreApplication::translate("MainWindow", "Binarize", nullptr));
        flip->setText(QCoreApplication::translate("MainWindow", "Flip", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(otherTechniques), QCoreApplication::translate("MainWindow", "Clustering Based Thresholding", nullptr));
        unetBinarize->setText(QCoreApplication::translate("MainWindow", "Binarize", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(unet), QCoreApplication::translate("MainWindow", "UNET Based Binarization", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Binarization), QCoreApplication::translate("MainWindow", "Binarizing Image", nullptr));
        whiteBlobRemoval->setText(QCoreApplication::translate("MainWindow", "Remove Isolated White Blobs", nullptr));
        holeRemoval->setText(QCoreApplication::translate("MainWindow", "Remove Isolated Black Holes", nullptr));
        spotRemoval->setText(QCoreApplication::translate("MainWindow", "Remove Spots at Once", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(SpuriousPatchElimination), QCoreApplication::translate("MainWindow", "Eliminating Spurious Patches", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(Image_Processing), QCoreApplication::translate("MainWindow", "Image Processing", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Blum's Grass Fire Propagation", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Collision Impact Threshold", nullptr));
        btnComputeCI->setText(QCoreApplication::translate("MainWindow", "View Collision Impact Map", nullptr));
        dt->setTitle(QCoreApplication::translate("MainWindow", "Distance Transform", nullptr));
        btnComputeDT->setText(QCoreApplication::translate("MainWindow", "View Distance Transform Map", nullptr));
        rbnBin->setText(QCoreApplication::translate("MainWindow", "on Binary Image", nullptr));
        toolBox_4->setItemText(toolBox_4->indexOf(basicPreprocessing), QCoreApplication::translate("MainWindow", "Preprocessing", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Manual Loop Cutter", nullptr));
        selectPoints->setText(QCoreApplication::translate("MainWindow", "Select Points", nullptr));
        completeSkel->setText(QCoreApplication::translate("MainWindow", "Complete Skeleton", nullptr));
        finalSkel->setText(QCoreApplication::translate("MainWindow", "Final Skeleton", nullptr));
        primarySkel->setText(QCoreApplication::translate("MainWindow", "Primary Skeleton", nullptr));
        BreakLoop->setText(QCoreApplication::translate("MainWindow", "Break Loop", nullptr));
        toolBox_4->setItemText(toolBox_4->indexOf(skeletonization), QCoreApplication::translate("MainWindow", "Skeletonization", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Number of Iterations", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Set &alpha; ", nullptr));
        dendriteExtraction->setText(QCoreApplication::translate("MainWindow", "Dendrite Extraction", nullptr));
        setManualDE->setText(QCoreApplication::translate("MainWindow", "Set Dendrite End Point Manually", nullptr));
        spinelocalisation->setTabText(spinelocalisation->indexOf(dendriteExtractionTab), QCoreApplication::translate("MainWindow", "Dendrite Extraction", nullptr));
        rBtnPrimarySegmentation->setText(QCoreApplication::translate("MainWindow", " Primary Segmented Image", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Set SBP", nullptr));
        label_18->setText(QString());
        showSpine->setItemText(showSpine->indexOf(showSpinePage1), QCoreApplication::translate("MainWindow", "Spine Base Point (SBP)", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Fill Spine Mass", nullptr));
        showCHP->setText(QCoreApplication::translate("MainWindow", "Show CHP", nullptr));
        label_19->setText(QString());
        showSpine->setItemText(showSpine->indexOf(page), QCoreApplication::translate("MainWindow", "Central Head Point (CHP)", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Allowed Standard Deviation for Filopodium", nullptr));
        label_20->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Set Head Neck Junction Point", nullptr));
        label_21->setText(QString());
        showSpine->setItemText(showSpine->indexOf(page_2), QCoreApplication::translate("MainWindow", "Head Neck Junction (HNJ)", nullptr));
        spinelocalisation->setTabText(spinelocalisation->indexOf(segmentation), QCoreApplication::translate("MainWindow", "Compartmentalization", nullptr));
        performDefaultSpineLocalisation->setText(QCoreApplication::translate("MainWindow", "Perform Spine Localisation using Default Parameters", nullptr));
        toolBox_4->setItemText(toolBox_4->indexOf(spineLocalisation), QCoreApplication::translate("MainWindow", "Spine Localisation", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(Settings), QCoreApplication::translate("MainWindow", "DESC", nullptr));
        wholeStats->setText(QString());
        displayNetStats->setText(QCoreApplication::translate("MainWindow", "Display Net Statistics", nullptr));
        displaySpineNumber->setText(QCoreApplication::translate("MainWindow", "Display All Spine Number", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QCoreApplication::translate("MainWindow", "Global Statistics", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Enter Spine Number", nullptr));
        individualStats->setText(QString());
        displayIndividualSpineInformation->setText(QCoreApplication::translate("MainWindow", "Display Spine Information", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QCoreApplication::translate("MainWindow", "Individual Spine Statistics", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(Results), QCoreApplication::translate("MainWindow", "MorphoAnalyser", nullptr));
        mouseInfo->setTitle(QCoreApplication::translate("MainWindow", "General Info", nullptr));
        filename->setText(QString());
        label_24->setText(QCoreApplication::translate("MainWindow", "File Name", nullptr));
        coordinates->setText(QString());
        spineNum->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "Mouse Coordinate", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Set Resolution", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Spine Number", nullptr));
        lblImage->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "\302\251  Dr. Subhadip Basu, Dept. of CSE, Jadavpur University, India", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Save", nullptr));
        folderPath->setPlaceholderText(QCoreApplication::translate("MainWindow", "Save Folder Location", nullptr));
        browse->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        saveNet->setText(QCoreApplication::translate("MainWindow", "Save Net Summary", nullptr));
        saveAllSpines->setText(QCoreApplication::translate("MainWindow", "Save All Spines Stats", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
