/********************************************************************************
** Form generated from reading UI file 'setinputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETINPUTDIALOG_H
#define UI_SETINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetInputDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *xSpinBox;
    QLabel *label_2;
    QSpinBox *ySpinBox;
    QSpacerItem *horizontalSpacer_5;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *SetInputDialog)
    {
        if (SetInputDialog->objectName().isEmpty())
            SetInputDialog->setObjectName(QString::fromUtf8("SetInputDialog"));
        SetInputDialog->resize(400, 300);
        gridLayout = new QGridLayout(SetInputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 49, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(95, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        frame = new QFrame(SetInputDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        xSpinBox = new QSpinBox(frame);
        xSpinBox->setObjectName(QString::fromUtf8("xSpinBox"));

        horizontalLayout_2->addWidget(xSpinBox);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        ySpinBox = new QSpinBox(frame);
        ySpinBox->setObjectName(QString::fromUtf8("ySpinBox"));

        horizontalLayout_2->addWidget(ySpinBox);


        gridLayout->addWidget(frame, 1, 1, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(94, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        progressBar = new QProgressBar(SetInputDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 2, 1, 1);

        widget = new QWidget(SetInputDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addButton = new QPushButton(widget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout->addWidget(addButton);

        horizontalSpacer_2 = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        okButton = new QPushButton(widget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addWidget(widget, 3, 0, 1, 4);

        verticalSpacer_3 = new QSpacerItem(20, 49, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);


        retranslateUi(SetInputDialog);

        QMetaObject::connectSlotsByName(SetInputDialog);
    } // setupUi

    void retranslateUi(QDialog *SetInputDialog)
    {
        SetInputDialog->setWindowTitle(QCoreApplication::translate("SetInputDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetInputDialog", "x:", nullptr));
        label_2->setText(QCoreApplication::translate("SetInputDialog", "y:", nullptr));
        addButton->setText(QCoreApplication::translate("SetInputDialog", "Add", nullptr));
        okButton->setText(QCoreApplication::translate("SetInputDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetInputDialog: public Ui_SetInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETINPUTDIALOG_H
