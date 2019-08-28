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

//Deal with input Points
#include<QVector>
#include<QPoint>

//Deal with operations
#include "operation.h"



namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = nullptr);
    ~myMainWindow();

    void setRC(int,int);

private slots:

    void on_lastButton_clicked();

    void on_nextButton_clicked();

    void on_limitedCheckBox_stateChanged(int state);

    void on_cleanCheckBox_stateChanged(int state);

private:
    Ui::myMainWindow *ui;

    SettingWidget *settingWidget;

    int row;
    int col;

    int inputPointsNum;
    QVector<QPoint> inputPoints;
    QPoint outputPoint;

    bool canShowMatrix;

    Operation *op;

    QFile *myFile;

    bool drawInput;
    bool drawNext;

    QPoint currentSquare;

    bool haveToClose;



protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);
};

#endif // MYMAINWINDOW_H
