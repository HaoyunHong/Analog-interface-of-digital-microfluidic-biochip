#ifndef MATRIX_H
#define MATRIX_H
#include<QPoint>
#include<QSet>
#include<QDebug>

class Matrix
{
public:
    Matrix();

    //void setRGBA(int r, int g,int b,int a);

    //void getRGBA();

    void insertPollutedSet(QString kind);


private:
    //颜色信息
    int red;
    int green;
    int blue;
    int alpha;
    //污染信息
    QSet<QString> pollutedSet;
};

#endif // MATRIX_H
