#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "settingwidget.h"
#include <QCloseEvent>

//Deal with picture
#include<QPainter>
#include<QPaintEvent>

//Deal with pop dialogue
#include<QAction>
#include<QDialog>

//Deal with file
#include<QFile>
#include<QFileDialog>
#include<QDebug>

//Deal with MainWindow
#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
#include<QTextEdit>
#include<QDockWidget>

//Deal with input
#include<vector>
#include<QPoint>



namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = nullptr);
    ~myMainWindow();

    void setData(int,int);

private slots:

private:
    Ui::myMainWindow *ui;

    SettingWidget *settingWidget;

    int row;
    int col;

    std::vector<QPoint> inputPoints;
    QPoint outputPoint;

    bool canShowMatrix;


    QFile *myFile;

    int inputPointsNum;

    std::vector<QPoint> inputPoint;


protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);
};

#endif // MYMAINWINDOW_H
