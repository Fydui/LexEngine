#include "item.h"

Item::Item(QString path)
{
    bool t = pix.load(path); //加载图片    
    //this->setPos(-(1080/2-pix.width()/2),-(720/2-pix.height()/2));
    //因为QGraphicsScene的原点为窗口中心, 为了习惯手动设置锚点到左上角(至少看上去是      
}

Item::~Item()
{
    pix = QPixmap();
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(),pix);         
    
}

QRectF Item::boundingRect() const
{
    qreal penwidth = 0;
    return QRectF(-pix.width()/2+penwidth,-pix.height()/2+penwidth,
                  pix.width()+penwidth*2,pix.height()+penwidth*2);  //绘制范围
}



