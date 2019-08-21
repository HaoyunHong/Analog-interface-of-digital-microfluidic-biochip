#include "mymainwindow.h"
#include "ui_mymainwindow.h"


myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);

    this->resize(1200,900);

    this->setWindowTitle("Main Window");





    inputPointsNum = 0;

    //菜单栏
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    //添加菜单
    QMenu *menu = mBar->addMenu("Option");



//    connect(settingWidget,&SettingWidget::backToMainWindow,
//            [=]()
//    {
//        this->show();
//    });

    QAction *actSet= menu->addAction("Setting");
    connect(actSet,&QAction::triggered,
            [=]()
        {
            //这里可以弹出一个子窗口
            settingWidget = new SettingWidget(this);
            connect(settingWidget,&SettingWidget::confirmSignal,this,&myMainWindow::setData);

//            connect(settingWidget,&SettingWidget::confirmSignal,
//                    [=]()
//            {
//                settingWidget->close();
//                this->show();

//            });
            connect(settingWidget,&SettingWidget::setInputPointsNumberSignal,
                    [=](int n)
            {
                inputPointsNum = n;
                qDebug()<<"inputPointsNum = "<<inputPointsNum;
            });
            connect(settingWidget,&SettingWidget::sendInputPoint,
                    [=](QPoint p)
            {
                unsigned int size = inputPoints.size();
                bool canStore = true;
                if(size !=0)
                {
                    for(unsigned int i=0;i<size-1;i++)
                    {
                        if(inputPoints[i].x() == p.x() && inputPoints[i].y() == p.y())
                        {
                            settingWidget->sendDuplicate(true);
                            canStore = false;
                            qDebug()<<"In Main Window Duplicate : p = "<<p;
                            break;
                        }
                    }
                }
                if(canStore)
                {
                    inputPoints.push_back(p);
                    qDebug()<<"In main window p = "<<p;
                }

            });
            settingWidget->exec();

            connect(settingWidget,&SettingWidget::setAgain,
                    [=]()
            {
                inputPoint.clear();
            });

        }
    );



    menu->addSeparator();//为了美观添加分割线
    //QAction *actFile = menu->addAction("File");



    //工具栏，菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");

    //工具栏添加快捷键
    toolBar->addAction(actSet);

}

void myMainWindow::closeEvent(QCloseEvent *event)
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

myMainWindow::~myMainWindow()
{
    delete ui;
}

void myMainWindow::setData(int r, int c)
{
    row = r;
    col = c;
    //data->setNumber(row, col);
    qDebug()<<"setData!"<<"row = "<<row<<" col = "<<col;
}

