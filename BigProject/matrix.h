#ifndef MATRIX_H
#define MATRIX_H
#include<QPoint>
#include<QSet>

class Matrix
{
public:
    Matrix();
    void setPosition(int colIndex, int rowIndex);

    //void setRGBA(int r, int g,int b,int a);

    //void getRGBA();

    //void insertPollutedSet(QString kind);


private:
    //自己的位置信息
    QPoint position;
    //颜色信息
    int red;
    int green;
    int blue;
    int alpha;
    //污染信息
    QSet<QString> pollutedSet;
};

#endif // MATRIX_H
