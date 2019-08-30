#ifndef LINE_H
#define LINE_H
#include<QString>
#include<QStringList>
#include<QVector>
#include<QPoint>
#include<QDebug>


class Line
{
public:
    Line(QString line);
    QString wholeLine;
    int beginTime;
    int kind;
    QVector<QPoint> path;
    int endTime;
    int curStep;

    QString action;

    //每个命令都截成每个时间单位时对某一个格子的操作
    QVector<QStringList> lineList;


};

#endif // LINE_H
