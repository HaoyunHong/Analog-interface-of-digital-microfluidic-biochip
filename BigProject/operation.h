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

#include<QMediaPlayer>

struct Polluted
{
    int iniPol;
    int time;
    QPoint p;
    int cleanTime;
};

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

    int rowNum;
    int colNum;

    bool isLimited;
    bool isClean;

    matrixComb* status;

    int wholeTime;

    QList<QStringList>* lineTimeList;

    int judge();

    int stopTime;


    int cannotClean();

    QVector<matrixComb> cleanStatus;

    int startClean();

    void changeIsSafe();

    //然后它在mainwindow的画布里会有自己的ints计时器
    int startCleanTime(int index);

    QVector<Polluted> pollutedInfo;

    void cleanMode();

signals:
    void cannotShowCommand();
    void neednotClean();

public slots:

private:
    QFile *myFile;
    std::vector<QPoint> inputPoints;
    QPoint outputPoint;

    int time;

    bool canShowCommand;

    int cannotCleanTime;







    QVector<Line> commandLines;

    int colorSeed;
    QVector<QColor> dropKinds;

//    void updateMatrixI(int);
//    void updateMatrixMO(int);
//    void updateMatrixS(int);
//    void updateMatrixME(int);
//    void updateMatrixMI(int);
//    void updateMatrixO(int);

    //void fillBlank(int);

};

#endif // OPERATION_H
