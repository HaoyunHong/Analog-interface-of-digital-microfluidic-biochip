#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
      time = 0;

      canShowCommand = true;

      isLimited = false;
      isClean = false;

      colorSeed = 0;

      cannotCleanTime = -1;
}

void Operation::setFile(QString path)
{
    qDebug()<<"In setFile path = "<<path;
    myFile = new QFile(path);
    qDebug()<<"File parsing!";
    this->parseFile();
    if(pollutedInfo.size()==0)
    {
        isClean = false;
        emit neednotClean();
    }
    stopTime = this->judge();
    if(isClean)
    {
        cleanMode();
    }

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


        //先把无论是否清洗模式都要做的存状态步骤做完
        status[0].isDecided = true;
        for (int t = 0; t <= wholeTime; t++)
        {
            if (t > 0)
            {
                status[t] = status[t - 1];
                status[t].soundDefault();
            }

            for (int k = 0; k < lineTimeList[t].size(); k++)
            {
                if (lineTimeList[t][k][0] == "drawI")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    qDebug() << "c = " << c;
                    qDebug() << "r = " << r;

                    status[t].comb[c][r].isEmpty = false;
                    colorSeed++;
                    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t - 1].comb[c][r].dropColor = nowColor;
                    //status[t].comb[c][r].pollutedSet.push_back(nowColor);
                    //然后在paintEvent里面遍历所有颜色画出污染
                }
                if (lineTimeList[t][k][0] == "move")
                {
                    int c1 = lineTimeList[t][k][2].toInt();
                    int r1 = lineTimeList[t][k][3].toInt();
                    int c2 = lineTimeList[t][k][4].toInt();
                    int r2 = lineTimeList[t][k][5].toInt();

                    status[t].comb[c2][r2].isEmpty = false;
                    colorSeed++;
                    QColor nowColor = status[t - 1].comb[c1][r1].dropColor;
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c2][r2].dropColor = nowColor;
                    //status[t].comb[c1][r1].pollutedSet.push_back(nowColor);

                    status[t].isMm = true;

                    Polluted pol;
                    for(int s=t-1;s>=0;s--)
                    {
                        if(status[s].comb[c2][r2].isEmpty == false)
                        {
                            pol.iniPol = s;
                            break;
                        }
                    }
                    if(status[t].comb[c2][r2].pollutedSet.size()>0)
                    {

                        pol.time=t;
                        pol.p = QPoint(c2,r2);
                        pollutedInfo.push_back(pol);
                    }


                }
                if (lineTimeList[t][k][0] == "drawLS")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    status[t].comb[c][r].isEmpty = false;
                    QColor nowColor = status[t].comb[c][r].dropColor;
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t].comb[c][r].isLongDrop = true;
                    status[t].isStr = true;
                }
                if (lineTimeList[t][k][0] == "drawLFS")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    status[t].comb[c][r].isEmpty = false;
                    QColor nowColor = status[t].comb[c][r].dropColor;
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t].comb[c][r].isLongDrop = true;
                    status[t].comb[c][r].isFat = true;
                    status[t].isStr = true;
                }
                if (lineTimeList[t][k][0] == "drawS")
                {
                    int c1 = lineTimeList[t][k][2].toInt();
                    int r1 = lineTimeList[t][k][3].toInt();
                    int c2 = lineTimeList[t][k][4].toInt();
                    int r2 = lineTimeList[t][k][5].toInt();
                    status[t].comb[c1][r1].isEmpty = false;
                    status[t].comb[c2][r2].isEmpty = false;
                    colorSeed++;
                    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c1][r1].dropColor = nowColor;
                    status[t].comb[c1][r1].isSmaller = true;
                    status[t].comb[c1][r1].pollutedSet.push_back(nowColor);
                    colorSeed++;
                    nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
                    status[t].comb[c2][r2].dropColor = nowColor;
                    status[t].comb[c2][r2].isSmaller = true;
                    status[t].isAp = true;
                    //status[t].comb[c2][r2].pollutedSet.push_back(nowColor);

                }
                if (lineTimeList[t][k][0] == "drawLM")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    status[t].comb[c][r].isEmpty = false;
                    colorSeed++;
                    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t].comb[c][r].isLongDrop = true;
                    //status[t].comb[c][r].pollutedSet.push_back(nowColor);

                }
                if (lineTimeList[t][k][0] == "drawLFM")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    status[t].comb[c][r].isEmpty = false;
                    colorSeed++;
                    QColor nowColor = QColor((colorSeed * 220) % 255, (colorSeed * 20) % 255, (colorSeed * 60) % 255, 200);
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t].comb[c][r].isLongDrop = true;
                    status[t].comb[c][r].isFat = true;
                    //status[t].comb[c][r].pollutedSet.push_back(nowColor);

                }
                if (lineTimeList[t][k][0] == "drawB")
                {
                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    status[t].comb[c][r].isEmpty = false;
                    QColor nowColor = status[t - 1].comb[c][r].dropColor;
                    qDebug() << "nowColor = " << nowColor;
                    status[t].comb[c][r].dropColor = nowColor;
                    status[t].comb[c][r].isBigger = true;
                    qDebug() << "Draw Bigger!";

                    status[t].isMer = true;
                    qDebug() << "status[" << t << "].isMer = true";
                }
                if (lineTimeList[t][k][0] == "clear")
                {

                    int c = lineTimeList[t][k][2].toInt();
                    int r = lineTimeList[t][k][3].toInt();
                    QColor nowColor = status[t].comb[c][r].dropColor;
                    qDebug() << "nowColor = " << nowColor;

                    status[t].comb[c][r].setDefault();
                    status[t].comb[c][r].pollutedSet.push_back(nowColor);

                }


                //只是轨迹变化，其它并不变，等做了一次清洗操作后，如果后面的之前会发生污染液滴事件的点也被清洗了，那就跳过它，再去清洗下一个
                //如果pollutedInfo已被赋值，就去寻找每一个该去clean的之前的时间
                //说不定前面的清理已经将后面的一个polluted给去除了
            }
        }
    }


    myFile->close();
}


//这里还可以再加入信息
int Operation::cannotClean()
{
    int cannotCleanTime = -1;
    if(isClean)
    {
        qDebug()<<"Judging clean!";
        for(int i=0;i<commandLines.size();i++)
        {
            bool flag = false;
            qDebug()<<"Judging clean!";
            if(commandLines[i].action == "Merge")
            {
                qDebug()<<"Merge case!";
                qDebug()<<"commandLines["<<i<<"].wholeLine: "<<commandLines[i].wholeLine;
                QPoint p1 = commandLines[i].path[0];
                QPoint p2 = commandLines[i].path[1];
                QPoint p = (p1+p2)/2;
                int now = commandLines[i].beginTime;
                for(int j=i+1;j<commandLines.size();j++)
                {
                    if(commandLines[j].action == "Move" && commandLines[j].beginTime == commandLines[i].endTime && commandLines[j].path[0]==p &&(commandLines[j].path[1]==p1 || commandLines[j].path[1]==p2))
                    {
                        qDebug()<<"Here!";
                        qDebug()<<"commandLines["<<j<<"].wholeLine: "<<commandLines[j].wholeLine;
                        cannotCleanTime = commandLines[j].beginTime;
                        qDebug()<<"cannotCleanTime: "<<cannotCleanTime;
                        flag = true;
                        break;
                    }
                    if(commandLines[j].action == "Mix" && commandLines[j].beginTime == commandLines[i].endTime && commandLines[j].path[0]==p &&(commandLines[j].path[1]==p1 || commandLines[j].path[1]==p2))
                    {
                        qDebug()<<"Here!";
                        qDebug()<<"commandLines["<<j<<"].wholeLine: "<<commandLines[j].wholeLine;
                        cannotCleanTime = commandLines[j].beginTime;
                        qDebug()<<"cannotCleanTime: "<<cannotCleanTime;
                        flag = true;
                        break;
                    }
                }
                if(flag) break;
            }
        }
    }

    return cannotCleanTime;
}

int Operation::judge()
{
    qDebug()<<"judge~judge~";
    qDebug()<<wholeTime;

    //只要找到最新violate的就可以
    bool violate = false;
    int t = -1;
    for (int now = 0; now <= wholeTime; now++)
    {
        //qDebug()<<"Here now:"<<now;
        //qDebug()<<"colNum = "<<colNum;
        //qDebug()<<"rowNum = "<<rowNum;
        for (int i = 1; i <= colNum; i++)
        {
            //qDebug()<<"Here i: "<<i;
            for (int j = 1; j <= rowNum; j++)
            {
                //qDebug()<<"Here j: "<<j;
                //qDebug()<<"status["<<now<<"].comb["<<i<<"]["<<j<<"]";
                if (!status[now].comb[i][j].isEmpty)
                {
                    qDebug()<<"Judging status["<<now<<"].comb["<<i<<"]["<<j<<"]";
                    if (i < colNum && i > 1 && j < rowNum && j>1)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j < rowNum && j>1";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now + 1].comb[i - 1][j - 1].isEmpty
                            || !status[now + 1].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now + 1].comb[i + 1][j - 1].isEmpty
                            || !status[now + 1].comb[i + 1][j + 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }

                    }

                    if (i == colNum && j > 0 && j < rowNum)
                    {
                        //qDebug()<<"i == colNum && j > 0 && j < rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now + 1].comb[i - 1][j - 1].isEmpty
                            || !status[now + 1].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }
                    if (i == 1 && j > 0 && j < rowNum)
                    {
                       // qDebug()<<"i == 1 && j > 0 && j < rowNum";
                        if (!status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now + 1].comb[i + 1][j - 1].isEmpty
                            || !status[now + 1].comb[i + 1][j + 1].isEmpty)
                        {
                           // qDebug()<<"Here!";
                            violate = true;
                            break;
                        }



                    }

                    if (i < colNum && i > 1 && j == 1)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j == 1";
                        if (!status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now + 1].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now + 1].comb[i + 1][j + 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }

                    }

                    if (i < colNum && i > 1 && j == rowNum)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j == rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now + 1].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now + 1].comb[i + 1][j - 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }

                    if (i == colNum && j == rowNum)
                    {
                        //qDebug()<<"i == colNum && j == rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now + 1].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }

                    if (i == colNum && j == 1)
                    {
                        //qDebug()<<"i == colNum && j == 1";
                        if (!status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now + 1].comb[i][j + 1].isEmpty)
                        {
                            qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }

                    if (i == 1 && j == 1)
                    {
                        qDebug()<<"i == 1 && j == 1";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now + 1].comb[i + 1][j + 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }

                    if (i == 1 && j == rowNum)
                    {
                        //qDebug()<<"i == 1 && j == rowNum";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now + 1].comb[i + 1][j - 1].isEmpty)
                        {
                            //qDebug()<<"Here!";
                            violate = true;
                            break;
                        }
                    }
                }
                if (violate)
                {
                    t = now;
                    qDebug() << "status[" << now << "].comb[" << i << "][" << j << "] is Violating!";
                    return t;
                }
            }
        }
    }
    return t;
}


void Operation::changeIsSafe()
{
    for(int now=0;now<=wholeTime;now++)
    {
        for(int i=1;i<=colNum;i++)
        {
            for(int j=1;j<=rowNum;j++)
            {
                if (!status[now].comb[i][j].isEmpty)
                {
                    status[now].comb[i][j].isSafe=false;
                }
                if (status[now].comb[i][j].isEmpty)
                {
                    if (i < colNum && i > 1 && j < rowNum && j>1)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j < rowNum && j>1";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }

                    }

                    if (i == colNum && j > 0 && j < rowNum)
                    {
                        //qDebug()<<"i == colNum && j > 0 && j < rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }
                    }
                    if (i == 1 && j > 0 && j < rowNum)
                    {
                       // qDebug()<<"i == 1 && j > 0 && j < rowNum";
                        if (!status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty)
                        {
                           status[now].comb[i][j].isSafe=false;
                        }



                    }

                    if (i < colNum && i > 1 && j == 1)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j == 1";
                        if (!status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }

                    }

                    if (i < colNum && i > 1 && j == rowNum)
                    {
                        //qDebug()<<"i < colNum && i > 1 && j == rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty
                            || !status[now].comb[i + 1][j].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }
                    }

                    if (i == colNum && j == rowNum)
                    {
                        //qDebug()<<"i == colNum && j == rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }
                    }

                    if (i == colNum && j == 1)
                    {
                        //qDebug()<<"i == colNum && j == 1";
                        if (!status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                           status[now].comb[i][j].isSafe=false;
                        }
                    }

                    if (i == 1 && j == 1)
                    {
                        qDebug()<<"i == 1 && j == 1";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                           status[now].comb[i][j].isSafe=false;
                        }
                    }

                    if (i == 1 && j == rowNum)
                    {
                        //qDebug()<<"i == 1 && j == rowNum";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe=false;
                        }
                    }
                }
            }
        }
    }

    for(int now=0;now<=wholeTime;now++)
    {
        for(int i=1;i<=colNum;i++)
        {
            for(int j=1;j<=rowNum;j++)
            {
                qDebug()<<"status["<<now<<"].comb["<<i<<"]["<<j<<"].isSafe"<<status[now].comb[i][j].isSafe;
            }
         }

    }
}

//针对每一个最早的污染点来洗，使用index来取得值即可，如果不需要清洗也就不用调用对应index的函数
//其实应该是这里来判断是不是可以洗
int Operation::startCleanTime(int index)
{

    int start = -1;
    for(int t=pollutedInfo[index].time-1;t>pollutedInfo[index].iniPol;t--)
    {
        //清洗点是安全的，并且要保证出口和入口也是安全的，这样才能洗
        if(status[t].comb[pollutedInfo[index].p.x()][pollutedInfo[index].p.y()].isSafe && status[t].comb[1][1].isSafe)
        {
            start = t;

            break;
        }
    }

    qDebug()<<"clean startTime: "<<start;

    pollutedInfo[index].cleanTime=start;

    qDebug()<<"pollutedInfo["<<index<<"].cleanTime: "<<pollutedInfo[index].cleanTime;

    if(start == -1)
    {
        cannotCleanTime = pollutedInfo[index].time;
    }
    return start;
}

void Operation::cleanMode()
{
    changeIsSafe();
    qDebug()<<"isClean: "<<isClean;
    if(isClean)
    {

        //这里不怕,就是按时间顺序排的
        for(int i =0;i<pollutedInfo.size();i++)
        {
            qDebug()<<"pollutedInfo["<<i<<"].time: "<<pollutedInfo[i].time;
            qDebug()<<"pollutedInfo["<<i<<"].p: "<<pollutedInfo[i].p;
            //此时还未初始化
            //qDebug()<<"pollutedInfo["<<i<<"].cleanTime: "<<pollutedInfo[i].cleanTime;
        }
    }

    int polIndex=0;
    while(polIndex<pollutedInfo.size())
    {
        qDebug()<<"polIndex: "<<polIndex;

        startCleanTime(polIndex);

        qDebug()<<"Here!";
        if(pollutedInfo[polIndex].cleanTime==-1)
        {
            return;
        }
        for(int t =0;t<pollutedInfo[polIndex].cleanTime;t++)
        {
            cleanStatus.push_back(status[t]);
        }

        //然后开始对入口到清洗点和清洗点到出口分别进行bfs，寻找最短路径并且至多清洗路径上的三个点（即到清洗点之前不能已经洗了三个点）
        //寻找最短路径，把每一次能走到终点的路径存下来，如果后面走着还有更短的，更新存储的最短路径
        //然后把该时刻安全的点和没有被Block的点加入队列，开始bfs
        //用一个清洗次数的计数器
        //如果怎么走，清洗液滴都会违反以下规则
        /*
        1. 还没到清洗点时已被污染三次（解决办法，再来一个液滴，重复走这条路）
        2. 走不到清洗点，报错，指出此时无法清洗
        3. 走不到终点，报错，指出此时无法清洗
        */


        polIndex++;
    }





    int cleanTime = pollutedInfo[polIndex].cleanTime;
     cleanStatus[cleanTime].comb[1][1].hasWashing = true;
}


