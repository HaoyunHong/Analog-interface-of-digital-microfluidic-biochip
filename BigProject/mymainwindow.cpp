#include "mymainwindow.h"
#include "ui_mymainwindow.h"


myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);

    this->resize(1200,900);

    this->setWindowTitle("Main Window");

    this->show();

    //菜单栏
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    //添加菜单
    QMenu *menu = mBar->addMenu("Option");


    connect(&settingWidget,&SettingWidget::confirmSignal,this,&myMainWindow::setData);

    connect(&settingWidget,&SettingWidget::confirmSignal,
            [=]()
    {
        settingWidget.close();
        this->show();

    });

    connect(&settingWidget,&SettingWidget::backToMainWindow,
            [=]()
    {
        this->show();
    });

    QAction *actSet= menu->addAction("Setting");
    connect(actSet,&QAction::triggered,
            [=]()
        {
            //这里可以弹出一个子窗口
            settingWidget.exec();

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

void myMainWindow::setData(int row, int col)
{
    data->setNumber(row, col);

}

