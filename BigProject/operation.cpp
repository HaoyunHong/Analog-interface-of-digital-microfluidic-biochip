#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
      time = 0;
      countKind = 0;

      canShowCommand = true;

      isLimited = false;
      isClean = false;
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

        if(!isClean)
        {

        }
    }
    myFile->close();
}

//这里设置的时候坐标就要反过来
void Operation::setRC(int row, int col)
{
      for(int i=0;i<col;i++)
      {
          for(int j=0;j<row;j++)
          {
              //matrixComb[i][j].isValid
          }
      }
}


