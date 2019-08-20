#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include<QMessageBox>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    static int row;
    static int col;

private slots:
    void on_confirmButton_clicked();

    void on_resetButton_clicked();

    void on_rowSpinBox_valueChanged(const QString &arg1);

    void on_colSpinBox_valueChanged(const QString &arg1);

private:
    Ui::SettingWidget *ui;



signals:
    void confirmSignal(int,int);
    void resetSignal();
    void setAgain();
    //void backToMainWindow();
};

#endif // SETTINGWIDGET_H
