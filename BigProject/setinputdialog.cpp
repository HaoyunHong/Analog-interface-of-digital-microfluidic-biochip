#include "setinputdialog.h"
#include "ui_setinputdialog.h"

SetInputDialog::SetInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInputDialog)
{
    ui->setupUi(this);

    ui->okButton->setEnabled(false);

    count = 0;
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
        count++;
        if(count == inputNum)
        {
            ui->addButton->setEnabled(false);
            ui->okButton->setEnabled(true);
            connect(ui->okButton,&QPushButton::clicked,
                    [=]()
            {
                this->close();
            });
        }
    }
    else {

    }




}

void SetInputDialog::setInputNum(int n)
{
    inputNum = n;
}
