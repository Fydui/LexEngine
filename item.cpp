#include "item.h"
Item::Item(QString path, qreal x, qreal y, qreal k, AnchorPoint ap):
    itemPoint(x,y),scaleValue{k,ap}
{
    qDebug() << getItemPoint().x() << getItemPoint().y()<< getScaleValue().scaleValue;
    
    pix.load(path); //加载图片
    //qDebug() << itemPoint.x() << itemPoint.y()<< scaleValue.scaleValue;
    //this->setPos(-(1080/2-pix.width()/2),-(720/2-pix.height()/2));
    //因为QGraphicsScene的原点为窗口中心, 为了习惯手动设置锚点到左上角(至少看上去是    
}

void Item::setScale(qreal x, AnchorPoint ap)
{        
    QGraphicsItem::setScale(x);                 //放大图元
    QRectF F = mapRectToScene(boundingRect());  //计算放大之后的矩形
        
    if(ap == AnchorPoint::UpperLeftCorner) return; //设置缩放锚点 四角和中心
    else if(ap == AnchorPoint::UpperRightCorner){
        itemPoint.rx() = itemPoint.rx() + F.width() - pix.width();
    }
    else if(ap == AnchorPoint::BottomRightCorner){
        itemPoint.rx() = itemPoint.rx() - F.width() - pix.width();
        itemPoint.ry() = itemPoint.ry() - F.height() - pix.height();
    }
    else if(ap == AnchorPoint::BottomLeftCorner){
        itemPoint.ry() = itemPoint.ry() - F.height() - pix.height();
    }
    else if(ap == AnchorPoint::Center){
        itemPoint.rx() = itemPoint.rx() - (F.width() - pix.width()/2);
        itemPoint.ry() = itemPoint.ry() - (F.height() - pix.height()/2);
    }

    
}

void Item::moveItem(qreal x, qreal y){
    moveBy(x,y);
}

QPointF Item::getItemPoint() {
    return itemPoint;
}

Item::ScaleValue  Item::getScaleValue(){
    return scaleValue;
}

Item::~Item(){
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



