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
    ui->confirmButton_2->setStyleSheet("background: rgb(245,150,170)");

    ui->inpNumSpinBox->setEnabled(false);
    ui->inOKButton->setEnabled(false);
    ui->outXSpinBox->setEnabled(false);
    ui->outYSpinBox->setEnabled(false);
    ui->inputCheckLabel->setEnabled(false);
    ui->rcCheckLabel->setEnabled(false);
    ui->outputCheckLabel->setEnabled(false);
    ui->confirmButton_2->setEnabled(false);

    rcOK = false;
    inputOK = false;
    outputOK = true;

    rowNum = 0;
    colNum = 0;

    dlg = new SetInputDialog(this);

    connect(dlg,&SetInputDialog::InFinishedSignal,
            [=]()
    {
        inputOK = true;
        qDebug()<<"lllllll";
        ui->inOKButton->setEnabled(false);
        ui->inputCheckLabel->setEnabled(true);
        ui->inpNumSpinBox->setEnabled(false);
    });



    connect(this,&SettingWidget::setAgain,
            [=]()
    {
        //question返回的是枚举类型
        ui->inpNumSpinBox->setValue(1);
        ui->outXSpinBox->setValue(1);
        ui->outYSpinBox->setValue(1);
        ui->inpNumSpinBox->setEnabled(false);
        ui->outXSpinBox->setEnabled(false);
        ui->outYSpinBox->setEnabled(false);
        ui->inputCheckLabel->setEnabled(false);
        ui->rcCheckLabel->setEnabled(false);
        ui->outputCheckLabel->setEnabled(false);
        ui->confirmButton_2->setEnabled(false);
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

void SettingWidget::outIsOK(bool flag)
{
    outputOK = flag;
    qDebug()<<"outputOK~~ "<<outputOK;
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
        ui->confirmButton->setEnabled(true);
        emit setAgain();
        return;
    }
    else {
        rcOK = false;
        rowNum = row;
        colNum = col;

        rcOK = true;
        int ret = QMessageBox::information(this,"Tips","Now you can enter the following!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
        ui->confirmButton->setEnabled(false);
        ui->rcCheckLabel->setEnabled(true);

        qDebug()<<"dlg new!";
        dlg->knowRowAndCol(row,col);
        qDebug()<<"row and col set! row = "<<row<<", col = "<<col;
        ui->inpNumSpinBox->setEnabled(true);
        ui->inOKButton->setEnabled(true);
        ui->inOKButton->setStyleSheet("background: rgb(245,150,170)");
        ui->outXSpinBox->setEnabled(true);
        ui->outYSpinBox->setEnabled(true);
        ui->confirmButton_2->setEnabled(true);

        ui->rowSpinBox->setEnabled(false);
        ui->colSpinBox->setEnabled(false);

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
    qDebug()<<"setInputPointsNumberSignal";

}

void SettingWidget::on_saveButton_clicked()
{
    if(rcOK && inputOK && outputOK)
    {
        this->hide();
        ui->saveButton->setEnabled(false);
    }
    else if(!inputOK){
        int ret = QMessageBox::warning(this,"Undone","Input points setting undone!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
    }
    else if(!outputOK)
    {
        int ret = QMessageBox::warning(this,"Undone","Output point setting undone!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }

    }

}

void SettingWidget::on_confirmButton_2_clicked()
{
    int x = ui->outXSpinBox->value();
    int y = ui->outYSpinBox->value();
    emit outputCheckSignal(x,y);
    qDebug()<<"Checked! "<<"outputOK = "<<outputOK;
    if(x > rowNum || y > colNum)
    {
        int ret = QMessageBox::warning(this,"Error","The position of the output point out of range!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            ui->outXSpinBox->setValue(1);
            ui->outYSpinBox->setValue(1);
            break;
        default:
            break;
         }
    }
            else if(!outputOK)
            {
                int ret = QMessageBox::warning(this,"Error","The position of the output point is already taken!",QMessageBox::Ok);
                switch(ret)
                {
                case QMessageBox::Ok:
                    ui->outXSpinBox->setValue(1);
                    ui->outYSpinBox->setValue(1);
                    break;
                default:
                    break;
                }
            }
    else if((x==1||x==rowNum||y==1||y==colNum)&&outputOK)
    {
        qDebug()<<"rowNum = "<<rowNum;
        qDebug()<<"colNum = "<<colNum;
        emit outputFinishedSignal(x,y);
        ui->confirmButton_2->setEnabled(false);
        ui->outputCheckLabel->setEnabled(true);
        ui->outXSpinBox->setEnabled(false);
        ui->outYSpinBox->setEnabled(false);
    }


    else {
        int ret = QMessageBox::warning(this,"Error","Please make sure that output points are on the edge!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            ui->outXSpinBox->setValue(1);
            ui->outYSpinBox->setValue(1);
            break;
        default:
            break;
        }
    }
}

void SettingWidget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this,"question","Do you want to quit?",QMessageBox::Yes|QMessageBox::No);
    switch(ret)
    {
        case QMessageBox::Yes:
            break;
        case QMessageBox::No:
            event->ignore();
            break;
        default:
            break;
    }
}

