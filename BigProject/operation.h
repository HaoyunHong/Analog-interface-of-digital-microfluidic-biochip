#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>
#include "matrix.h"
#include<QFile>
#include<QDebug>
#include<vector>
#include<map>

class Operation : public QObject
{
    Q_OBJECT
public:
    explicit Operation(QObject *parent = nullptr);

    void setRC(int row, int col);
    void setFile(QString path);
    void setEveryInput(QPoint pIn);
    void setTheOut(QPoint pOut);

    void parseFile();
    void parseLine(QString);


signals:
    void cannotShowCommand();
    void drawInput(int,int);

public slots:

private:
    Matrix ** matrix;
    QFile *myFile;
    std::vector<QPoint> inputPoints;
    QPoint outputPoint;

    int time;

    bool canShowCommand;

    int countKind;

    std::vector<int> timer;
    std::vector<Matrix**> status;

};

#endif // OPERATION_H
