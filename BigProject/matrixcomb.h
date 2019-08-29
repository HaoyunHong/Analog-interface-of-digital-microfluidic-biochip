#ifndef MATRIXCOMB_H
#define MATRIXCOMB_H
#include"matrix.h"


class matrixComb
{
public:
    matrixComb();

    Matrix comb[13][13];
    bool isDecided;

    bool isMm;
    bool isStr;
    bool isAp;
    bool isMer;

};

#endif // MATRIXCOMB_H
