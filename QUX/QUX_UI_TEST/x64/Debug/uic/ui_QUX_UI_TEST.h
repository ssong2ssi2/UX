/********************************************************************************
** Form generated from reading UI file 'QUX_UI_TEST.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUX_UI_TEST_H
#define UI_QUX_UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QUX_UI_TESTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QUX_UI_TESTClass)
    {
        if (QUX_UI_TESTClass->objectName().isEmpty())
            QUX_UI_TESTClass->setObjectName(QString::fromUtf8("QUX_UI_TESTClass"));
        QUX_UI_TESTClass->resize(600, 400);
        menuBar = new QMenuBar(QUX_UI_TESTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QUX_UI_TESTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QUX_UI_TESTClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QUX_UI_TESTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QUX_UI_TESTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QUX_UI_TESTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QUX_UI_TESTClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QUX_UI_TESTClass->setStatusBar(statusBar);

        retranslateUi(QUX_UI_TESTClass);

        QMetaObject::connectSlotsByName(QUX_UI_TESTClass);
    } // setupUi

    void retranslateUi(QMainWindow *QUX_UI_TESTClass)
    {
        QUX_UI_TESTClass->setWindowTitle(QCoreApplication::translate("QUX_UI_TESTClass", "QUX_UI_TEST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QUX_UI_TESTClass: public Ui_QUX_UI_TESTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUX_UI_TEST_H
