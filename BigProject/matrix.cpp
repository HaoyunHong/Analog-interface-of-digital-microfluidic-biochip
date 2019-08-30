#include "matrix.h"
#include <QColor>


Matrix::Matrix()
{
    isEmpty = true;
    isLongDrop = false;
    isFat = false;

    //Merge时
    isBigger = false;
    //Split时
    isSmaller = false;
    isBlock = false;
    isSafe = true;
    hasWashing = false;

}

void Matrix::setDefault()
{
    isEmpty = true;
    isLongDrop = false;
    isFat = false;


    //Merge时
    isBigger = false;
    //Split时
    isSmaller = false;
}
