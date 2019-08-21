#include "setinputdialog.h"
#include "ui_setinputdialog.h"

SetInputDialog::SetInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInputDialog)
{
    ui->setupUi(this);

    ui->okButton->setEnabled(false);

    ui->xSpinBox->setMinimum(1);
    ui->ySpinBox->setMinimum(1);

    count = 0;
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

void SetInputDialog::resetInputPoints()
{
    ui->xSpinBox->setValue(1);
    ui->ySpinBox->setValue(1);
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
        if(point.x()==1 || point.x()==row || point.y()==1||point.y()==col )
        {
            if(isDuplicate)
            {
                int ret = QMessageBox::warning(this,"Error","Please enter a different position!",QMessageBox::Ok);
                switch(ret)
                {
                case QMessageBox::Ok:
                    this->resetInputPoints();
                    break;
                default:
                    break;
            }
            }
            else{
                 count++;
                }

        }
        else if(point.x()>row||point.y()>col)
        {
            int ret = QMessageBox::warning(this,"Error","The position of this input point out of range!",QMessageBox::Ok);
            switch(ret)
            {
            case QMessageBox::Ok:
                break;
            default:
                break;
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
            ui->addButton->setEnabled(false);
            ui->okButton->setEnabled(true);
            connect(ui->okButton,&QPushButton::clicked,
                    [=]()
            {
                this->close();
            });
            emit InFinishedSignal();//让SettingWidget知道自己ok了
        }
    }
    else {

    }
}




