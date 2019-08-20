#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "settingwidget.h"
#include "data.h"
#include <QCloseEvent>

//Deal with pop dialogue
#include<QAction>
#include<QDialog>

//Deal with file
#include<QFile>
#include<QFileDialog>
#include<QDebug>
#include<QDateTime>

//Deal with MainWindow
#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
#include<QTextEdit>
#include<QDockWidget>



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

    SettingWidget settingWidget;

    Data *data;

    QFile *myFile;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MYMAINWINDOW_H
