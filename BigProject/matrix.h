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

    //void setRGBA(int r, int g,int b,int a);

    //void getRGBA();

    void insertPollutedSet(QString kind);

    bool isValid;

    bool isEmpty;

    bool isLongDrop;

    bool hasTrace;

    bool isBigger;

    bool isSmaller;

    int lastStepKind;

    int nextStepKind;

    //颜色信息
    QColor dropColor;




private:
    //污染信息
    QSet<QString> pollutedSet;
};

#endif // MATRIX_H
