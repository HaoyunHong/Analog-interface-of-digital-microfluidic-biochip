#include "matrix.h"


Matrix::Matrix()
{
    position.setX(0);
    position.setY(0);
}

void Matrix::setPosition(int colIndex, int rowIndex)
{
    position.setX(colIndex);
    position.setY(rowIndex);
}
