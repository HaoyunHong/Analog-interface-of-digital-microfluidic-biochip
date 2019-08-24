#include "operation.h"

Operation::Operation(QObject *parent) : QObject(parent)
{
      time = 0;
      countKind = 0;

      canShowCommand = true;
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
        QString line(array);
        line = line.replace(" ", ",");
        line = line.replace(";", ",");
        this->parseLine(line);
    }
    if(!canShowCommand)
    {
        emit cannotShowCommand();
    }
    myFile->close();
}

void Operation::parseLine(QString line)
{
    qDebug()<<"line = "<<line;
    QStringList parts = line.split(",");
    qDebug()<<parts;
    if(parts[0]=="Input")
    {
        time=parts[1].toInt();
        int colIndex = parts[2].toInt();
        qDebug()<<parts[3];
        int rowIndex = parts[3].toInt();

        bool equal=false;
        for(unsigned int i=0;i<inputPoints.size();i++)
        {
            if(colIndex == inputPoints[i].x() && rowIndex == inputPoints[i].y())
            {
                qDebug()<<"colIndex = "<<colIndex<<" inputPoints["<<i<<"].x() = "<<inputPoints[i].x();
                qDebug()<<"rowIndex = "<<rowIndex<<" inputPoints["<<i<<"].y() = "<<inputPoints[i].y();
                equal = true;
                break;
            }
        }
        if(equal)
        {
            emit drawInput(colIndex,rowIndex);
            countKind++;
            QString kind = QString("%1").arg(countKind);
            matrix[colIndex-1][rowIndex-1].insertPollutedSet(kind);
            qDebug()<<"kind = "<<kind;
        }
        else {
            canShowCommand = false;
        }
    }

    if(parts[0]=="Output")
    {
        time=parts[1].toInt();
        int colIndex = parts[2].toInt();
        int rowIndex = parts[3].toInt();

        bool equal=false;
        qDebug()<<"colIndex = "<<colIndex<<" outputPoint.x() = "<<outputPoint.x();
        qDebug()<<"rowIndex = "<<rowIndex<<" outputPoint.y() = "<<outputPoint.y();
        if(colIndex == outputPoint.x() && rowIndex == outputPoint.y())
        {
            equal = true;
        }
        if(equal)
        {
            timer.push_back(time);
            status.push_back(matrix);
        }
        else {
            canShowCommand = false;
        }
    }
}

//这里设置的时候坐标就要反过来
void Operation::setRC(int row, int col)
{
    matrix = new Matrix* [col];
      for(int i=0;i<col;i++)
      {
          matrix[i] = new Matrix [row];
      }
}


