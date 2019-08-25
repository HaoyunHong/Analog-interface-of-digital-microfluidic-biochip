#include "settingwidget.h"
#include "ui_settingwidget.h"


SettingWidget::SettingWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    //去窗口裱框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //窗口背景设置为透明、
    setAttribute(Qt::WA_TranslucentBackground);

    this->resize(1500,800);

    this->defaultAll();

    dlg = new SetInputDialog(this);

    connect(dlg,&SetInputDialog::InFinishedSignal,
            [=]()
    {
        inputOK = true;
        qDebug()<<"InFinishedSignal";

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

void SettingWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/image/image/dlg.png"));
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
        qDebug()<<"SetRC Again!";
        ui->rcCheckLabel->setEnabled(false);
        ui->confirmButton->setEnabled(true);
        emit setAgain();
        return;
    }
    else {
        emit sendRC(row,col);
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
        ui->outXSpinBox->setEnabled(true);
        ui->outYSpinBox->setEnabled(true);
        ui->confirmButton_2->setEnabled(true);

        ui->rowSpinBox->setEnabled(false);
        ui->colSpinBox->setEnabled(false);

    }
}


void SettingWidget::on_inOKButton_clicked()
{
    int n = ui->inpNumSpinBox->value();
    if(n>=2*(rowNum+colNum)-3)
    {
        int ret = QMessageBox::warning(this,"Error","Input points number out of range!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
        ui->inpNumSpinBox->setValue(1);
        return;
    }
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
        ui->saveButton->setEnabled(false);
        emit setAllDone();
        int ret = QMessageBox::information(this,"Tips","Setting is done and will be closed!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
        this->close();

    }
    else if(!rcOK)
    {
        int ret = QMessageBox::warning(this,"Undone","Row and column numbers setting undone!",QMessageBox::Ok);
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            break;
        }
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
    if(x > colNum || y > rowNum)
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
    else if((x==1||x==colNum||y==1||y==rowNum)&&outputOK)
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

void SettingWidget::defaultAll()
{
    ui->titleLabel->setStyleSheet("color: rgb(142,53,74)");
    ui->rowNum->setStyleSheet("color: rgb(142,53,74)");
    ui->colNum->setStyleSheet("color: rgb(142,53,74)");
    ui->label_2->setStyleSheet("color: rgb(142,53,74)");
    ui->label_3->setStyleSheet("color: rgb(142,53,74)");
    ui->label_4->setStyleSheet("color: rgb(142,53,74)");
    ui->label_5->setStyleSheet("color: rgb(142,53,74)");
    ui->rowSpinBox->setMinimum(1);
    ui->rowSpinBox->setMaximum(12);
    ui->rowSpinBox->setStyleSheet("background: rgb(254,223,225);color: rgb(142,53,74)");
    ui->colSpinBox->setMinimum(1);
    ui->colSpinBox->setMaximum(12);
    ui->colSpinBox->setStyleSheet("background: rgb(254,223,225);color: rgb(142,53,74)");
    ui->inpNumSpinBox->setMinimum(1);
    ui->inpNumSpinBox->setStyleSheet("background: rgb(238,169,169);color: rgb(142,53,74)");
    ui->outXSpinBox->setMinimum(1);
    ui->outXSpinBox->setStyleSheet("background: rgb(254,223,225);color: rgb(142,53,74)");
    ui->outYSpinBox->setMinimum(1);
    ui->outYSpinBox->setStyleSheet("background: rgb(254,223,225);color: rgb(142,53,74)");

    ui->confirmButton->setStyleSheet("background: rgb(245,150,170);color: rgb(142,53,74)");
    ui->confirmButton_2->setStyleSheet("background: rgb(245,150,170);color: rgb(142,53,74)");
    ui->inOKButton->setStyleSheet("background: rgb(232,122,144);color: rgb(142,53,74)");
    ui->saveButton->setStyleSheet("background: rgb(254,223,225);color: rgb(142,53,74)");

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
    outputOK = false;

    rowNum = 0;
    colNum = 0;
}
