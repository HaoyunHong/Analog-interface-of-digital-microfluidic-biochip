#include "data.h"

Data::Data()
{

}

void Data::setNumber(int row,int col)
{
    rowNumber = row;
    colNumber = col;
    qDebug()<<"row = "<<row;
    qDebug()<<"col = "<<col;
}

