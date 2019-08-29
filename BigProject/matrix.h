#ifndef MATRIX_H
#define MATRIX_H
#include<QPoint>
#include<QSet>
#include<QDebug>
#include<QColor>

class Matrix
{
public:
    Matrix();

    QVector<QColor> pollutedSet;

    bool isEmpty;

    bool isLongDrop;

    bool isFat;

    bool hasTrace;

    bool isBigger;

    bool isSmaller;

    int lastStepKind;

    int nextStepKind;

    //颜色信息
    QColor dropColor;

    void setDefault();

    bool isBlock;


};

#endif // MATRIX_H
