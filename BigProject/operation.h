#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>
#include "matrix.h"
#include<QFile>
#include<QDebug>
#include<vector>

#include "line.h"
#include "matrixcomb.h"
#include<algorithm>


class Operation : public QObject
{
    Q_OBJECT
public:
    explicit Operation(QObject *parent = nullptr);

    void setFile(QString path);
    void setEveryInput(QPoint pIn);
    void setTheOut(QPoint pOut);

    void parseFile();
    void parseLine(QString);

    bool isLimited;
    bool isClean;

    matrixComb* status;

    int wholeTime;


signals:
    void cannotShowCommand();

public slots:

private:
    QFile *myFile;
    std::vector<QPoint> inputPoints;
    QPoint outputPoint;

    int time;

    bool canShowCommand;



    int rowNum;
    int colNum;

    QVector<Line> commandLines;

    int colorSeed;
    QVector<QColor> dropKinds;

    void updateMatrixI(int);
    void updateMatrixMO(int);
    void updateMatrixS(int);
    void updateMatrixME(int);
    void updateMatrixMI(int);
    void updateMatrixO(int);
};

#endif // OPERATION_H
