/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(428, 344);
        QFont font;
        font.setFamily(QStringLiteral("Serif"));
        font.setPointSize(20);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Serif"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        progressBar->setFont(font1);
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QStringLiteral(""));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Vertical);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::BottomToTop);

        horizontalLayout->addWidget(progressBar);

        horizontalSpacer = new QSpacerItem(38, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        progressBar_2 = new QProgressBar(centralWidget);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        sizePolicy.setHeightForWidth(progressBar_2->sizePolicy().hasHeightForWidth());
        progressBar_2->setSizePolicy(sizePolicy);
        progressBar_2->setFont(font1);
        progressBar_2->setAutoFillBackground(false);
        progressBar_2->setValue(24);
        progressBar_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        progressBar_2->setTextVisible(false);
        progressBar_2->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        progressBar->setFormat(QApplication::translate("MainWindow", "%p CM", nullptr));
        progressBar_2->setFormat(QApplication::translate("MainWindow", "%p CM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
