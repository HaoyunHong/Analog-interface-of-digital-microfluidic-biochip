/********************************************************************************
** Form generated from reading UI file 'mymainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINWINDOW_H
#define UI_MYMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myMainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QPushButton *lastButton;
    QPushButton *nextButton;
    QPushButton *resetButton;
    QPushButton *playButton;
    QCheckBox *limitedCheckBox;
    QCheckBox *cleanCheckBox;
    QWidget *widget;
    QLabel *commandViewerlabel;
    QTextEdit *commandTextEdit;
    QLCDNumber *lcdNumber;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myMainWindow)
    {
        if (myMainWindow->objectName().isEmpty())
            myMainWindow->setObjectName(QString::fromUtf8("myMainWindow"));
        myMainWindow->resize(1200, 900);
        centralWidget = new QWidget(myMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(838, 11, 351, 461));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(780, 560, 421, 221));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lastButton = new QPushButton(frame);
        lastButton->setObjectName(QString::fromUtf8("lastButton"));
        lastButton->setGeometry(QRect(80, 10, 93, 42));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lastButton->sizePolicy().hasHeightForWidth());
        lastButton->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lastButton->setFont(font);
        nextButton = new QPushButton(frame);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(80, 80, 93, 42));
        sizePolicy1.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy1);
        nextButton->setFont(font);
        resetButton = new QPushButton(frame);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(240, 80, 93, 42));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy2);
        resetButton->setFont(font);
        playButton = new QPushButton(frame);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(238, 12, 93, 42));
        sizePolicy2.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy2);
        playButton->setFont(font);
        limitedCheckBox = new QCheckBox(frame);
        limitedCheckBox->setObjectName(QString::fromUtf8("limitedCheckBox"));
        limitedCheckBox->setGeometry(QRect(250, 150, 107, 37));
        sizePolicy2.setHeightForWidth(limitedCheckBox->sizePolicy().hasHeightForWidth());
        limitedCheckBox->setSizePolicy(sizePolicy2);
        limitedCheckBox->setFont(font);
        cleanCheckBox = new QCheckBox(frame);
        cleanCheckBox->setObjectName(QString::fromUtf8("cleanCheckBox"));
        cleanCheckBox->setGeometry(QRect(80, 150, 161, 37));
        sizePolicy2.setHeightForWidth(cleanCheckBox->sizePolicy().hasHeightForWidth());
        cleanCheckBox->setSizePolicy(sizePolicy2);
        cleanCheckBox->setFont(font);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(770, 20, 431, 541));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        commandViewerlabel = new QLabel(widget);
        commandViewerlabel->setObjectName(QString::fromUtf8("commandViewerlabel"));
        commandViewerlabel->setGeometry(QRect(90, 10, 247, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        commandViewerlabel->setFont(font1);
        commandViewerlabel->setLayoutDirection(Qt::LeftToRight);
        commandViewerlabel->setAlignment(Qt::AlignCenter);
        commandTextEdit = new QTextEdit(widget);
        commandTextEdit->setObjectName(QString::fromUtf8("commandTextEdit"));
        commandTextEdit->setGeometry(QRect(70, 50, 291, 431));
        sizePolicy3.setHeightForWidth(commandTextEdit->sizePolicy().hasHeightForWidth());
        commandTextEdit->setSizePolicy(sizePolicy3);
        commandTextEdit->setFont(font);
        commandTextEdit->setReadOnly(true);
        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(180, 500, 71, 31));
        sizePolicy2.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy2);
        myMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 26));
        myMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        myMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        myMainWindow->setStatusBar(statusBar);

        retranslateUi(myMainWindow);

        QMetaObject::connectSlotsByName(myMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *myMainWindow)
    {
        myMainWindow->setWindowTitle(QCoreApplication::translate("myMainWindow", "myMainWindow", nullptr));
        lastButton->setText(QCoreApplication::translate("myMainWindow", "last", nullptr));
        nextButton->setText(QCoreApplication::translate("myMainWindow", "next", nullptr));
        resetButton->setText(QCoreApplication::translate("myMainWindow", "reset", nullptr));
        playButton->setText(QCoreApplication::translate("myMainWindow", "play", nullptr));
        limitedCheckBox->setText(QCoreApplication::translate("myMainWindow", "limited", nullptr));
        cleanCheckBox->setText(QCoreApplication::translate("myMainWindow", "Clean Mode", nullptr));
        commandViewerlabel->setText(QCoreApplication::translate("myMainWindow", "Command Viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myMainWindow: public Ui_myMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINWINDOW_H
