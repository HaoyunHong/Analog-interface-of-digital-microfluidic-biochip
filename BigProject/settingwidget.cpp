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
    ui->inpNumSpinBox->setMinimum(1);
    ui->outXSpinBox->setMinimum(1);
    ui->outYSpinBox->setMinimum(1);

    ui->confirmButton->setStyleSheet("background: rgb(245,150,170)");

    ui->inpNumSpinBox->setEnabled(false);
    ui->inOKButton->setEnabled(false);
    ui->outXSpinBox->setEnabled(false);
    ui->outYSpinBox->setEnabled(false);
    ui->inputCheckLabel->setEnabled(false);
    ui->rcCheckLabel->setEnabled(false);
    ui->outputCheckLabel->setEnabled(false);

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
        int ret = QMessageBox::warning(this,"Error","Please make sure that row number or col number is larger than 3!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    });


}

void SettingWidget::sendDuplicate(bool flag)
{
    dlg->checkDuplicate(flag);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::on_confirmButton_clicked()
{
    qDebug()<<"confirmButton clicked!";
    int row = ui->rowSpinBox->value();
    int col = ui->colSpinBox->value();

    if(row<=3 && col<=3)
    {
        qDebug()<<"What Here!";
        ui->rcCheckLabel->setEnabled(false);

        emit setAgain();
        return;
    }
    else {
        int ret = QMessageBox::information(this,"Tips","Now you can enter the number of input points with their postions and the postion of an output point!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
        ui->confirmButton->setStyleSheet("background: rgb(144,180,75)");
        ui->rcCheckLabel->setEnabled(true);
        dlg = new SetInputDialog(this);
        qDebug()<<"dlg new!";
        dlg->knowRowAndCol(row,col);
        qDebug()<<"row and col set! row = "<<row<<", col = "<<col;
        ui->inpNumSpinBox->setEnabled(true);
        ui->inOKButton->setEnabled(true);
        ui->inOKButton->setStyleSheet("background: rgb(245,150,170)");
        ui->outXSpinBox->setEnabled(true);
        ui->outYSpinBox->setEnabled(true);

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

    //dlg = new SetInputDialog(this);
    dlg->setInputNum(n);
    connect(dlg,&SetInputDialog::setInputPointSignal,this,&SettingWidget::sendInputPoint);
    dlg->exec();
    qDebug()<<"^_^ setInputPointsNumberSignal";

    connect(dlg,&SetInputDialog::InFinishedSignal,
            [=]()
    {
        ui->inOKButton->setStyleSheet("background: rgb(144,180,75)");
        ui->inputCheckLabel->setEnabled(true);
        qDebug()<<"input setting finished!";
    });

    connect(this,&SettingWidget::setAgain,
            [=]()
    {
        dlg->resetInputPoints();
    });
}
