#include "designinterface.h"
#include "ui_designinterface.h"

DesignInterface::DesignInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignInterface)
{
    ui->setupUi(this);

    this->resize(1200,900);

    this->setWindowTitle("Design Interface");

//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/image/purback.jpg")));
//    this->setPalette(palette);
//    setAcceptDrops(true);

}

void DesignInterface::paintEvent(QPaintEvent *)
{
    QPainter p;//创建画家对象
    p.begin(this);//指定当前窗口为绘图设备

    //绘图操作
    //p.drawxxx();//各种函数
    //画背景图
    //自动获取窗口的宽度和高度
    p.drawPixmap(0,0,width(),height(),QPixmap(":/image/image/purback.jpg"));
    //设置不透明度
    setWindowOpacity(0.96);

    //定义画笔
    QPen pen;
    pen.setWidth(5);//设置线宽
    //pen.setColor(Qt::red);//设置颜色
    //pen.setColor(QColor(244,96,108));//设置RGB颜色
    pen.setColor(QColor(220,159,180));
    pen.setStyle(Qt::SolidLine);

    //把画笔交给画家
    p.setPen(pen);

//    //画直线
//    p.drawLine(50,50,150,50);
//    p.drawLine(50,50,50,150);

    //创建画刷对象
    QBrush brush;
    brush.setColor(QColor(248,195,205));//设置颜色
    brush.setStyle(Qt::SolidPattern);//设置样式

    //把画刷交给画家
    p.setBrush(brush);

    int x = width()/2-60;
    int y = height()-60;
    //画矩形
    p.drawRect(30,30,x,y);

//    //画圆
//    p.drawEllipse(QPoint(150,150),50,25);

//    //画笑脸
//    p.drawPixmap(x,180,80,80,QPixmap("C:/Users/Jacqueline/Desktop/QT/PaintEvent/face.jpg"));

    p.end();
}

DesignInterface::~DesignInterface()
{
    delete ui;
}
