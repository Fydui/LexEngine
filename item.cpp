#include "item.h"
Item::Item(QString path, qreal x, qreal y)
{
    pix.load(path); //加载图片
    px =  x;
    py = y;
    
    //this->setPos(-(1080/2-pix.width()/2),-(720/2-pix.height()/2));
    //因为QGraphicsScene的原点为窗口中心, 为了习惯手动设置锚点到左上角(至少看上去是    
}

Item::~Item()
{
    pix = QPixmap();
}


void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   
    painter->drawPixmap(boundingRect().toRect(),pix);  //(QRect(0,0,pix.width(),pix.height())
    //update(-pix.width()/2+px,-pix.height()/2+py,pix.width()*2,pix.height()*2); 
}

QRectF Item::boundingRect() const
{
    //qreal penwidth = 0;
    
    //return QRectF(-pix.width()/2,-pix.height()/2,pix.width(),pix.height());  //绘制范围
    return QRectF(0,0,pix.width(),pix.height());
}



