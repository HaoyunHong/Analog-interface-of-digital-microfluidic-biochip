#include "mymainwindow.h"
#include "ui_mymainwindow.h"


myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1200,900);

    this->setWindowTitle("Main Window");

    QIcon mainIcon(":/image/image/rabbit.png");
    this->setWindowIcon(mainIcon);

    this->setStyleSheet("color: rgba(142,53,74,200);font-weight:bold;");

//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/image/pinback.jpg")));
//    this->setPalette(palette);
//    setAcceptDrops(true);
    drawLast = false;
    drawNext = false;

    now = 0;

    inputPointsNum = 0;

    row = 0;
    col = 0;

    outputPoint.setX(0);
    outputPoint.setY(0);

    haveToClose = false;

    op = new Operation(this);

    //菜单栏
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    mBar->setStyleSheet("background-image:url(:/image/image/back.jpg)");
    //添加菜单
    QMenu *menu = mBar->addMenu("Option");
    menu->setStyleSheet("background-image:url(:/image/image/back.jpg)");

    QAction *actSet= menu->addAction("Setting");

    //工具栏，菜单项的快捷方式
    QToolBar *toolBar = new QToolBar("toolBar",this);
    addToolBar(Qt::RightToolBarArea,toolBar);
    toolBar->setStyleSheet("background-image:url(:/image/image/back.jpg)");

    menu->addSeparator();//为了美观添加分割线
    QAction *actCommand = menu->addAction("Command");
    //工具栏添加快捷键
    toolBar->addAction(actSet);
    toolBar->addAction(actCommand);

    QIcon settingIcon(":/image/image/settingIcon.png");
    actSet->setIcon(settingIcon);
    QIcon commandIcon(":/image/image/commandIcon.png");
    actCommand->setIcon(commandIcon);

    actCommand->setEnabled(false);
    ui->commandTextEdit->hide();
    QString chooseSetting = "Please Click Setting Option! ";
    //状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText(chooseSetting);
    label->setStyleSheet("font-size:40px;font-weight:bold;font-family:Calibri;background-color:rgba(255,255,255,200)");
    sBar->addWidget(label);

    ui->commandViewerlabel->hide();
    ui->commandViewerlabel->setStyleSheet("color: rgba(142,53,74,200);font-weight:bold;");
    ui->commandTextEdit->setStyleSheet("border-image:url(:/image/image/back.jpg);border-width:1;border-style:outset;");

    ui->lcdNumber->setStyleSheet("background-color: rgba(208,16,76,200);border-width:2;border-style:outset;border-color:rgb(208,16,76);font-weight:bold;");
    ui->lcdNumber->hide();
    ui->lastButton->setStyleSheet("border-width:3;border-style:outset;border-color:rgb(220,159,180);");
    ui->lastButton->hide();
    ui->nextButton->setStyleSheet("border-width:3;border-style:outset;border-color:rgb(220,159,180);");
    ui->nextButton->hide();
    //ui->cleanButton->setStyleSheet("border-width:3;border-style:outset;border-color:rgb(220,159,180);");
    //ui->cleanButton->hide();ui->limitedCheckBox->setStyleSheet("border-width:3;border-color:rgb(220,159,180);");
    ui->cleanCheckBox->setStyleSheet("border-width:3;border-color:rgb(220,159,180);");
    ui->cleanCheckBox->hide();
    ui->limitedCheckBox->setStyleSheet("border-width:3;border-color:rgb(220,159,180);");
    ui->limitedCheckBox->hide();
    ui->playButton->setStyleSheet("border-width:3;border-style:outset;border-color:rgb(220,159,180);");
    ui->playButton->hide();
    ui->resetButton->setStyleSheet("border-width:3;border-style:outset;border-color:rgb(220,159,180);");
    ui->resetButton->hide();

    ui->lastButton->setEnabled(false);
    ui->nextButton->setEnabled(false);
    ui->cleanCheckBox->setEnabled(false);
    ui->limitedCheckBox->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    settingWidget = new SettingWidget(this);

    connect(actCommand,&QAction::triggered,
            [=]()
    {
        QString chooseCommand = "Light pink represents input points, dark pink represents the output point.";
        label->setText(chooseCommand);
        label->setStyleSheet("font-size:30px;font-weight:bold;font-family:Calibri;background-color:rgba(255,255,255,200)");
        QString path = QFileDialog::getOpenFileName(this,
                                        "open","../","TXT(*.txt)");
            //只有当文件不为空时才进行操作
            if(path.isEmpty()== false)
            {
                //文件操作
                QFile file(path);
                myFile = new QFile(path);
                //打开文件，只读方式
                bool isOK = file.open(QIODevice::ReadOnly);
                if(isOK == true)
                {
                    op->setFile(path);
                    QByteArray array;
                    while(file.atEnd() == false)
                    {
                        //每次读一行
                        array += file.readLine();
                    }
                    ui->commandTextEdit->setText(array);
                }
                else if(isOK == false){
                    int ret = QMessageBox::warning(this,"Error","Please choose another readable file as the command file!",QMessageBox::Ok);
                    switch(ret)
                    {
                        case QMessageBox::Ok:
                            break;
                        default:
                            break;
                    }
                }
                //关闭文件
                file.close();
             }

            ui->lastButton->setEnabled(true);
            ui->nextButton->setEnabled(true);
            //ui->cleanButton->setEnabled(true);
            ui->cleanCheckBox->setEnabled(true);

            ui->playButton->setEnabled(true);
            ui->resetButton->setEnabled(true);

            ui->lcdNumber->display("0");
            ui->lcdNumber->show();
    });
    connect(actSet,&QAction::triggered,
            [=]()
        {
        QString chooseCommand = "Setting now~";
        label->setText(chooseCommand);
        label->setStyleSheet("font-size:40px;font-weight:bold;font-family:Calibri;background-color:rgba(255,255,255,200)");
            //这里弹出一个子窗口
            //connect(settingWidget,&SettingWidget::confirmSignal,this,&myMainWindow::setRC);

            connect(settingWidget,&SettingWidget::sendRC,this,&myMainWindow::setRC);
            connect(settingWidget,&SettingWidget::setInputPointsNumberSignal,
                    [=](int n)
            {
                inputPointsNum = n;
                qDebug()<<"inputPointsNum = "<<inputPointsNum;
            });

            connect(settingWidget,&SettingWidget::sendInputPoint,
                    [=](QPoint p)
            {
                int size = inputPoints.size();
                qDebug()<<"size = "<<size;
                    bool canStore = true;
                    for(int i=0;i<size;i++)
                    {
                        if(inputPoints[i]==p || p == outputPoint)
                        {
                            qDebug()<<i<<" : inputPoints["<<i<<"] = "<<inputPoints[i];
                            qDebug()<<"p = "<<p;
                            settingWidget->sendDuplicate(true);
                            canStore = false;
                            qDebug()<<"In Main Window Duplicate : p = "<<p;
                            break;
                        }
                    }
                    if(canStore)
                    {
                        settingWidget->sendDuplicate(false);
                        inputPoints.push_back(p);
                        qDebug()<<"In main window p = "<<p;
                    }
            });
            settingWidget->exec();

            connect(settingWidget,&SettingWidget::setAgain,
                    [=]()
            {
                inputPoints.clear();
                qDebug()<<"Clear input points!";
            });

        }
    );

    connect(settingWidget,&SettingWidget::outputCheckSignal,
            [=](int x, int y)
    {
       int size = inputPoints.size();
        qDebug()<<"size = "<<size;
//        for(unsigned int i=0;i<size;i++)
//        {
//            qDebug()<<inputPoints[i];
//        }
        if(size == 0)
        {
            settingWidget->outIsOK(true);
            qDebug()<<"Input points haven't entered, so it's OK.";
        }
        else
        {
            bool flag = true;
            for(int i=0;i<size;i++)
            {
                qDebug()<<"x = "<<x<<"y = "<<y;
                qDebug()<<"inputPoints["<<i<<"]"<<inputPoints[i];


                if(inputPoints[i].x() == x && inputPoints[i].y() == y)
                {
                    flag = false;
                    qDebug()<<"Output overlap with input!";
                    break;
                }
            }
            settingWidget->outIsOK(flag);

        }
    }
        );


    connect(settingWidget,&SettingWidget::outputFinishedSignal,
            [=](int x, int y)
    {
        outputPoint.setX(x);
        outputPoint.setY(y);
        qDebug()<<"outputPoint = "<<outputPoint;
    });

    canShowMatrix = false;

    connect(settingWidget,&SettingWidget::setAllDone,
            [=]()
    {
        canShowMatrix = true;
        qDebug()<<"Set all done Updating!";
        update();
        actCommand->setEnabled(true);
        ui->commandTextEdit->show();
        ui->commandViewerlabel->setStyleSheet("color: rgba(142,53,74,200);font-weight:bold;");
        ui->commandViewerlabel->show();
        ui->lastButton->show();
        ui->nextButton->show();
        ui->cleanCheckBox->show();
        ui->limitedCheckBox->show();
        ui->playButton->show();
        ui->resetButton->show();

        //sBar->show();
        QString chooseCommand = "Light pink represents input points, dark pink represents the output point. Please Click Command Option!";
        //label->show();
        label->setText(chooseCommand);
        label->setStyleSheet("font-size:30px;font-weight:bold;font-family:Calibri;background-color:rgba(255,255,255,200)");
        //sBar->addWidget(label);

        for(int i = 0;i< inputPoints.size();i++)
        {
            op->setEveryInput(inputPoints[i]);
            qDebug()<<"In Main Window send av inputPoint to Operation!";
            qDebug()<<"inputPoints["<<i<<"] = "<<inputPoints[i];
        }
        op->setTheOut(outputPoint);
        qDebug()<<"In Main Window send the outputPoint to Operation!";
        qDebug()<<"outputPoint = "<<outputPoint;
    });


    connect(op,&Operation::cannotShowCommand,
            [=]()
    {
        ui->commandTextEdit->clear();
        ui->commandTextEdit->setText("Please choose a valid Command File!");
        int ret = QMessageBox::warning(this,"Error","[Invalid Command File] Please choose a valid Command File next time and restart the application! It will close soon!",QMessageBox::Ok);
        switch(ret)
        {
            case QMessageBox::Ok:
                haveToClose = true;
                this->close();
                break;
            default:
                break;
        }
    });

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,
            [=]()
    {
        now++;
        if(now<0 || now>op->wholeTime)
        {
            drawNext = false;
            now--;
        }
        else {
            drawNext = true;
            qDebug()<<"Next updating!";
            update();
            qDebug()<<"now: "<<now;
        }
        if(now >= op->wholeTime)
        {
            timer->stop();
            ui->nextButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
            ui->resetButton->setEnabled(true);
        }
        ui->lcdNumber->display(now);
    });

}

void myMainWindow::paintEvent(QPaintEvent *)
{
    QPainter p;//创建画家对象
    p.begin(this);//指定当前窗口为绘图设备

    qDebug()<<"Begin painting!";
    //反锯齿
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/image/image/pinback.jpg"));
    //设置屏幕透明度
    setWindowOpacity(0.96);

    QPoint center(width()/2,height()/2);

    if(canShowMatrix)
    {
        //定义画笔
        QPen pen;
        pen.setWidth(2);//设置线宽
        pen.setColor(QColor(220,159,180));
        pen.setStyle(Qt::DashDotDotLine);

        //把画笔交给画家
        p.setPen(pen);

        //创建画刷对象
        QBrush brush;
        brush.setColor(QColor(255,255,255,98));//设置颜色
        brush.setStyle(Qt::SolidPattern);//设置样式
        //把画刷交给画家
        p.setBrush(brush);
        int x = width()-40;
        int y = height()-70;
        int x2 = 3*width()/5;
        int y2 = y-60;

        //画背景矩形
        p.drawRect(20,50,x,y);

        //画矩阵框
        pen.setWidth(5);//设置线宽
        pen.setColor(QColor(220,159,180));
        pen.setStyle(Qt::SolidLine);
        p.setPen(pen);
        brush.setColor(QColor(255,255,255));//设置颜色
        brush.setStyle(Qt::SolidPattern);//设置样式
        p.setBrush(brush);

        //对坐标做平移变换
        QPoint origin(50,80);
        p.translate(origin.x(),origin.y());
        p.drawRect(0,0,x2,y2);

        center.setX(x2/2);
        center.setY(y2/2);
        //qDebug()<<"center = "<<center;

        //qDebug()<<"row = "<<row;
        //qDebug()<<"col = "<<col;
        int unit = 50;
        int mwidth = col*unit;
        //qDebug()<<"mwidth = "<<mwidth;
        int mheight = row*unit;
        //qDebug()<<"mheight = "<<mheight;
        pen.setWidth(3);//设置线宽
        pen.setColor(QColor(245,150,170));
        pen.setStyle(Qt::SolidLine);
        p.setPen(pen);
        //一定要是center,把坐标画对
        p.drawPoint(center);
        p.drawRect(center.x()-mwidth/2,center.y()-mheight/2,mwidth,mheight);
        for(int i=1;i<col;i++)
        {
            //qDebug()<<"center.x()-mwidth/2+i*unit = "<<center.x()-mwidth/2+i*unit;
            p.drawLine(center.x()-mwidth/2+i*unit,center.y()-mheight/2,center.x()-mwidth/2+i*unit,center.y()+mheight/2);
        }
        for(int i=1;i<row;i++)
        {
            p.drawLine(center.x()-mwidth/2,center.y()-mheight/2+i*unit,center.x()+mwidth/2,center.y()-mheight/2+i*unit);
        }

        //然后以左下角为原点
        p.translate(center.x()-mwidth/2,center.y()+mheight/2);

        //开始画输出口
        pen.setWidth(3);//设置线宽
        pen.setColor(QColor(245,150,170));
        pen.setStyle(Qt::DashLine);
        brush.setColor(QColor(219,77,109));//设置颜色
        brush.setStyle(Qt::SolidPattern);//设置样式

        p.setPen(pen);
        p.setBrush(brush);
        if(outputPoint.y()==1 && outputPoint.x() < col)
        {
            p.drawRect((outputPoint.x()-1)*unit,0-(outputPoint.y()-2)*unit+unit/8,unit,-9*unit/8);
        }
        else if(outputPoint.y()==row && outputPoint.x() <= col)
        {
            p.drawRect((outputPoint.x()-1)*unit,0-(outputPoint.y())*unit,unit,-9*unit/8);
        }
        else if(outputPoint.x()==1 && outputPoint.y() < row)
        {
            p.drawRect((outputPoint.x()-2)*unit-unit/8,0-(outputPoint.y()-1)*unit,9*unit/8,-unit);
        }
        else if(outputPoint.x()==col && outputPoint.y() < row)
        {
            p.drawRect((outputPoint.x())*unit,0-(outputPoint.y()-1)*unit,9*unit/8,-unit);
        }

        //画输入端口
        pen.setWidth(3);//设置线宽
        pen.setColor(QColor(245,150,170));
        pen.setStyle(Qt::DashLine);
        brush.setColor(QColor(254,223,225));//设置颜色
        brush.setStyle(Qt::SolidPattern);//设置样式
        p.setPen(pen);
        p.setBrush(brush);
        for(int i=0;i<inputPoints.size();i++)
        {
            if(inputPoints[i].y()==1 && inputPoints[i].x() < col)
            {
                p.drawRect((inputPoints[i].x()-1)*unit,0-(inputPoints[i].y()-2)*unit+unit/8,unit,-9*unit/8);
            }
            else if(inputPoints[i].y()==row && inputPoints[i].x() <= col)
            {
                p.drawRect((inputPoints[i].x()-1)*unit,0-(inputPoints[i].y())*unit,unit,-9*unit/8);
            }
            else if(inputPoints[i].x()==1 && inputPoints[i].y() < row)
            {
                p.drawRect((inputPoints[i].x()-2)*unit-unit/8,0-(inputPoints[i].y()-1)*unit,9*unit/8,-unit);
            }
            else if(inputPoints[i].x()==col && inputPoints[i].y() < row)
            {
                p.drawRect((inputPoints[i].x())*unit,0-(inputPoints[i].y()-1)*unit,9*unit/8,-unit);
            }
        }

        //三种不同型号的小圆直径
        int sD = 20;
        int mD = 30;
        int lD = 40;
        //椭圆形的参数
        int longD = 120;
        int shortD = 30;

        if(drawNext || drawLast)
        {
            brush.setStyle(Qt::SolidPattern);//设置样式
            for(int i=1;i<=col;i++)
             {
                  for(int j=1;j<=row;j++)
                  {
                       if(!op->status[now].comb[i][j].isEmpty)
                       {
                           brush.setColor(op->status[now].comb[i][j].dropColor);//设置颜色
                           p.setBrush(brush);
                           p.setPen(Qt::NoPen);
                           if(op->status[now].comb[i][j].isLongDrop)
                           {
                               qDebug()<<"IsLong!";
                               if(op->status[now].comb[i][j].isFat)
                               {
                                    qDebug()<<"IsFat!";
                                    p.drawEllipse((i-1)*unit+unit/2-longD/2,0-(j-1)*unit-unit/2+shortD/2,longD,-shortD);
                               }
                               else {
                                   qDebug()<<"IsThin!";
                                    p.drawEllipse((i-1)*unit+unit/2-shortD/2,0-(j-1)*unit-unit/2+longD/2,shortD,-longD);
                               }

                           }
                           else if(op->status[now].comb[i][j].isBigger)
                           {
                               qDebug()<<"in Main draw Bigger!";
                               p.drawEllipse((i-1)*unit+unit/2-lD/2,0-(j-1)*unit-unit/2+lD/2,lD,-lD);
                           }
                           else if(op->status[now].comb[i][j].isSmaller)
                           {
                               p.drawEllipse((i-1)*unit+unit/2-sD/2,0-(j-1)*unit-unit/2+sD/2,sD,-sD);
                           }
                           else {
                               p.drawEllipse((i-1)*unit+unit/2-mD/2,0-(j-1)*unit-unit/2+mD/2,mD,-mD);
                           }

                       }
                  }
             }
        }
    }
    p.end();

}

void myMainWindow::closeEvent(QCloseEvent *event)
{
    if(haveToClose) return;
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

myMainWindow::~myMainWindow()
{
    delete ui;
}

void myMainWindow::setRC(int r, int c)
{
    row = r;
    col = c;
    //op->setRC(row,col);
    qDebug()<<"setRC!"<<"row = "<<row<<" col = "<<col;
}

void myMainWindow::on_lastButton_clicked()
{
    now--;
    if(now<0 || now>op->wholeTime)
    {
        drawLast = false;
        now++;
    }
    else {
        drawLast = true;
        qDebug()<<"Last updating!";
        update();
        qDebug()<<"now: "<<now;
    }
    ui->lcdNumber->display(now);
}

void myMainWindow::on_nextButton_clicked()
{
    now++;
    if(now<0 || now>op->wholeTime)
    {
        drawNext = false;
        now--;
    }
    else {
        drawNext = true;
        qDebug()<<"Next updating!";
        update();
        qDebug()<<"now: "<<now;
    }
    ui->lcdNumber->display(now);
}

void myMainWindow::on_limitedCheckBox_stateChanged(int state)
{
    if(state == Qt::Checked)
    {
        op->isLimited = true;
    }
    else if(state == Qt::Unchecked)
    {
        op->isLimited = false;
    }
}

void myMainWindow::on_cleanCheckBox_stateChanged(int state)
{
    if(state == Qt::Checked)
    {
        ui->limitedCheckBox->setEnabled(true);
        op->isClean = true;
    }
    else if(state == Qt::Unchecked)
    {
        op->isClean = false;
    }
}

void myMainWindow::on_resetButton_clicked()
{
    now = 0;
    ui->lcdNumber->display(now);
    drawLast = false;
    drawNext = false;
    update();
}

void myMainWindow::on_playButton_clicked()
{

    timer->start(1000);

    qDebug()<<"now = "<<now;
    ui->nextButton->setEnabled(false);
    ui->lastButton->setEnabled(false);
    ui->resetButton->setEnabled(false);


}
