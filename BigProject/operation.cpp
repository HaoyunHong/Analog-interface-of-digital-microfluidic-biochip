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
    qDebug()<<"inputPoints.size() = "<<inputPoints.size();
    qDebug()<<parts;
    if(parts[0]=="Input")
    {
        time=parts[1].toInt();
        int colIndex = parts[2].toInt();
        qDebug()<<parts[3];
        int rowIndex = parts[3].toInt();
        qDebug()<<"colIndex = "<<colIndex<<" inputPoints["<<0<<"].x() = "<<inputPoints[0].x();
        qDebug()<<"rowIndex = "<<rowIndex<<" inputPoints["<<0<<"].y() = "<<inputPoints[0].y();

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
        qDebug()<<"equal = "<<equal;
        if(equal)
        {
            countKind++;
            QString kind = QString("%1").arg(countKind);
            qDebug()<<"kind = "<<kind;
            matrix[colIndex-1][rowIndex-1].insertPollutedSet(kind);
            qDebug()<<"kind = "<<kind;
        }
        else {
            canShowCommand = false;
            //emit cannotShowCommand();
        }
//        if(parts[0]=="Output")
//        {
//            time=parts[1].toInt();
//            int colIndex = parts[2].toInt();
//            int rowIndex = parts[3].toInt();

//            bool equal=false;
//            if(colIndex == outputPoint.x() && rowIndex == outputPoint.y())
//            {
//                equal = true;
//            }
//            if(equal)
//            {
//                //matrix[colIndex][rowIndex].insertPollutedSet(kind);
//                timer.push_back(time);
//                status.push_back(matrix);
//            }
//            else {
//                emit cannotShowCommand();
//            }
//        }

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


