#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include<QMessageBox>
#include <QCloseEvent>

#include"setinputdialog.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    void sendDuplicate(bool flag = false);

    void outIsOK(bool);


private slots:
    void on_confirmButton_clicked();

    void on_resetButton_clicked();

    void on_inOKButton_clicked();


    void on_saveButton_clicked();

    void on_confirmButton_2_clicked();



private:
    Ui::SettingWidget *ui;

    SetInputDialog *dlg;

    bool rcOK;
    bool inputOK;
    bool outputOK;

    int rowNum;
    int colNum;

signals:
    void confirmSignal(int,int);
    void resetSignal();
    void setAgain();
    void backToMainWindow();
    void backToSettingWidget();

    void setInputPointsNumberSignal(int);

    void sendInputPoint(QPoint);

    void outputFinishedSignal(int,int);

    void outputCheckSignal(int,int);

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // SETTINGWIDGET_H
