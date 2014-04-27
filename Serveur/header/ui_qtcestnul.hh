/********************************************************************************
** Form generated from reading UI file 'qtcestnul.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCESTNUL_H
#define UI_QTCESTNUL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qtcestnul
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qtcestnul)
    {
        if (Qtcestnul->objectName().isEmpty())
            Qtcestnul->setObjectName(QStringLiteral("Qtcestnul"));
        Qtcestnul->resize(530, 244);
        centralWidget = new QWidget(Qtcestnul);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(220, 140, 111, 41));
        pushButton->setAutoDefault(false);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 20, 321, 111));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Qtcestnul->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qtcestnul);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 530, 25));
        Qtcestnul->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qtcestnul);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qtcestnul->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qtcestnul);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qtcestnul->setStatusBar(statusBar);

        retranslateUi(Qtcestnul);
        QObject::connect(pushButton, SIGNAL(clicked()), Qtcestnul, SLOT(close()));

        QMetaObject::connectSlotsByName(Qtcestnul);
    } // setupUi

    void retranslateUi(QMainWindow *Qtcestnul)
    {
        Qtcestnul->setWindowTitle(QApplication::translate("Qtcestnul", "Qtcestnul", 0));
        pushButton->setText(QApplication::translate("Qtcestnul", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class Qtcestnul: public Ui_Qtcestnul {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCESTNUL_H
