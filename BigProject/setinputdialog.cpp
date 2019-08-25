#include "setinputdialog.h"
#include "ui_setinputdialog.h"

SetInputDialog::SetInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInputDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Input Points Setting");

    ui->okButton->setEnabled(false);

    ui->xSpinBox->setMinimum(1);
    ui->ySpinBox->setMinimum(1);
    ui->progressBar->setValue(0);

    count = 0;

    isDuplicate = false;
}

void SetInputDialog::knowRowAndCol(int r,int c)
{
    row = r;
    col = c;

}

void SetInputDialog::checkDuplicate(bool flag)
{
    isDuplicate = flag;
    qDebug()<<"isDuplicate = "<<isDuplicate;
}

void SetInputDialog::setInputNum(int n)
{
    inputNum = n;
}


SetInputDialog::~SetInputDialog()
{
    delete ui;
}

void SetInputDialog::on_addButton_clicked()
{
    qDebug()<<"inputNum = "<<inputNum;
    if(count < inputNum)
    {
        qDebug()<<"count = "<<count;
        QPoint point;
        point.setX(ui->xSpinBox->value());
        point.setY(ui->ySpinBox->value());
        qDebug()<<"In Setting point = "<<point;
        emit setInputPointSignal(point);

        if(point.x()>col || point.y()>row)
        {
            int ret = QMessageBox::warning(this,"Error","The position of this input point out of range!",QMessageBox::Ok);
            switch(ret)
            {
            case QMessageBox::Ok:
                ui->xSpinBox->setValue(1);
                ui->ySpinBox->setValue(1);
                break;
            default:
                break;
            }
        }
        else if(point.x()==1 || point.x()==col || point.y()==1||point.y()==row )
        {
            if(isDuplicate)
            {
                int ret = QMessageBox::warning(this,"Error","Please enter a different position!",QMessageBox::Ok);
                switch(ret)
                {
                case QMessageBox::Ok:
                    ui->xSpinBox->setValue(1);
                    ui->ySpinBox->setValue(1);
                    break;
                default:
                    break;
                }
            }
            else{

                qDebug()<<"Point is OK: point = "<<point;
                 count++;
                 ui->progressBar->setMaximum(inputNum);
                 ui->progressBar->setValue(count);
                }

        }
        else {
            int ret = QMessageBox::warning(this,"Error","Please make sure that input points are on the edge!",QMessageBox::Ok);
            switch(ret)
            {
            case QMessageBox::Ok:
                break;
            default:
                break;
            }
        }

        if(count == inputNum)
        {
            qDebug()<<"OK";
            ui->addButton->setEnabled(false);
            ui->okButton->setEnabled(true);
            ui->xSpinBox->setEnabled(false);
            ui->ySpinBox->setEnabled(false);
        }
    }
    else {

    }
}

void SetInputDialog::resetThisInputPoint()
{
    ui->xSpinBox->setValue(1);
    ui->ySpinBox->setValue(1);
    ui->progressBar->setValue(0);
}


void SetInputDialog::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::warning(this,"Warning","Please finish editing!",QMessageBox::Ok);
    switch(ret)
    {
        case QMessageBox::Ok:
            event->ignore();
            break;
        default:
            break;
    }
}


void SetInputDialog::on_okButton_clicked()
{
    this->hide();
    emit InFinishedSignal();
    qDebug()<<"lll";
}
