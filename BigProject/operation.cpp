#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
      time = 0;

      canShowCommand = true;

      isLimited = false;
      isClean = false;

      colorSeed = 0;
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
            for(int j=0;j<inputPoints.size();j++)
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

        std::sort(commandLines.begin(),commandLines.end(),[](Line &a, Line &b){return a.beginTime<b.beginTime;});
        for(int i=0;i<commandLines.size();i++)
        {
            qDebug()<<"commandLines.wholeLine: "<<commandLines[i].wholeLine;
            //if(commandLines[i])
        }

//        colorSeed++;
//        color = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,(colorSeed*789)%255);
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
                emit updatePic();
            }
        }
    }
    myFile->close();
}

//每次能够把一个状态存入前先初始化
//这里设置的时候坐标就要反过来
void Operation::setRC(int row, int col)
{
      status.last().setValidMatrix(col,row);
}

void Operation::updateMatrixI(int i)
{
    QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,(colorSeed*789)%255);
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor = nowColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].hasTrace = false;
    commandLines[i].curStep++;
}

void Operation::updateMatrixMO(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor = nowColor;
    commandLines[i].curStep++;
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
        }
    }
    else
    {
        colorSeed++;
        QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,(colorSeed*789)%255);
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;
        status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = true;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].dropColor = nowColor;
        status[nowTime].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isSmaller = true;
    }
    commandLines[i].curStep++;
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
        QColor nowColor = QColor((colorSeed*123)%255,(colorSeed*345)%255,(colorSeed*567)%255,(colorSeed*789)%255);
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
}

void Operation::updateMatrixMI(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor = nowColor;
    commandLines[i].curStep++;
}

void Operation::updateMatrixO(int i)
{
    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
    int curPointIndex = commandLines[i].curStep;
    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].dropColor = nowColor;
    status[nowTime].comb[commandLines[i].path[curPointIndex].x()][commandLines[i].path[curPointIndex].y()].hasTrace = false;
    commandLines[i].curStep++;
}


