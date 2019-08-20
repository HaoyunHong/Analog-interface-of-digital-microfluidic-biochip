#ifndef SETINPUTDIALOG_H
#define SETINPUTDIALOG_H

#include <QDialog>
#include<QDebug>

namespace Ui {
class SetInputDialog;
}

class SetInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetInputDialog(QWidget *parent = nullptr);
    ~SetInputDialog();

    void setInputNum(int);

private slots:
    void on_addButton_clicked();

private:
    Ui::SetInputDialog *ui;

    int inputNum;

    int count;

signals:
    void setInputPointSignal(QPoint);
};

#endif // SETINPUTDIALOG_H
