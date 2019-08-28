#ifndef MATRIXCOMB_H
#define MATRIXCOMB_H
#include"matrix.h"


class matrixComb
{
public:
    matrixComb();

    Matrix comb[13][13];

    void setValidMatrix(int col, int row);
};

#endif // MATRIXCOMB_H
