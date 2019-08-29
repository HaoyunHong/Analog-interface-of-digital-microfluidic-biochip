/********************************************************************************
** Form generated from reading UI file 'settingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWidget
{
public:
    QLabel *titleLabel;
    QFrame *frame;
    QLabel *rowNum;
    QLabel *colNum;
    QSpinBox *rowSpinBox;
    QSpinBox *colSpinBox;
    QPushButton *confirmButton;
    QLabel *rcCheckLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QLabel *label_2;
    QSpinBox *inpNumSpinBox;
    QPushButton *inOKButton;
    QLabel *inputCheckLabel;
    QWidget *widget_3;
    QLabel *label_3;
    QSpinBox *outXSpinBox;
    QSpinBox *outYSpinBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *outputCheckLabel;
    QPushButton *confirmButton_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;
    QSpacerItem *horizontalSpacer_11;

    void setupUi(QWidget *SettingWidget)
    {
        if (SettingWidget->objectName().isEmpty())
            SettingWidget->setObjectName(QString::fromUtf8("SettingWidget"));
        SettingWidget->resize(1096, 682);
        titleLabel = new QLabel(SettingWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(280, 40, 551, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setLayoutDirection(Qt::LeftToRight);
        titleLabel->setAlignment(Qt::AlignCenter);
        frame = new QFrame(SettingWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(310, 110, 471, 111));
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        rowNum = new QLabel(frame);
        rowNum->setObjectName(QString::fromUtf8("rowNum"));
        rowNum->setGeometry(QRect(12, 12, 161, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        rowNum->setFont(font1);
        colNum = new QLabel(frame);
        colNum->setObjectName(QString::fromUtf8("colNum"));
        colNum->setGeometry(QRect(10, 70, 191, 31));
        colNum->setFont(font1);
        rowSpinBox = new QSpinBox(frame);
        rowSpinBox->setObjectName(QString::fromUtf8("rowSpinBox"));
        rowSpinBox->setGeometry(QRect(210, 20, 46, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        rowSpinBox->setFont(font2);
        colSpinBox = new QSpinBox(frame);
        colSpinBox->setObjectName(QString::fromUtf8("colSpinBox"));
        colSpinBox->setGeometry(QRect(210, 80, 46, 21));
        colSpinBox->setFont(font2);
        confirmButton = new QPushButton(frame);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setGeometry(QRect(330, 40, 93, 28));
        confirmButton->setFont(font2);
        rcCheckLabel = new QLabel(frame);
        rcCheckLabel->setObjectName(QString::fromUtf8("rcCheckLabel"));
        rcCheckLabel->setGeometry(QRect(420, 40, 51, 31));
        rcCheckLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/image/correct.png")));
        rcCheckLabel->setScaledContents(true);
        widget = new QWidget(SettingWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(1063, 456, 22, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(SettingWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(310, 260, 471, 51));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 191, 28));
        label_2->setFont(font1);
        inpNumSpinBox = new QSpinBox(widget_2);
        inpNumSpinBox->setObjectName(QString::fromUtf8("inpNumSpinBox"));
        inpNumSpinBox->setGeometry(QRect(210, 20, 46, 21));
        inpNumSpinBox->setFont(font2);
        inOKButton = new QPushButton(widget_2);
        inOKButton->setObjectName(QString::fromUtf8("inOKButton"));
        inOKButton->setGeometry(QRect(330, 20, 93, 28));
        inOKButton->setFont(font2);
        inputCheckLabel = new QLabel(widget_2);
        inputCheckLabel->setObjectName(QString::fromUtf8("inputCheckLabel"));
        inputCheckLabel->setGeometry(QRect(420, 10, 51, 31));
        inputCheckLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/image/correct.png")));
        inputCheckLabel->setScaledContents(true);
        widget_3 = new QWidget(SettingWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(310, 350, 481, 51));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 171, 31));
        label_3->setFont(font1);
        outXSpinBox = new QSpinBox(widget_3);
        outXSpinBox->setObjectName(QString::fromUtf8("outXSpinBox"));
        outXSpinBox->setGeometry(QRect(190, 20, 46, 21));
        outXSpinBox->setFont(font2);
        outYSpinBox = new QSpinBox(widget_3);
        outYSpinBox->setObjectName(QString::fromUtf8("outYSpinBox"));
        outYSpinBox->setGeometry(QRect(270, 20, 46, 21));
        outYSpinBox->setFont(font2);
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 20, 16, 16));
        label_4->setFont(font2);
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 10, 20, 31));
        label_5->setFont(font2);
        outputCheckLabel = new QLabel(widget_3);
        outputCheckLabel->setObjectName(QString::fromUtf8("outputCheckLabel"));
        outputCheckLabel->setGeometry(QRect(420, 20, 51, 31));
        outputCheckLabel->setPixmap(QPixmap(QString::fromUtf8(":/image/image/correct.png")));
        outputCheckLabel->setScaledContents(true);
        confirmButton_2 = new QPushButton(widget_3);
        confirmButton_2->setObjectName(QString::fromUtf8("confirmButton_2"));
        confirmButton_2->setGeometry(QRect(330, 20, 93, 28));
        confirmButton_2->setFont(font2);
        widget_4 = new QWidget(SettingWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(260, 440, 657, 50));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(115, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        saveButton = new QPushButton(widget_4);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setFont(font2);

        horizontalLayout_2->addWidget(saveButton);

        horizontalSpacer_11 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);


        retranslateUi(SettingWidget);

        QMetaObject::connectSlotsByName(SettingWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingWidget)
    {
        SettingWidget->setWindowTitle(QCoreApplication::translate("SettingWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("SettingWidget", "Please enter the following properties", nullptr));
        rowNum->setText(QCoreApplication::translate("SettingWidget", "row number:", nullptr));
        colNum->setText(QCoreApplication::translate("SettingWidget", "colmun number:", nullptr));
        confirmButton->setText(QCoreApplication::translate("SettingWidget", "confirm", nullptr));
        rcCheckLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("SettingWidget", "input number:", nullptr));
        inOKButton->setText(QCoreApplication::translate("SettingWidget", "continue", nullptr));
        inputCheckLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("SettingWidget", "output point:", nullptr));
        label_4->setText(QCoreApplication::translate("SettingWidget", "x:", nullptr));
        label_5->setText(QCoreApplication::translate("SettingWidget", "y:", nullptr));
        outputCheckLabel->setText(QString());
        confirmButton_2->setText(QCoreApplication::translate("SettingWidget", "confirm", nullptr));
        saveButton->setText(QCoreApplication::translate("SettingWidget", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWidget: public Ui_SettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
