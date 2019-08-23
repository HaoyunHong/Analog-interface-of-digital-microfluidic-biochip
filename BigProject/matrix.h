#ifndef MATRIX_H
#define MATRIX_H
#include<QPoint>
#include<QSet>

class Matrix
{
public:
    Matrix();
    Matrix(int,int);

private:
    //自己的位置信息
    QPoint position;
    //颜色信息
    int red;
    int green;
    int blue;
    int alpha;
    //污染次数信息
    int count;
    QSet<int> pollutedSet;





};

#endif // MATRIX_H
