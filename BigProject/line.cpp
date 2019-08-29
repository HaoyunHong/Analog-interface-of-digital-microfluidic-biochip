#include "line.h"

Line::Line(QString line)
{
    curStep = 0;
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
        beginTime = parts[1].toInt();
        interval = 1;

        QStringList list2;
        list2<< "drawI"<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list2);
        qDebug()<<list2;
    }
    if(action == "Move")
    {
        kind = 2;
        interval = 1;
        QStringList list1;
        list1<< "clear"<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list1);
        qDebug()<<list1;
        QStringList list2;
        list2<< "move"<<QString::number(beginTime+1)<<parts[2]<<parts[3]<<parts[4]<<parts[5];
        lineList.push_back(list2);
        qDebug()<<list2;
    }

    if(action == "Split")
    {
        kind = 3;
        interval = 2;
        QStringList list1;
        list1<< "clear"<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list1);
        qDebug()<<list1;
        QStringList list2;
        if(path[2].y()==path[1].y())
        {
            list2<< "drawLFS";
        }
        else {
            list2<<"drawLS";
        }
        list2<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list2);
        qDebug()<<list2;
        QStringList list3;
        list3<< "clear"<<QString::number(beginTime+2)<<parts[2]<<parts[3];
        lineList.push_back(list3);
        qDebug()<<list3;
        QStringList list4;
        list4<< "drawS"<<QString::number(beginTime+2)<<parts[4]<<parts[5]<<parts[6]<<parts[7];
        lineList.push_back(list4);
        qDebug()<<list4;
    }
    if(action == "Merge")
    {
        kind = 4;
        interval = 2;
        QStringList list1;
        list1<< "clear"<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list1);
        qDebug()<<list1;
        QStringList list2;
        list2<< "clear"<<QString::number(beginTime+1)<<parts[4]<<parts[5];
        lineList.push_back(list2);
        qDebug()<<list2;
        QStringList list3;
        QPoint middle = (path[0]+path[1])/2;
        if(path[0].y()==path[1].y())
        {
            list3<< "drawLFM";
        }
        else {
            list3<<"drawLM";
        }
        list3<<QString::number(beginTime+1)<<QString::number(middle.x())<<QString::number(middle.y());
        lineList.push_back(list3);
        qDebug()<<list3;
        QStringList list4;
        list4<< "clear"<<QString::number(beginTime+2)<<QString::number(middle.x())<<QString::number(middle.y());
        lineList.push_back(list4);
        qDebug()<<list4;
        QStringList list5;
        list5<< "drawB"<<QString::number(beginTime+2)<<QString::number(middle.x())<<QString::number(middle.y());
        lineList.push_back(list5);
        qDebug()<<list5;



    }
    if(action == "Mix")
    {
        kind = 5;
        interval = path.size()-1;
        qDebug()<<"path.size() = "<<path.size();
        int cnt = 2;
        int t = 1;
        while(t<path.size())
        {
            //这里小心别越界了
            qDebug()<<"cnt = "<<cnt;
            if(cnt>=2*path.size()) break;
            QStringList list1;
            list1<< "clear"<<QString::number(beginTime+t)<<parts[cnt]<<parts[cnt+1];
            lineList.push_back(list1);
            qDebug()<<list1;
            QStringList list2;
            list2<< "move"<<QString::number(beginTime+t)<<parts[cnt]<<parts[cnt+1]<<parts[cnt+2]<<parts[cnt+3];
            lineList.push_back(list2);
            qDebug()<<list2;
            cnt+=2;
            t++;
        }
    }
    if(action == "Output")
    {
        kind = 6;
        interval = 1;
        QStringList list2;
        list2<< "clear"<<QString::number(beginTime+1)<<parts[2]<<parts[3];
        lineList.push_back(list2);
        qDebug()<<list2;
    }

    endTime = beginTime+interval;

}
