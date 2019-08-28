#include "line.h"

Line::Line(QString line)
{
    wholeLine = line;
    qDebug()<<"wholeLine = "<<wholeLine;
    line = line.replace(" ", ",");
    line = line.replace(";", ",");
    QStringList parts = line.split(",");
    qDebug()<<parts;

    QString action = parts[0];
    qDebug()<<"action = "<<action;


    QPoint nowPoint;
    for(int i=2;i<parts.size()-1;i+=2)
    {
        if(parts[i].toInt()==0)
        {
            break;
        }
        else {
            nowPoint.setX(parts[i].toInt());
            nowPoint.setY(parts[i+1].toInt());
            path.push_back(nowPoint);
        }
    }

    beginTime = parts[1].toInt();
    int interval = 0;
    if(action == "Input")
    {
        kind = 1;
        beginTime = parts[1].toInt()-1;
        interval = 1;
    }
    if(action == "Move")
    {
        kind = 2;
        interval = 1;


    }
    if(action == "Split")
    {
        kind = 3;
        interval = 2;
    }
    if(action == "Merge")
    {
        kind = 4;
        interval = 2;
    }
    if(action == "Mix")
    {
        kind = 5;
        interval = path.size()-1;
    }
    if(action == "Output")
    {
        kind = 6;
        interval = 1;
    }

    endTime = beginTime+interval;

}
