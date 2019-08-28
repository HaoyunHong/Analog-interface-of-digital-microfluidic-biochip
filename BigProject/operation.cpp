#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
      time = 0;

      canShowCommand = true;

      isLimited = false;
      isClean = false;

      colorSeed = 1;
}

void Operation::setFile(QString path)
{
    qDebug()<<"In setFile path = "<<path;
    myFile = new QFile(path);
    this->parseFile();
    qDebug()<<"File parsing!";
}

void Operation::setEveryInput(QPoint pIn)
{
    inputPoints.push_back(pIn);
    qDebug()<<"In operation inputPoints.size() = "<<inputPoints.size();
    qDebug()<<"In operation current inputPoint = "<<pIn;
}

void Operation::setTheOut(QPoint pOut)
{
    outputPoint = pOut;
    qDebug()<<"In operation outputPoint = "<<outputPoint;
}

void Operation::parseFile()
{
    QByteArray array;
    myFile->open(QIODevice::ReadOnly);
    while(myFile->atEnd() == false)
    {
        //每次读一行
        array = myFile->readLine();

        Line L(array);
        commandLines.push_back(L);

    }

    for(int i=0;i<commandLines.size();i++)
    {

        if(commandLines[i].kind == 1)
        {
            int cntDiff = 0;
            for(int j=0;j < inputPoints.size();j++)
            {
                if(commandLines[i].path[0]==inputPoints[j])
                {
                    break;
                }
                else {
                    cntDiff++;
                }
            }
            if(cntDiff == inputPoints.size())
            {
                canShowCommand = false;
            }
        }


        if(commandLines[i].kind == 6)
        {
            if(commandLines[i].path[0]!=outputPoint)
            {
                canShowCommand = false;
            }
        }
    }


    //如果输入文件有任何不对的，就不用做任何处理了
    if(!canShowCommand)
    {
        emit cannotShowCommand();
    }
    else {

        wholeTime = 0;
        std::sort(commandLines.begin(),commandLines.end(),[](Line &a, Line &b){return a.beginTime<b.beginTime;});
        for(int i=0;i<commandLines.size();i++)
        {

            qDebug()<<"commandLines.wholeLine: "<<commandLines[i].wholeLine;
            wholeTime = wholeTime>commandLines[i].endTime?wholeTime:commandLines[i].endTime;
        }

        status = new matrixComb[wholeTime+5];

        for(int i=0;i<commandLines.size();i++)
        {
            for (int index = commandLines[i].beginTime; index <= commandLines[i].endTime; index++)
            {
                status[index].isDecided = true;
            }
        }


        if(!isClean)
        {
            //然后在每一步之间检查是否满足动态约束，写一个分析的函数
            for(int i=0;i<commandLines.size();i++)
            {
                switch(commandLines[i].kind)
                {
                    case 1:
                        updateMatrixI(i);
                        break;
                    case 2:
                        updateMatrixMO(i);
                        break;
                    case 3:
                        updateMatrixS(i);
                        break;
                    case 4:
                        updateMatrixME(i);
                        break;
                    case 5:
                        updateMatrixMI(i);
                        break;
                    case 6:
                        updateMatrixO(i);
                        break;
                }

            }

            //0时刻应当都是空的，也是确定的
            status[0].isDecided = true;
            for(int index=1;index<=wholeTime;index++)
            {
                qDebug()<<"status["<<index<<"].isDecideds"<<status[index].isDecided;
                if(!status[index].isDecided)
                {
                    qDebug()<<"status["<<index<<"] is UnDecided!";
                    for(int j=index-1;j>=0;j--)
                    {
                        if(status[j].isDecided)
                        {
                            status[index] = status[j];
                        }
                    }
                }
            }

        }
    }
    myFile->close();
}

void Operation::updateMatrixI(int i)
{
    qDebug()<<"i = "<<i;
    QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,200);
    qDebug()<<"nowColor = "<<nowColor;
    int drawTime = commandLines[i].endTime;
    qDebug()<<"drawTime = "<<drawTime;
    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].hasTrace = false;
    qDebug()<<"updateMatrixI!";
}

void Operation::updateMatrixMO(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    qDebug()<<"nowTime = "<<nowTime;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
    qDebug()<<"nowColor = "<<nowColor;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
    status[nowTime].comb[commandLines[1].path[0].x()][commandLines[i].path[1].y()].dropColor = nowColor;
    qDebug()<<"updateMatrixMO!";
}

void Operation::updateMatrixS(int i)
{

    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    if(curPointIndex < 2)
    {
        QColor nowColor = status[nowTime-1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
        status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
        if(curPointIndex == 1)
        {
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isLongDrop = true;
            if(commandLines[i].path[0].y() == commandLines[i].path[1].y())
            {
                status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isFat = true;
            }
        }
    }
    else
    {
        colorSeed++;
        QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,200);
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = true;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].dropColor = nowColor;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isSmaller = true;
    }
    commandLines[i].curStep++;
    qDebug()<<"updateMatrixS!";
}

void Operation::updateMatrixME(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    if(curPointIndex == 0)
    {
        QColor nowColor = status[nowTime-1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
        status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
        nowColor = status[nowTime-1].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;
    }
    else
    {
        colorSeed++;
        QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,200);
        QPoint center = (commandLines[i].path[0]+commandLines[i].path[1])/2;
        status[nowTime].comb[center.x()][center.y()].isEmpty = false;
        status[nowTime].comb[center.x()][center.y()].dropColor = nowColor;
        if(curPointIndex == 1)
        {
            status[nowTime].comb[center.x()][center.y()].isLongDrop = true;
        }
        else {
            status[nowTime].comb[center.x()][center.y()].isBigger = true;
        }
    }

    commandLines[i].curStep++;
    qDebug()<<"updateMatrixME!";
}

void Operation::updateMatrixMI(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor = nowColor;
    commandLines[i].curStep++;
    qDebug()<<"updateMatrixMI!";
}

void Operation::updateMatrixO(int i)
{
    int nowTime = commandLines[i].beginTime;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].hasTrace = false;
    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = true;
    qDebug()<<"updateMatrixO!";
}


