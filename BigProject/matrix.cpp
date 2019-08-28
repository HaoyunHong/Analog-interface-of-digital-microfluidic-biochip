#include "matrix.h"
#include <QColor>


Matrix::Matrix()
{
    isValid = false;
    isEmpty = true;
    isLongDrop = false;
    isFat = false;

    //如果有trace的话，是找之前的路径然后画出很多小圆
    hasTrace = true;

    //Merge时
    isBigger = false;
    //Split时
    isSmaller = false;

    d=30;

}

void Matrix::insertPollutedSet(QString kind)
{
    pollutedSet<<kind;
    qDebug()<<"kind = "<<kind;
}

