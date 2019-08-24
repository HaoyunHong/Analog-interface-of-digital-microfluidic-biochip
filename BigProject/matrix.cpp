#include "matrix.h"


Matrix::Matrix()
{

}

void Matrix::insertPollutedSet(QString kind)
{
    pollutedSet<<kind;
    qDebug()<<"kind = "<<kind;
}

