#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    this->resize(800,600);

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

    //connect();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::on_confirmButton_clicked()
{
    int row = ui->rowSpinBox->value();
    int col = ui->colSpinBox->value();
    if(row<=3 && col<=3)
    {
        emit setAgain();
        return;
    }
    else {
        qDebug()<<"Here!";
        qDebug()<<"row = "<<row;
        qDebug()<<"col = "<<col;
        emit confirmSignal(row,col);
        qDebug()<<"Success confirmSignal";
    }
}

void SettingWidget::on_resetButton_clicked()
{
    emit resetSignal();
    qDebug()<<"resetSignal";
}

void SettingWidget::on_inOKButton_clicked()
{
    int n = ui->inpNumSpinBox->value();
    emit setInputPointsNumberSignal(n);

    dlg = new SetInputDialog(this);
    dlg->setInputNum(n);
    connect(dlg,&SetInputDialog::setInputPointSignal,this,&SettingWidget::sendInputPoint);
    dlg->exec();
    qDebug()<<"^_^ setInputPointsNumberSignal";
}
