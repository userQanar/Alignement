/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButtonNW;
    QRadioButton *radioButtonNWAffin;
    QRadioButton *radioButtonSW;
    QRadioButton *radioButtonSWaffin;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSequenceB;
    QLabel *labelHeaderB;
    QLabel *labelSequenceB;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSequenceA;
    QLabel *labelHeaderA;
    QLabel *labelSequenceA;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineEditMatch;
    QLineEdit *lineEditMismatch;
    QLineEdit *lineEditgapPenalty;
    QLineEdit *lineEditGapExtensionPenalty;
    QTabWidget *Tabs;
    QWidget *TabAlignment;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonPerformAlignment;
    QPlainTextEdit *plainTextEditMatrices;
    QLabel *labelAlign;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelResultA;
    QLabel *labelResultB;
    QWidget *TabDotplot;
    QPlainTextEdit *plainTextEditDotplot;
    QPushButton *pushButtonDotplot;
    QHBoxLayout *horizontalLayout_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(845, 599);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        radioButtonNW = new QRadioButton(centralWidget);
        radioButtonNW->setObjectName(QString::fromUtf8("radioButtonNW"));
        radioButtonNW->setChecked(true);

        verticalLayout_6->addWidget(radioButtonNW);

        radioButtonNWAffin = new QRadioButton(centralWidget);
        radioButtonNWAffin->setObjectName(QString::fromUtf8("radioButtonNWAffin"));

        verticalLayout_6->addWidget(radioButtonNWAffin);

        radioButtonSW = new QRadioButton(centralWidget);
        radioButtonSW->setObjectName(QString::fromUtf8("radioButtonSW"));

        verticalLayout_6->addWidget(radioButtonSW);

        radioButtonSWaffin = new QRadioButton(centralWidget);
        radioButtonSWaffin->setObjectName(QString::fromUtf8("radioButtonSWaffin"));

        verticalLayout_6->addWidget(radioButtonSWaffin);


        gridLayout->addLayout(verticalLayout_6, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonSequenceB = new QPushButton(centralWidget);
        pushButtonSequenceB->setObjectName(QString::fromUtf8("pushButtonSequenceB"));
        pushButtonSequenceB->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(pushButtonSequenceB);

        labelHeaderB = new QLabel(centralWidget);
        labelHeaderB->setObjectName(QString::fromUtf8("labelHeaderB"));
        labelHeaderB->setMinimumSize(QSize(100, 20));

        horizontalLayout->addWidget(labelHeaderB);


        verticalLayout_2->addLayout(horizontalLayout);

        labelSequenceB = new QLabel(centralWidget);
        labelSequenceB->setObjectName(QString::fromUtf8("labelSequenceB"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSequenceB->sizePolicy().hasHeightForWidth());
        labelSequenceB->setSizePolicy(sizePolicy);
        labelSequenceB->setMaximumSize(QSize(800, 16777215));
        labelSequenceB->setTextFormat(Qt::RichText);
        labelSequenceB->setScaledContents(true);
        labelSequenceB->setWordWrap(true);

        verticalLayout_2->addWidget(labelSequenceB);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonSequenceA = new QPushButton(centralWidget);
        pushButtonSequenceA->setObjectName(QString::fromUtf8("pushButtonSequenceA"));
        pushButtonSequenceA->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(pushButtonSequenceA);

        labelHeaderA = new QLabel(centralWidget);
        labelHeaderA->setObjectName(QString::fromUtf8("labelHeaderA"));
        labelHeaderA->setMinimumSize(QSize(100, 20));

        horizontalLayout_2->addWidget(labelHeaderA);


        verticalLayout->addLayout(horizontalLayout_2);

        labelSequenceA = new QLabel(centralWidget);
        labelSequenceA->setObjectName(QString::fromUtf8("labelSequenceA"));
        sizePolicy.setHeightForWidth(labelSequenceA->sizePolicy().hasHeightForWidth());
        labelSequenceA->setSizePolicy(sizePolicy);
        labelSequenceA->setMaximumSize(QSize(800, 16777215));
        labelSequenceA->setTextFormat(Qt::RichText);
        labelSequenceA->setScaledContents(false);
        labelSequenceA->setWordWrap(true);

        verticalLayout->addWidget(labelSequenceA);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, -1, -1, -1);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_7->addWidget(label_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_7->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_7->addWidget(label_4);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_7->addWidget(label_5);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        lineEditMatch = new QLineEdit(centralWidget);
        lineEditMatch->setObjectName(QString::fromUtf8("lineEditMatch"));

        verticalLayout_8->addWidget(lineEditMatch);

        lineEditMismatch = new QLineEdit(centralWidget);
        lineEditMismatch->setObjectName(QString::fromUtf8("lineEditMismatch"));

        verticalLayout_8->addWidget(lineEditMismatch);

        lineEditgapPenalty = new QLineEdit(centralWidget);
        lineEditgapPenalty->setObjectName(QString::fromUtf8("lineEditgapPenalty"));

        verticalLayout_8->addWidget(lineEditgapPenalty);

        lineEditGapExtensionPenalty = new QLineEdit(centralWidget);
        lineEditGapExtensionPenalty->setObjectName(QString::fromUtf8("lineEditGapExtensionPenalty"));
        lineEditGapExtensionPenalty->setEnabled(true);

        verticalLayout_8->addWidget(lineEditGapExtensionPenalty);


        horizontalLayout_3->addLayout(verticalLayout_8);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        Tabs = new QTabWidget(centralWidget);
        Tabs->setObjectName(QString::fromUtf8("Tabs"));
        TabAlignment = new QWidget();
        TabAlignment->setObjectName(QString::fromUtf8("TabAlignment"));
        verticalLayout_5 = new QVBoxLayout(TabAlignment);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        pushButtonPerformAlignment = new QPushButton(TabAlignment);
        pushButtonPerformAlignment->setObjectName(QString::fromUtf8("pushButtonPerformAlignment"));
        pushButtonPerformAlignment->setEnabled(true);
        pushButtonPerformAlignment->setMinimumSize(QSize(250, 0));
        pushButtonPerformAlignment->setMaximumSize(QSize(250, 16777215));

        verticalLayout_5->addWidget(pushButtonPerformAlignment);

        plainTextEditMatrices = new QPlainTextEdit(TabAlignment);
        plainTextEditMatrices->setObjectName(QString::fromUtf8("plainTextEditMatrices"));
        QFont font;
        plainTextEditMatrices->setFont(font);

        verticalLayout_5->addWidget(plainTextEditMatrices);

        labelAlign = new QLabel(TabAlignment);
        labelAlign->setObjectName(QString::fromUtf8("labelAlign"));
        labelAlign->setFont(font);

        verticalLayout_5->addWidget(labelAlign);

        label = new QLabel(TabAlignment);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout_5->addWidget(label);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelResultA = new QLabel(TabAlignment);
        labelResultA->setObjectName(QString::fromUtf8("labelResultA"));
        labelResultA->setFont(font);

        verticalLayout_4->addWidget(labelResultA);

        labelResultB = new QLabel(TabAlignment);
        labelResultB->setObjectName(QString::fromUtf8("labelResultB"));
        labelResultB->setFont(font);

        verticalLayout_4->addWidget(labelResultB);


        verticalLayout_5->addLayout(verticalLayout_4);

        Tabs->addTab(TabAlignment, QString());
        TabDotplot = new QWidget();
        TabDotplot->setObjectName(QString::fromUtf8("TabDotplot"));
        plainTextEditDotplot = new QPlainTextEdit(TabDotplot);
        plainTextEditDotplot->setObjectName(QString::fromUtf8("plainTextEditDotplot"));
        plainTextEditDotplot->setGeometry(QRect(10, 40, 801, 161));
        plainTextEditDotplot->setFont(font);
        pushButtonDotplot = new QPushButton(TabDotplot);
        pushButtonDotplot->setObjectName(QString::fromUtf8("pushButtonDotplot"));
        pushButtonDotplot->setGeometry(QRect(10, 10, 251, 23));
        pushButtonDotplot->setMinimumSize(QSize(251, 23));
        pushButtonDotplot->setMaximumSize(QSize(251, 16777215));
        Tabs->addTab(TabDotplot, QString());

        gridLayout->addWidget(Tabs, 5, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 845, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Bioinformatics", nullptr));
        radioButtonNW->setText(QApplication::translate("MainWindow", "Needleman-Wunsch linear", nullptr));
        radioButtonNWAffin->setText(QApplication::translate("MainWindow", "Needleman-Wunsch affin", nullptr));
        radioButtonSW->setText(QApplication::translate("MainWindow", "Smith-Waterman linear", nullptr));
        radioButtonSWaffin->setText(QApplication::translate("MainWindow", "Smith-Waterman affin", nullptr));
        pushButtonSequenceB->setText(QApplication::translate("MainWindow", "Sequence B", nullptr));
        labelHeaderB->setText(QString());
        labelSequenceB->setText(QString());
        pushButtonSequenceA->setText(QApplication::translate("MainWindow", "Sequence A", nullptr));
        labelHeaderA->setText(QString());
        labelSequenceA->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "match", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "mismatch", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "gapPenalty", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "gapExtensionPenalty", nullptr));
        lineEditMatch->setText(QApplication::translate("MainWindow", "2", nullptr));
        lineEditMismatch->setText(QApplication::translate("MainWindow", "-1", nullptr));
        lineEditgapPenalty->setText(QApplication::translate("MainWindow", "-1", nullptr));
        lineEditGapExtensionPenalty->setText(QApplication::translate("MainWindow", "-1", nullptr));
        pushButtonPerformAlignment->setText(QApplication::translate("MainWindow", "Perform Alignment", nullptr));
        labelAlign->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Resultierendes Alignment", nullptr));
        labelResultA->setText(QString());
        labelResultB->setText(QString());
        Tabs->setTabText(Tabs->indexOf(TabAlignment), QApplication::translate("MainWindow", "Alignment", nullptr));
        pushButtonDotplot->setText(QApplication::translate("MainWindow", "Print Dotplot", nullptr));
        Tabs->setTabText(Tabs->indexOf(TabDotplot), QApplication::translate("MainWindow", "Dotplot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
