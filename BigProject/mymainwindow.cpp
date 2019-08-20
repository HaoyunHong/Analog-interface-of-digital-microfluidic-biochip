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

    QAction *actSet= menu->addAction("Setting");
    connect(actSet,&QAction::triggered,
            [=]()
        {
            //这里可以弹出一个子窗口
            settingWidget.show();
            this->hide();
        }
    );

    menu->addSeparator();//为了美观添加分割线
    //QAction *actFile = menu->addAction("File");



}

myMainWindow::~myMainWindow()
{
    delete ui;
}

void myMainWindow::setData(int row, int col)
{
    data->setNumber(row, col);

}

