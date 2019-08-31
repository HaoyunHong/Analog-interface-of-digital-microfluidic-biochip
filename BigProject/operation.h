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

#include "node.h"

#define MAXNUM 100000

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
    int wholeCleanTime;
    int cleanLength;

    QList<QStringList>* lineTimeList;

    int judge();

    int stopTime;


    int cannotClean();

    QVector<matrixComb> cleanStatus;

    matrixComb* BlockStatus;

    int startClean( );

    void changeIsSafe();

    //然后它在mainwindow的画布里会有自己的ints计时器
    int startCleanTime(Polluted &pol);

    QVector<Polluted> pollutedInfo;

    void changeCleanSafe(int now);




signals:
    void cannotShowCommand();
    void sendWholeCleanTimeSignal(int);
    void cannotCleaninCleanMode(int);
    void cannotCleanHere();

public slots:

private:
    QFile *myFile;
    std::vector<QPoint> inputPoints;
    QPoint outputPoint;

    int time;

    bool canShowCommand;

    int cannotCleanTime;

    void out(int i,int j);

    int **path;

    QVector<QPoint> points;

    QVector<int> road;//暂存路径的点下标
    QVector<QPoint> wholeRoad;//存储头到中间再到尾的最短路径

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

    QVector<int> cleanTimes;

};

#endif // OPERATION_H
