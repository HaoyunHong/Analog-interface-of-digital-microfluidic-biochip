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


private slots:
    void on_confirmButton_clicked();

    void on_resetButton_clicked();

    void on_inOKButton_clicked();


private:
    Ui::SettingWidget *ui;

    SetInputDialog *dlg;

signals:
    void confirmSignal(int,int);
    void resetSignal();
    void setAgain();
    void backToMainWindow();
    void backToSettingWidget();

    void setInputPointsNumberSignal(int);

    void sendInputPoint(QPoint);
};

#endif // SETTINGWIDGET_H
