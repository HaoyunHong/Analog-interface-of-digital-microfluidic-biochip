#ifndef DESIGNINTERFACE_H
#define DESIGNINTERFACE_H

#include <QWidget>
#include<QPainter>
#include<QPaintEvent>

namespace Ui {
class DesignInterface;
}

class DesignInterface : public QWidget
{
    Q_OBJECT

public:
    explicit DesignInterface(QWidget *parent = nullptr);
    ~DesignInterface();

    void paintEvent(QPaintEvent *);


private:
    Ui::DesignInterface *ui;


};

#endif // DESIGNINTERFACE_H
