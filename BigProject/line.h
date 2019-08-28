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

};

#endif // LINE_H
