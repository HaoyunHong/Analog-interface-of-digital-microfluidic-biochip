#ifndef SETINPUTDIALOG_H
#define SETINPUTDIALOG_H

#include <QDialog>
#include<QDebug>
#include<QMessageBox>

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

    void knowRowAndCol(int,int);

    void checkDuplicate(bool);

    void resetInputPoints();

private slots:
    void on_addButton_clicked();

private:
    Ui::SetInputDialog *ui;

    int inputNum;

    int count;

    bool ac;

    //行列数还都是要存的
    int row;
    int col;

    bool isDuplicate;

signals:
    void setInputPointSignal(QPoint);
    void InFinishedSignal();
};

#endif // SETINPUTDIALOG_H
