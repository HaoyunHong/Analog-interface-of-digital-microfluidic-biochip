#ifndef OPERATIONSIGNAL_H
#define OPERATIONSIGNAL_H

#include <QObject>

#include "matrix.h"
#include<QFile>
#include<QDebug>
#include<vector>

class OperationSignal : public QObject
{
    Q_OBJECT
public:
    explicit OperationSignal(QObject *parent = nullptr,int row = 0, int col = 0);
    void setFile(QString path);
    void setEveryInput(QPoint pIn);
    void setTheOut(QPoint pOut);

    void parseFile();

signals:

public slots:

private:
    Matrix ** matrix;
    QFile *myFile;
    std::vector<QPoint> inputPoints;
    QPoint outputPoint;
};

#endif // OPERATIONSIGNAL_H
