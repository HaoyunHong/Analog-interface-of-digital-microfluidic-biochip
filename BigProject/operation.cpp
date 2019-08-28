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
                qDebug()<<"Now command: "<<commandLines[i].wholeLine;

                int now = commandLines[i].endTime;
                switch(commandLines[i].kind)
                {
                    case 1:
                        updateMatrixI(i);
                        fillBlank(i);
                        break;
                    case 2:
                        updateMatrixMO(i);
                        fillBlank(i);
                        break;
                    case 3:
                        updateMatrixS(i);
                        fillBlank(i);
                        break;
                    case 4:
                        updateMatrixME(i);
                        fillBlank(i);
                        break;
                    case 5:
                        updateMatrixMI(i);
                        fillBlank(i);
                        break;
                    case 6:
                        updateMatrixO(i);
                        fillBlank(i);
                        break;
                }

            }

            //0时刻应当都是空的，也是确定的
            status[0].isDecided = true;

            for(int i=0;i<wholeTime;i++)
            {
                qDebug()<<"status["<<i<<"].isDecided: "<<status[i].isDecided;
                if(!status[i].isDecided)
                {
                    for(int j=i-1;j>=0;j--)
                    {
                        if(status[j].isDecided)
                        {
                            status[i] = status[j];
                            status[i].isDecided=true;
                            qDebug()<<"status["<<i<<"] = status["<<j<<"]";
                            break;
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
    colorSeed++;
    QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
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
    QColor nowColor;
    for(int j=nowTime-1;j>=0;j--)
    {
        if(status[j].isDecided)
        {
            nowColor= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
            break;
        }
    }

    for(int j=0;j<inputPoints.size();j++)
    {
        if(commandLines[i].path[0] == inputPoints[j])
        {
            nowColor = status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
            break;
        }
    }

    qDebug()<<"nowColor = "<<nowColor;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;

    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;

    qDebug()<<"updateMatrixMO!";
}

void Operation::updateMatrixS(int i)
{

    int nowTime = commandLines[i].beginTime;
    QColor nowColor;
    for(int j=nowTime-1;j>=0;j--)
    {
        if(status[j].isDecided)
        {
            nowColor= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
            break;
        }
    }

    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;

    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isLongDrop = true;
    if (commandLines[i].path[0].y() == commandLines[i].path[1].y())
    {
        status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isFat = true;
    }

    colorSeed++;
    nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;
    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = true;
    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isEmpty = false;
    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].dropColor = nowColor;
    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isSmaller = true;

    qDebug() << "updateMatrixS!";
}

void Operation::updateMatrixME(int i)
{
    int nowTime = commandLines[i].beginTime;
    QColor nowColor1;
    for(int j=nowTime-1;j>=0;j--)
    {
        if(status[j].isDecided)
        {
            nowColor1= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
            break;
        }
    }
    QColor nowColor2;
    for(int j=nowTime-1;j>=0;j--)
    {
        if(status[j].isDecided)
        {
            nowColor2= status[j].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor;
            status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
            status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
            break;
        }
    }

    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor1;
    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor2;

    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
    QPoint center = (commandLines[i].path[0] + commandLines[i].path[1]) / 2;
    status[nowTime+1].comb[center.x()][center.y()].isEmpty = false;
    status[nowTime+1].comb[center.x()][center.y()].dropColor = nowColor;
    status[nowTime+1].comb[center.x()][center.y()].isLongDrop = true;
    if (commandLines[i].path[0].y() == commandLines[i].path[1].y())
    {
        qDebug()<<"Is Fat!";
        status[nowTime+1].comb[center.x()][center.y()].isFat = true;
    }

    status[nowTime + 2].comb[center.x()][center.y()].isEmpty = false;
    status[nowTime + 2].comb[center.x()][center.y()].dropColor = nowColor;
    status[nowTime + 2].comb[center.x()][center.y()].isBigger = true;

    qDebug() << "updateMatrixME!";
}

void Operation::updateMatrixMI(int i)
{
    int nowTime = commandLines[i].beginTime;

    QColor nowColor = status[nowTime - 1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;

    for (int k = 0; k < commandLines[i].path.size(); k++)
    {
        status[nowTime].comb[commandLines[i].path[k].x()][commandLines[i].path[k].y()].isEmpty = false;
        status[nowTime].comb[commandLines[i].path[k].x()][commandLines[i].path[k].y()].dropColor = nowColor;
        nowTime++;
    }

    qDebug() << "updateMatrixMI!";
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

void Operation::fillBlank(int i)
{
    if(!status[i].isDecided)
    {
        qDebug()<<"status["<<i<<"] UnDecided";
        for(int j=i-1;j>=0;j--)
        {
            if(status[j].isDecided)
            {
                status[i] = status[j];
                status[i].isDecided=true;
                qDebug()<<"status["<<i<<"] = status["<<j<<"]";
                break;
            }
        }
    }
}


