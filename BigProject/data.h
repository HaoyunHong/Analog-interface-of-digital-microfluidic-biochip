#ifndef DATA_H
#define DATA_H
#include<QPoint>
#include<QDebug>


class Data
{
public:
    Data();

    //设置行列数
    void setNumber(int,int);


private:

    //行数
    int rowNumber;
    //列数
    int colNumber;

};

#endif // DATA_H
