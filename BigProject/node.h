#ifndef NODE_H
#define NODE_H
#include<QPoint>
#include<QDebug>
class Node
{
public:
    Node(int,int,int,int);
    QPoint p;
    QPoint *next;
    //距离污染点的步数
    int dist;

    void nextPoint(QPoint,int);
};

#endif // NODE_H
