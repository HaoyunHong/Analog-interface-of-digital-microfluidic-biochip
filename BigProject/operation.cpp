#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
    time = 0;

    canShowCommand = true;

    isLimited = false;
    isClean = false;

    colorSeed = 0;

    cannotCleanTime = -1;

    wholeCleanTime = 0;
    cleanLength = 0;
}

void Operation::setFile(QString path)
{
    qDebug() << "In setFile path = " << path;
    myFile = new QFile(path);
    qDebug() << "File parsing!";
    this->parseFile();
    stopTime = this->judge();

}

void Operation::setEveryInput(QPoint pIn)
{
    inputPoints.push_back(pIn);
    qDebug() << "In operation inputPoints.size() = " << inputPoints.size();
    qDebug() << "In operation current inputPoint = " << pIn;
}

void Operation::setTheOut(QPoint pOut)
{
    outputPoint = pOut;
    qDebug() << "In operation outputPoint = " << outputPoint;
}

void Operation::parseFile()
{
    QByteArray array;
    myFile->open(QIODevice::ReadOnly);
    while (myFile->atEnd() == false)
    {
        //每次读一行
        array = myFile->readLine();
        //qDebug()<<"here";

        Line L(array);
        //qDebug()<<"here";
        commandLines.push_back(L);
        //qDebug()<<"here";

    }

    for (int i = 0; i < commandLines.size(); i++)
    {

        if (commandLines[i].kind == 1)
        {
            int cntDiff = 0;
            for (int j = 0; j < inputPoints.size(); j++)
            {
                if (commandLines[i].path[0] == inputPoints[j])
                {
                    break;
                }
                else {
                    cntDiff++;
                }
            }
            if (cntDiff == inputPoints.size())
            {
                canShowCommand = false;
            }
        }


        if (commandLines[i].kind == 6)
        {
            if (commandLines[i].path[0] != outputPoint)
            {
                canShowCommand = false;
            }
        }
    }

    //qDebug()<<"here";

    //如果输入文件有任何不对的，就不用做任何处理了
    if (!canShowCommand)
    {
        emit cannotShowCommand();
    }
    else {

        //qDebug()<<"here";
        wholeTime = 0;
        std::sort(commandLines.begin(), commandLines.end(), [](Line &a, Line &b) {return a.beginTime < b.beginTime; });
        //qDebug()<<"here";
        for (int i = 0; i < commandLines.size(); i++)
        {
            qDebug() << "commandLines.wholeLine: " << commandLines[i].wholeLine;
            wholeTime = wholeTime > commandLines[i].endTime ? wholeTime : commandLines[i].endTime;
        }

        status = new matrixComb[wholeTime + 5];
        lineTimeList = new QList<QStringList>[wholeTime + 5];
        for (int t = 0; t <= wholeTime; t++)
        {
            //qDebug()<<"heret";
            for (int i = 0; i < commandLines.size(); i++)
            {
                //qDebug()<<"herei";
                for (int j = 0; j < commandLines[i].lineList.size(); j++)
                {
                    //qDebug()<<"herej";
                    if (commandLines[i].lineList[j][1].toInt() == t)
                    {
                        qDebug() << "commandLines[" << i << "].lineList[" << j << "]" << commandLines[i].lineList[j];
                        lineTimeList[t].append(commandLines[i].lineList[j]);
                        status[t].isDecided = true;
                    }
                }

            }
        }

        for (int i = 0; i <= wholeTime; i++)
        {
            for (int j = 0; j < lineTimeList[i].size(); j++)
            {
                qDebug() << "lineTimeList[" << i << "][" << j << "]" << lineTimeList[i][j];
            }
        }


        //先把无论是否清洗模式都要做的存状态步骤做完
        status[0].isDecided = true;
        for (int t = 0; t <= wholeTime; t++)
        {
            if (!isClean)
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
                        if (status[t].comb[c2][r2].pollutedSet.size() > 0 && nowColor != status[t].comb[c2][r2].pollutedSet[0])
                        {
                            for (int s = t - 1; s >= 0; s--)
                            {
                                if (status[s].comb[c2][r2].isEmpty == false)
                                {
                                    pol.iniPol = s;
                                    break;
                                }
                            }

                            pol.time = t;
                            pol.p = QPoint(c2, r2);
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

            else
            {

                qDebug() << "isClean: " << isClean;

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

                        status[t].comb[c1][r1].isEmpty = true;
                        status[t].comb[c2][r2].isEmpty = false;
                        colorSeed++;
                        QColor nowColor = status[t - 1].comb[c1][r1].dropColor;
                        qDebug() << "nowColor = " << nowColor;
                        status[t].comb[c2][r2].dropColor = nowColor;


                        status[t].isMm = true;

                        Polluted pol;
                        if (status[t].comb[c2][r2].pollutedSet.size() > 0 && nowColor != status[t].comb[c2][r2].pollutedSet[0])
                        {
                            for (int s = t - 1; s >= 0; s--)
                            {
                                if (status[s].comb[c2][r2].isEmpty == false)
                                {
                                    pol.iniPol = s;
                                    break;
                                }
                            }

                            pol.time = t;
                            pol.p = QPoint(c2, r2);
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
                        status[t].comb[c][r].isEmpty = true;
                    }
                }



                if (pollutedInfo.size() > 0)
                {
                    qDebug() << "pollutedInfo.size()" << pollutedInfo.size();

                    changeIsSafe();
                    for (int s = 0; s < pollutedInfo.size(); s++)
                    {
                        Polluted pol = pollutedInfo[s];

                        qDebug() << pol.p;
                        qDebug() << pol.time;



                        qDebug() << "t = " << t;

                        startCleanTime(pol);

                        qDebug() << "pol.cleanTime" << pol.cleanTime;

                        int trueCleanTime = pol.cleanTime + cleanLength;
                        qDebug() << "trueCleanTime: " << trueCleanTime;

                        if (trueCleanTime == -1)
                        {
                            qDebug() << "Can't clean when " << pol.time;
                            cannotCleanTime = cannotCleanTime = cannotCleanTime < pol.time ? cannotCleanTime : pol.time;
                            return;
                        }


                        cleanTimes.push_back(pol.cleanTime);

                        qDebug() << "Here!";
                        if (cleanTimes.size() == 1)
                        {
                            for (int m = 0; m <= trueCleanTime; m++)
                            {
                                cleanStatus.push_back(status[m]);
                            }
                        }
                        else {
                            int index = cleanTimes.size();
                            for (int m = cleanTimes[index - 2]; m <= cleanTimes[index - 1]; m++)
                            {
                                qDebug() << "m = " << m;
                                cleanStatus.push_back(status[m]);
                            }
                        }
                        cleanStatus.last().soundDefault();
                        cleanStatus.last().isMm = true;

                        for (int i = 1; i <= colNum; i++)
                        {
                            for (int j = 1; j <= rowNum; j++)
                            {
                                qDebug() << "cleanStatus[" << pol.cleanTime << "].comb[" << i << "][" << j << "].isEmpty" << cleanStatus[pol.cleanTime].comb[i][j].isEmpty;

                                qDebug() << "cleanStatus[" << pol.cleanTime << "].comb[" << i << "][" << j << "].isSafe" << cleanStatus[pol.cleanTime].comb[i][j].isSafe;
                                qDebug() << "cleanStatus[" << pol.cleanTime << "].comb[" << i << "][" << j << "].isBlock" << cleanStatus[pol.cleanTime].comb[i][j].isBlock;
                                if (cleanStatus[trueCleanTime].comb[i][j].isSafe && !cleanStatus[trueCleanTime].comb[i][j].isBlock)
                                {
                                    QPoint p(i, j);
                                    points.push_back(p);
                                }
                            }
                        }

                        QPoint mid(pol.p);
                        qDebug() << "mid: " << mid;

                        //首先floyd，寻找任意两点间最短路，然后选路径的前3个点clean，如果没有clean到mid就再出一个水滴，沿原来的路径走

                        int pointNum = points.size();
                        int** dist = new int*[pointNum];
                        for (int i = 0; i < pointNum; i++)
                        {
                            dist[i] = new int[pointNum];
                        }

                        qDebug() << "pointNum = " << pointNum;

                        for (int i = 0; i < pointNum; i++)
                        {
                            qDebug() << "points[" << i << "]" << points[i];
                        }

                        path = new int*[pointNum];
                        for (int i = 0; i < pointNum; i++)
                        {
                            path[i] = new int[pointNum];
                        }

                        int middle = -1;

                        for (int i = 0; i < pointNum; i++)
                        {
                            if (points[i] == mid)
                            {
                                middle = i;
                            }
                        }

                        qDebug() << "middle: " << middle;


                        for (int i = 0; i < pointNum; i++)
                        {
                            for (int j = 0; j < pointNum; j++)
                            {
                                if (i == j)
                                {
                                    dist[i][j] = 0;
                                }
                                else if (qAbs(points[i].x() - points[j].x()) + qAbs(points[i].y() - points[j].y()) == 1)
                                {
                                    dist[i][j] = 1;
                                    //qDebug() << "Origin: dist[" << i << "][" << j << "] = 1";
                                }
                                else {
                                    dist[i][j] = MAXNUM;
                                }
                            }
                        }

                        for (int i = 0; i < pointNum; i++)
                        {
                            for (int j = 0; j < pointNum; j++)
                            {

                                if (dist[i][j] < MAXNUM)
                                {
                                    path[i][j] = i;
                                }
                                else {
                                    path[i][j] = -1;
                                }

                            }

                        }


                        for (int k = 0; k < pointNum; k++)
                        {
                            for (int i = 0; i < pointNum; i++)
                            {
                                for (int j = 0; j < pointNum; j++)
                                {
                                    if (dist[i][k] + dist[k][j] < dist[i][j])
                                    {
                                        dist[i][j] = dist[i][k] + dist[k][j];
                                        path[i][j] = path[k][j];
                                    }
                                }
                            }
                        }

                        //                        for (int i = 0; i < pointNum; i++)
                        //                        {
                        //                            for (int j = 0; j < pointNum; j++)
                        //                            {
                        //                                qDebug() << "After: dist[" << i << "][" << j << "] = " << dist[i][j];
                        //                                qDebug() << "After: path[" << i << "][" << j << "] = " << path[i][j];
                        //                            }

                        //                        }

                        out(0, middle);
                        wholeRoad.push_back(QPoint(1, 1));
                        for (int k = 0; k < road.size(); k++)
                        {
                            wholeRoad.push_back(points[road[k]]);
                        }
                        wholeRoad.push_back(mid);
                        road.clear();

                        out(middle, pointNum - 1);
                        for (int k = 0; k < road.size(); k++)
                        {
                            wholeRoad.push_back(points[road[k]]);
                        }
                        wholeRoad.push_back(QPoint(colNum, rowNum));
                        road.clear();

                        qDebug() << "wholeRoad.size(): " << wholeRoad.size();
                        for (int s = 0; s < wholeRoad.size(); s++)
                        {
                            qDebug() << "wholeRoad[" << s << "]: " << wholeRoad[s];
                        }


                        cleanStatus[trueCleanTime].comb[1][1].hasWashing = true;
                        int oneCleanDropTime = trueCleanTime;

                        //先不加约束
                        for (int n = 1; n < wholeRoad.size(); n++)
                        {
                            qDebug() << "n: " << n;
                            oneCleanDropTime++;
                            qDebug() << "oneCleanDropTime: " << oneCleanDropTime;
                            cleanStatus.push_back(cleanStatus[oneCleanDropTime - 1]);
                            cleanStatus[oneCleanDropTime].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].hasWashing = false;
                            cleanStatus[oneCleanDropTime].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].pollutedSet.clear();
                            cleanStatus[oneCleanDropTime].comb[wholeRoad[n].x()][wholeRoad[n].y()].hasWashing = true;
                            qDebug() << "wholeRoad[" << n << "]: " << wholeRoad[n];

                            status[pol.cleanTime - 1].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].pollutedSet.clear();
                            status[pol.cleanTime].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].pollutedSet.clear();

                            status[pol.cleanTime + 1].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].pollutedSet.clear();
                            status[t].comb[wholeRoad[n - 1].x()][wholeRoad[n - 1].y()].pollutedSet.clear();
                        }

                        wholeCleanTime = oneCleanDropTime;

                        cleanLength += wholeRoad.size();

                        qDebug() << "wholeCleanTime =" << wholeCleanTime;

                        //        while(cleanStatus[oneCleanDropTime].comb[mid.x()][mid.y()].pollutedSet.size()>0)
                        //        {
                        //            int limitedTime = 3;
                        //            qDebug()<<"mid pollution size: "<<cleanStatus[oneCleanDropTime].comb[mid.x()][mid.y()].pollutedSet.size();
                        //            for(int t=1;t<wholeRoad.size()+1;t++)
                        //            {
                        //                qDebug()<<"t: "<<t;
                        //                oneCleanDropTime++;
                        //                qDebug()<<"oneCleanDropTime: "<<oneCleanDropTime;
                        //                cleanStatus.push_back(cleanStatus[oneCleanDropTime-1]);
                        //                cleanStatus[oneCleanDropTime].comb[wholeRoad[t-1].x()][wholeRoad[t-1].y()].hasWashing = false;
                        //                if(limitedTime>0 && cleanStatus[oneCleanDropTime].comb[wholeRoad[t-1].x()][wholeRoad[t-1].y()].pollutedSet.size()>0)
                        //                {
                        //                    limitedTime--;
                        //                    qDebug()<<"limitedTime: "<<limitedTime;
                        //                    cleanStatus[oneCleanDropTime].comb[wholeRoad[t-1].x()][wholeRoad[t-1].y()].pollutedSet.clear();
                        //                }
                        //                qDebug()<<"here!";
                        //                cleanStatus[oneCleanDropTime].comb[wholeRoad[t].x()][wholeRoad[t].y()].hasWashing = true;
                        //                qDebug()<<"here!";
                        //            }
                        //        }


                        //然后开始对入口到清洗点和清洗点到出口分别进行寻找最短路径并且至多清洗路径上的三个点（即到清洗点之前不能已经洗了三个点）
                        //寻找最短路径，把每一次能走到终点的路径存下来，如果后面走着还有更短的，更新存储的最短路径
                        //然后把该时刻安全的点和没有被Block的点加入队列，开始寻找最短路
                        //用一个清洗次数的计数器
                        //如果怎么走，清洗液滴都会违反以下规则
                        /*
                        1. 还没到清洗点时已被污染三次（解决办法，再来一个液滴，重复走这条路）
                        2. 走不到清洗点，报错，指出此时无法清洗
                        3. 走不到终点，报错，指出此时无法清洗
                        */


                        //一定要记得不用vector了之后把东西清空丫
                        points.clear();
                        wholeRoad.clear();
                        qDebug()<<"cleanLength: "<<cleanLength;
                    }

                    pollutedInfo.clear();

                }





}
        }

        if (isClean)
        {
            int wholeTimeFinal = cleanLength + wholeTime;
            qDebug()<<"wholeTimeFinal: "<<wholeTimeFinal;

            for (int k = wholeCleanTime - cleanLength; k <= wholeTime; k++)
            {
                cleanStatus.push_back(status[k]);
            }
            wholeCleanTime = wholeTimeFinal;
            emit sendWholeCleanTimeSignal(wholeCleanTime);
        }

    }
    myFile->close();
}


//这里还可以再加入信息
int Operation::cannotClean()
{
    int cannotCleanTime = MAXNUM;
    if (isClean)
    {
        qDebug() << "Judging clean!";
        for (int i = 0; i < commandLines.size(); i++)
        {
            bool flag = false;
            qDebug() << "Judging clean!";
            if (commandLines[i].action == "Merge")
            {
                qDebug() << "Merge case!";
                qDebug() << "commandLines[" << i << "].wholeLine: " << commandLines[i].wholeLine;
                QPoint p1 = commandLines[i].path[0];
                QPoint p2 = commandLines[i].path[1];
                QPoint p = (p1 + p2) / 2;
                for (int j = i + 1; j < commandLines.size(); j++)
                {
                    if (commandLines[j].action == "Move" && commandLines[j].beginTime == commandLines[i].endTime && commandLines[j].path[0] == p && (commandLines[j].path[1] == p1 || commandLines[j].path[1] == p2))
                    {
                        qDebug() << "Here!";
                        qDebug() << "commandLines[" << j << "].wholeLine: " << commandLines[j].wholeLine;
                        cannotCleanTime = cannotCleanTime < commandLines[j].beginTime ? cannotCleanTime : commandLines[j].beginTime;
                        qDebug() << "cannotCleanTime: " << cannotCleanTime;
                        flag = true;
                        break;
                    }
                    if (commandLines[j].action == "Mix" && commandLines[j].beginTime == commandLines[i].endTime && commandLines[j].path[0] == p && (commandLines[j].path[1] == p1 || commandLines[j].path[1] == p2))
                    {
                        qDebug() << "Here!";
                        qDebug() << "commandLines[" << j << "].wholeLine: " << commandLines[j].wholeLine;
                        cannotCleanTime = cannotCleanTime < commandLines[j].beginTime ? cannotCleanTime : commandLines[j].beginTime;
                        qDebug() << "cannotCleanTime: " << cannotCleanTime;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
        }
    }

    return cannotCleanTime;
}

int Operation::judge()
{
    qDebug() << "judge~judge~";
    int t = -1;
    if (!isClean)
    {
        qDebug() << wholeTime;

        //只要找到最新violate的就可以
        bool violate = false;
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
                        qDebug() << "Judging status[" << now << "].comb[" << i << "][" << j << "]";
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
                                qDebug() << "Here!";
                                violate = true;
                                break;
                            }
                        }

                        if (i == 1 && j == 1)
                        {
                            qDebug() << "i == 1 && j == 1";
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


    //    else
    //    {
    //        qDebug()<<wholeCleanTime;

    //        //只要找到最新violate的就可以
    //        bool violate = false;
    //        for (int now = 0; now <= wholeCleanTime; now++)
    //        {
    //            //qDebug()<<"Here now:"<<now;
    //            //qDebug()<<"colNum = "<<colNum;
    //            //qDebug()<<"rowNum = "<<rowNum;
    //            for (int i = 1; i <= colNum; i++)
    //            {
    //                //qDebug()<<"Here i: "<<i;
    //                for (int j = 1; j <= rowNum; j++)
    //                {
    //                    //qDebug()<<"Here j: "<<j;
    //                    //qDebug()<<"status["<<now<<"].comb["<<i<<"]["<<j<<"]";
    //                    if (!cleanStatus[now].comb[i][j].isEmpty)
    //                    {
    //                        qDebug()<<"Judging cleanStatus["<<now<<"].comb["<<i<<"]["<<j<<"]";
    //                        if (i < colNum && i > 1 && j < rowNum && j>1)
    //                        {
    //                            //qDebug()<<"i < colNum && i > 1 && j < rowNum && j>1";
    //                            if (!cleanStatus[now].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j + 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }

    //                        }

    //                        if (i == colNum && j > 0 && j < rowNum)
    //                        {
    //                            //qDebug()<<"i == colNum && j > 0 && j < rowNum";
    //                            if (!cleanStatus[now].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }
    //                        if (i == 1 && j > 0 && j < rowNum)
    //                        {
    //                           // qDebug()<<"i == 1 && j > 0 && j < rowNum";
    //                            if (!cleanStatus[now].comb[i][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j + 1].isEmpty)
    //                            {
    //                               // qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }



    //                        }

    //                        if (i < colNum && i > 1 && j == 1)
    //                        {
    //                            //qDebug()<<"i < colNum && i > 1 && j == 1";
    //                            if (!cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j + 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }

    //                        }

    //                        if (i < colNum && i > 1 && j == rowNum)
    //                        {
    //                            //qDebug()<<"i < colNum && i > 1 && j == rowNum";
    //                            if (!cleanStatus[now].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j - 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }

    //                        if (i == colNum && j == rowNum)
    //                        {
    //                            //qDebug()<<"i == colNum && j == rowNum";
    //                            if (!cleanStatus[now].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now + 1].comb[i - 1][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j - 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }

    //                        if (i == colNum && j == 1)
    //                        {
    //                            //qDebug()<<"i == colNum && j == 1";
    //                            if (!cleanStatus[now].comb[i - 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i - 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i][j + 1].isEmpty)
    //                            {
    //                                qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }

    //                        if (i == 1 && j == 1)
    //                        {
    //                            qDebug()<<"i == 1 && j == 1";
    //                            if (!cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j + 1].isEmpty
    //                                || !cleanStatus[now].comb[i][j + 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j + 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }

    //                        if (i == 1 && j == rowNum)
    //                        {
    //                            //qDebug()<<"i == 1 && j == rowNum";
    //                            if (!cleanStatus[now].comb[i + 1][j].isEmpty
    //                                || !cleanStatus[now].comb[i][j - 1].isEmpty
    //                                || !cleanStatus[now].comb[i + 1][j - 1].isEmpty
    //                                || !cleanStatus[now + 1].comb[i + 1][j - 1].isEmpty)
    //                            {
    //                                //qDebug()<<"Here!";
    //                                violate = true;
    //                                break;
    //                            }
    //                        }
    //                    }
    //                    if (violate)
    //                    {
    //                        t = now;
    //                        qDebug() << "cleanStatus[" << now << "].comb[" << i << "][" << j << "] is Violating!";
    //                        return t;
    //                    }
    //                }
    //            }
    //        }
    //    }


}


void Operation::changeIsSafe()
{
    for (int now = 0; now <= wholeTime; now++)
    {
        for (int i = 1; i <= colNum; i++)
        {
            for (int j = 1; j <= rowNum; j++)
            {
                if (!status[now].comb[i][j].isEmpty)
                {
                    status[now].comb[i][j].isSafe = false;
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
                            status[now].comb[i][j].isSafe = false;
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
                            status[now].comb[i][j].isSafe = false;
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
                            status[now].comb[i][j].isSafe = false;
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
                            status[now].comb[i][j].isSafe = false;
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
                            status[now].comb[i][j].isSafe = false;
                        }
                    }

                    if (i == colNum && j == rowNum)
                    {
                        //qDebug()<<"i == colNum && j == rowNum";
                        if (!status[now].comb[i - 1][j - 1].isEmpty
                            || !status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe = false;
                        }
                    }

                    if (i == colNum && j == 1)
                    {
                        //qDebug()<<"i == colNum && j == 1";
                        if (!status[now].comb[i - 1][j].isEmpty
                            || !status[now].comb[i - 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe = false;
                        }
                    }

                    if (i == 1 && j == 1)
                    {
                        //qDebug()<<"i == 1 && j == 1";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i + 1][j + 1].isEmpty
                            || !status[now].comb[i][j + 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe = false;
                        }
                    }

                    if (i == 1 && j == rowNum)
                    {
                        //qDebug()<<"i == 1 && j == rowNum";
                        if (!status[now].comb[i + 1][j].isEmpty
                            || !status[now].comb[i][j - 1].isEmpty
                            || !status[now].comb[i + 1][j - 1].isEmpty)
                        {
                            status[now].comb[i][j].isSafe = false;
                        }
                    }
                }
            }
        }

    }


    //        for(int now = 0;now<=wholeTime;now++)
    //        {

    //         for (int i = 1; i <= colNum; i++)
    //        {
    //            for (int j = 1; j <= rowNum; j++)
    //            {
    //                qDebug() << "status[" << now << "].comb[" << i << "][" << j << "].isSafe" << status[now].comb[i][j].isSafe;
    //           }
    //        }

    //        }
}



//针对每一个最早的污染点来洗，使用index来取得值即可，如果不需要清洗也就不用调用对应index的函数
//其实应该是这里来判断是不是可以洗
int Operation::startCleanTime(Polluted &pol)
{

    int start = -1;
    for (int t = pol.time - 1; t > pol.iniPol; t--)
    {
        //清洗点是安全的，并且要保证出口和入口也是安全的，这样才能洗
        if (status[t].comb[pol.p.x()][pol.p.y()].isSafe && status[t].comb[1][1].isSafe)
        {
            qDebug() << "Now is safe!";
            start = t;

            break;
        }
    }

    qDebug() << "clean startTime: " << start;

    pol.cleanTime = start;

    qDebug() << "pol.cleanTime: " << pol.cleanTime;

    if (start == -1)
    {
        cannotCleanTime = pol.time;
    }
    return start;
}


void Operation::out(int i, int j)
{
    if (i == j)
    {
        //qDebug("%d->", i);
        return;
    }
    int k;
    k = path[i][j];
    if (k == i)
    {
        return;
    }
    //qDebug() << "path[" << i << "][" << j << "]: " << path[i][j];
    if (k == -1)
    {
        qDebug() << i << " and " << j << " can't be connected!";
        return;
    }
    out(i, k);
    road.push_back(k);
    qDebug("%d->", k);
}

