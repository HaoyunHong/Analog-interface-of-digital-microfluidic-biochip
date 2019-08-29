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
        //qDebug()<<"here";

        Line L(array);
        //qDebug()<<"here";
        commandLines.push_back(L);
        //qDebug()<<"here";

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

    //qDebug()<<"here";

    //如果输入文件有任何不对的，就不用做任何处理了
    if(!canShowCommand)
    {
        emit cannotShowCommand();
    }
    else {

        //qDebug()<<"here";
        wholeTime = 0;
        std::sort(commandLines.begin(),commandLines.end(),[](Line &a, Line &b){return a.beginTime<b.beginTime;});
        //qDebug()<<"here";
        for(int i=0;i<commandLines.size();i++)
        {
            qDebug()<<"commandLines.wholeLine: "<<commandLines[i].wholeLine;
            wholeTime = wholeTime>commandLines[i].endTime?wholeTime:commandLines[i].endTime;
        }

        status = new matrixComb[wholeTime+5];
        lineTimeList = new QList<QStringList>[wholeTime+5];
        for(int t = 0;t<=wholeTime;t++)
        {
            //qDebug()<<"heret";
            for(int i=0;i<commandLines.size();i++)
            {
                //qDebug()<<"herei";
                for(int j=0;j<commandLines[i].lineList.size();j++)
                {
                    //qDebug()<<"herej";
                    if(commandLines[i].lineList[j][1].toInt()==t)
                    {
                        qDebug()<<"commandLines["<<i<<"].lineList["<<j<<"]"<<commandLines[i].lineList[j];
                        lineTimeList[t].append(commandLines[i].lineList[j]);
                        status[t].isDecided = true;
                    }
                }

            }
        }

        for(int i=0;i<=wholeTime;i++)
        {
            for(int j=0;j<lineTimeList[i].size();j++)
            {
                qDebug()<<"lineTimeList["<<i<<"]["<<j<<"]"<<lineTimeList[i][j];
            }
        }


        if(!isClean)
        {
            //然后在每一步之间检查是否满足动态约束，写一个分析的函数
           status[0].isDecided = true;
           for(int t = 0;t<=wholeTime;t++)
           {
               if(t>0)
               {
                   status[t]=status[t-1];
               }

               for(int k=0;k<lineTimeList[t].size();k++)
               {
                   if(lineTimeList[t][k][0]=="drawI")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       qDebug()<<"c = "<<c;
                       qDebug()<<"r = "<<r;

                       status[t].comb[c][r].isEmpty = false;
                       colorSeed++;
                       QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t-1].comb[c][r].dropColor = nowColor;
                   }
                   if(lineTimeList[t][k][0]=="move")
                   {
                       int c1 = lineTimeList[t][k][2].toInt();
                       int r1 = lineTimeList[t][k][3].toInt();
                       int c2 = lineTimeList[t][k][4].toInt();
                       int r2 = lineTimeList[t][k][5].toInt();

                       status[t].comb[c2][r2].isEmpty = false;
                       colorSeed++;
                       QColor nowColor = status[t-1].comb[c1][r1].dropColor;
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c2][r2].dropColor = nowColor;

                       status[t].isMm = true;
                   }
                   if(lineTimeList[t][k][0]=="drawLS")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       QColor nowColor = status[t].comb[c][r].dropColor;
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isLongDrop = true;
                       status[t].isStr = true;
                   }
                   if(lineTimeList[t][k][0]=="drawLFS")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       QColor nowColor = status[t].comb[c][r].dropColor;
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isLongDrop = true;
                       status[t].comb[c][r].isFat = true;
                       status[t].isStr = true;
                   }
                   if(lineTimeList[t][k][0]=="drawS")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       colorSeed++;
                       QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isSmaller = true;
                       status[t].isAp = true;
                   }
                   if(lineTimeList[t][k][0]=="drawLM")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       colorSeed++;
                       QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isLongDrop = true;

                   }
                   if(lineTimeList[t][k][0]=="drawLFM")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       colorSeed++;
                       QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isLongDrop = true;
                       status[t].comb[c][r].isFat = true;

                   }
                   if(lineTimeList[t][k][0]=="drawB")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].isEmpty = false;
                       QColor nowColor = status[t-1].comb[c][r].dropColor;
                       qDebug()<<"nowColor = "<<nowColor;
                       status[t].comb[c][r].dropColor = nowColor;
                       status[t].comb[c][r].isBigger = true;
                       qDebug()<<"Draw Bigger!";
                       status[t-1].isMer = true;
                   }
                   if(lineTimeList[t][k][0]=="clear")
                   {
                       int c = lineTimeList[t][k][2].toInt();
                       int r = lineTimeList[t][k][3].toInt();
                       status[t].comb[c][r].setDefault();
                   }

                   //qDebug()<<"here";
               }
           }
        }
    }
    myFile->close();
}

//void Operation::updateMatrixI(int i)
//{
//    qDebug()<<"i = "<<i;
//    colorSeed++;
//    QColor nowColor = QColor((colorSeed*220)%255,(colorSeed*20)%255,(colorSeed*60)%255,200);
//    qDebug()<<"nowColor = "<<nowColor;
//    int drawTime = commandLines[i].endTime;
//    qDebug()<<"drawTime = "<<drawTime;
//    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
//    status[drawTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].hasTrace = false;
//    qDebug()<<"updateMatrixI!";
//}

//void Operation::updateMatrixMO(int i)
//{
//    int nowTime = commandLines[i].beginTime+commandLines[i].curStep;
//    qDebug()<<"nowTime = "<<nowTime;
//    QColor nowColor;
//    for(int j=nowTime-1;j>=0;j--)
//    {
//        if(status[j].isDecided)
//        {
//            nowColor= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
//            break;
//        }
//    }

//    for(int j=0;j<inputPoints.size();j++)
//    {
//        if(commandLines[i].path[0] == inputPoints[j])
//        {
//            nowColor = status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
//            break;
//        }
//    }

//    qDebug()<<"nowColor = "<<nowColor;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;

//    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;

//    qDebug()<<"updateMatrixMO!";
//}

//void Operation::updateMatrixS(int i)
//{

//    int nowTime = commandLines[i].beginTime;
//    QColor nowColor;
//    for(int j=nowTime-1;j>=0;j--)
//    {
//        if(status[j].isDecided)
//        {
//            nowColor= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
//            break;
//        }
//    }

//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;

//    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
//    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isLongDrop = true;
//    if (commandLines[i].path[0].y() == commandLines[i].path[1].y())
//    {
//        status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isFat = true;
//    }

//    colorSeed++;
//    nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
//    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
//    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor;
//    status[nowTime + 2].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = true;
//    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isEmpty = false;
//    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].dropColor = nowColor;
//    status[nowTime + 2].comb[commandLines[i].path[2].x()][commandLines[i].path[2].y()].isSmaller = true;

//    qDebug() << "updateMatrixS!";
//}

//void Operation::updateMatrixME(int i)
//{
//    int nowTime = commandLines[i].beginTime;
//    QColor nowColor1;
//    for(int j=nowTime-1;j>=0;j--)
//    {
//        if(status[j].isDecided)
//        {
//            nowColor1= status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
//            status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
//            break;
//        }
//    }
//    QColor nowColor2;
//    for(int j=nowTime-1;j>=0;j--)
//    {
//        if(status[j].isDecided)
//        {
//            nowColor2= status[j].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor;
//            status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isBigger = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isBigger;
//            status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isSmaller = status[j].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isSmaller;
//            break;
//        }
//    }

//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor1;
//    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].isEmpty = false;
//    status[nowTime].comb[commandLines[i].path[1].x()][commandLines[i].path[1].y()].dropColor = nowColor2;

//    colorSeed++;
//    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
//    QPoint center = (commandLines[i].path[0] + commandLines[i].path[1]) / 2;
//    status[nowTime+1].comb[center.x()][center.y()].isEmpty = false;
//    status[nowTime+1].comb[center.x()][center.y()].dropColor = nowColor;
//    status[nowTime+1].comb[center.x()][center.y()].isLongDrop = true;
//    if (commandLines[i].path[0].y() == commandLines[i].path[1].y())
//    {
//        qDebug()<<"Is Fat!";
//        status[nowTime+1].comb[center.x()][center.y()].isFat = true;
//    }

//    status[nowTime + 2].comb[center.x()][center.y()].isEmpty = false;
//    status[nowTime + 2].comb[center.x()][center.y()].dropColor = nowColor;
//    status[nowTime + 2].comb[center.x()][center.y()].isBigger = true;

//    qDebug() << "updateMatrixME!";
//}

//void Operation::updateMatrixMI(int i)
//{
//    int nowTime = commandLines[i].beginTime;

//    QColor nowColor = status[nowTime - 1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;

//    for (int k = 0; k < commandLines[i].path.size(); k++)
//    {
//        status[nowTime].comb[commandLines[i].path[k].x()][commandLines[i].path[k].y()].isEmpty = false;
//        status[nowTime].comb[commandLines[i].path[k].x()][commandLines[i].path[k].y()].dropColor = nowColor;
//        nowTime++;
//    }

//    qDebug() << "updateMatrixMI!";
//}

//void Operation::updateMatrixO(int i)
//{
//    int nowTime = commandLines[i].beginTime;
//    QColor nowColor = status[nowTime-1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = false;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].dropColor = nowColor;
//    status[nowTime].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].hasTrace = false;
//    status[nowTime+1].comb[commandLines[i].path[0].x()][commandLines[i].path[0].y()].isEmpty = true;
//    qDebug()<<"updateMatrixO!";
//}

//void Operation::fillBlank(int i)
//{
//    if(!status[i].isDecided)
//    {
//        qDebug()<<"status["<<i<<"] UnDecided";
//        for(int j=i-1;j>=0;j--)
//        {
//            if(status[j].isDecided)
//            {
//                status[i] = status[j];
//                status[i].isDecided=true;
//                qDebug()<<"status["<<i<<"] = status["<<j<<"]";
//                break;
//            }
//        }
//    }
//}


