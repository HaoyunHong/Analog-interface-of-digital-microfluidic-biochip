#include "matrixcomb.h"

matrixComb::matrixComb()
{


}

void matrixComb::setValidMatrix(int col, int row)
{
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            comb[i][j].isValid = true;
        }
    }
}
