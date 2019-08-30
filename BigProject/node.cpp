#include "node.h"

Node::Node(int i,int j,int a,int b)
{
    p = QPoint(i,j);
    next = new QPoint [4];
    for(int i=0;i<4;i++)
    {
       next[i]= QPoint(0,0);
    }
    dist = qAbs(a+b-i-j);
    qDebug()<<"In Node i= "<<i<<" j = "<<j<<" dist = "<<dist;
}

void Node::nextPoint(QPoint p,int i)
{
    next[i]=p;
}
