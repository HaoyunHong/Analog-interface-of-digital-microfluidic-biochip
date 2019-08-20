#include "settingwidget.h"
#include "ui_settingwidget.h"


int SettingWidget:: row =0;
int SettingWidget:: col =0;

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    this->resize(1200,900);

    ui->rowSpinBox->setMinimum(1);
    ui->colSpinBox->setMinimum(1);

    connect(ui->resetButton,&QPushButton::released,
            [=]()
    {
        //question返回的是枚举类型
        int ret = QMessageBox::question(this,"question","Do you want to reset the properties?",QMessageBox::Yes | QMessageBox::No);
        switch(ret)
        {
        case QMessageBox::Yes:
            //把原来所有值都变成初始值
            ui->rowSpinBox->setValue(1);
            ui->colSpinBox->setValue(1);
            break;
        case QMessageBox::No:
            //就不做任何重置的改动
            break;
        default:
            break;
        }
    });

    connect(this,&SettingWidget::setAgain,
            [=]()
    {
        //question返回的是枚举类型
        int ret = QMessageBox::question(this,"problem","Please make sure that row number or col number is larger than 3!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    });


}

void SettingWidget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this,"question","Do you want to quit setting the properties?",QMessageBox::Yes|QMessageBox::No);
    switch(ret)
    {
        case QMessageBox::Yes:
            emit backToMainWindow();
            break;
        case QMessageBox::No:
            emit backToSettingWidget();
            event->ignore();
            break;
        default:
            break;
    }
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::on_confirmButton_clicked()
{
    if(row<=3 && col<=3)
    {
        emit setAgain();
        return;
    }
    else {
        emit confirmSignal(row,col);
        qDebug()<<"confirmSignal";
    }
}

void SettingWidget::on_resetButton_clicked()
{
    emit resetSignal();
    qDebug()<<"resetSignal";
}

void SettingWidget::on_rowSpinBox_valueChanged(const QString &arg1)
{
    row = arg1.toInt();
    qDebug()<<"row = "<<row;
}


void SettingWidget::on_colSpinBox_valueChanged(const QString &arg2)
{
    col = arg2.toInt();
    qDebug()<<"col = "<<col;
}
