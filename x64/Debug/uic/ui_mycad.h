/********************************************************************************
** Form generated from reading UI file 'mycad.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCAD_H
#define UI_MYCAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mycadClass
{
public:
    QWidget *centralWidget;
    QPushButton *line_comp;
    QPushButton *clearall_comp;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *main_canvas_container;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mycadClass)
    {
        if (mycadClass->objectName().isEmpty())
            mycadClass->setObjectName(QString::fromUtf8("mycadClass"));
        mycadClass->resize(830, 699);
        centralWidget = new QWidget(mycadClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line_comp = new QPushButton(centralWidget);
        line_comp->setObjectName(QString::fromUtf8("line_comp"));
        line_comp->setGeometry(QRect(460, 90, 71, 21));
        clearall_comp = new QPushButton(centralWidget);
        clearall_comp->setObjectName(QString::fromUtf8("clearall_comp"));
        clearall_comp->setGeometry(QRect(460, 70, 71, 21));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 441, 401));
        main_canvas_container = new QHBoxLayout(horizontalLayoutWidget);
        main_canvas_container->setSpacing(6);
        main_canvas_container->setContentsMargins(11, 11, 11, 11);
        main_canvas_container->setObjectName(QString::fromUtf8("main_canvas_container"));
        main_canvas_container->setContentsMargins(0, 0, 0, 0);
        mycadClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mycadClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 830, 21));
        mycadClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mycadClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mycadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mycadClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mycadClass->setStatusBar(statusBar);

        retranslateUi(mycadClass);

        QMetaObject::connectSlotsByName(mycadClass);
    } // setupUi

    void retranslateUi(QMainWindow *mycadClass)
    {
        mycadClass->setWindowTitle(QCoreApplication::translate("mycadClass", "mycad", nullptr));
        line_comp->setText(QCoreApplication::translate("mycadClass", "Line", nullptr));
        clearall_comp->setText(QCoreApplication::translate("mycadClass", "Clear All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mycadClass: public Ui_mycadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCAD_H
