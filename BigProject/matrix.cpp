#include "matrix.h"


Matrix::Matrix()
{
    isValid = false;
    isEmpty = true;

}

void Matrix::insertPollutedSet(QString kind)
{
    pollutedSet<<kind;
    qDebug()<<"kind = "<<kind;
}

