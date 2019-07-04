#include "item.h"
#include "game.h"
extern game* g;
Item::Item(QString path, qreal x, qreal y, QString f)
{   
   
    itemValue.point.setX(x);
    itemValue.point.setY(y);
    setItemScale(1,AnchorPoint::UpperLeftCorner);
    setItemRotation(0,AnchorPoint::Center);
    pixPath = path;
    fun = f;

    
    //connect(this,SIGNAL(ItemClickedPress()),g,SLOT());
    //QMetaObject::invokeMethod(g,ch, Qt::DirectConnection);
    
    pix.load(path); //加载图片  
}

Item::Item(const Item &i)
{
    itemValue.point.setX(i.itemValue.point.x());
    itemValue.point.setY(i.itemValue.point.y());
    setItemScale(i.scaleValue.value,i.scaleValue.anchor);
    setItemRotation(i.rotationValue.value,i.rotationValue.anchor);
    pixPath = i.pixPath;
    pix.load(i.pixPath); //加载图片
}

Item &Item::operator=(const Item i)
{   
    itemValue.point.setX(i.itemValue.point.x());
    itemValue.point.setY(i.itemValue.point.y());
    setItemScale(i.scaleValue.value,i.scaleValue.anchor);
    setItemRotation(i.rotationValue.value,i.rotationValue.anchor);
    pixPath = i.pixPath;    
    pix.load(i.pixPath); //加载图片  
    return *this;
}

Item::~Item(){
    
    pix = QPixmap();
}

void Item::setItemScale(qreal x, AnchorPoint ap)
{        
    QGraphicsItem::setScale(x);                 //放大图元
    scaleValue.value = x;
    scaleValue.anchor = ap;
    getAnchorValue(ap);
    
}

void Item::setItemRotation(qreal f, AnchorPoint ap)
{   
    rotationValue.point = getCornerPoint(ap);
    setTransformOriginPoint(rotationValue.point);   
    setRotation(f);
    rotationValue.value = f;
    rotationValue.anchor = ap;
}

void Item::moveItem(qreal x, qreal y, AnchorPoint ap){
    QPointF temp = getAnchorValue(ap);
    itemValue.anchor =ap;    
    
    moveBy(x + temp.x(),y + temp.y());
}

Item:: PointValue Item::getItemValue() const {
    return itemValue;
}

Item::PointValue  Item::getScaleValue() const{
    return scaleValue;
}

Item::PointValue Item::getRotationValue() const{
    return rotationValue;
}

QPointF Item::getCornerPoint(AnchorPoint ap)
{    
    if(ap == AnchorPoint::UpperLeftCorner) 
        return QPointF(0,0); 
    else if(ap == AnchorPoint::UpperRightCorner){
        return QPointF(pix.width(),0);
    }
    else if(ap == AnchorPoint::BottomRightCorner){
        return QPointF(pix.width(),pix.height());
    }
    else if(ap == AnchorPoint::BottomLeftCorner){
        return QPointF(0,pix.height());
    }
    else if(ap == AnchorPoint::Center){
        return QPointF(pix.width()/2,pix.height()/2);
    }
}

QPointF Item::getAnchorValue(AnchorPoint ap)
{
    QRectF F = mapRectToScene(boundingRect());  //计算放大之后的矩形
    
    if(ap == AnchorPoint::UpperLeftCorner) 
        return QPointF(itemValue.point); 
    else if(ap == AnchorPoint::UpperRightCorner){
        itemValue.point.rx() += F.width() - pix.width();
    }
    else if(ap == AnchorPoint::BottomRightCorner){
        itemValue.point.rx() += -F.width() - pix.width();
        itemValue.point.ry() += -F.height() - pix.height();
    }
    else if(ap == AnchorPoint::BottomLeftCorner){
        itemValue.point.ry() += -F.height() - pix.height();
    }
    else if(ap == AnchorPoint::Center){
        itemValue.point.rx() += -(F.width() - pix.width()/2);
        itemValue.point.ry() += -(F.height() - pix.height()/2);
    }
    
    return QPointF(itemValue.point);
    
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->buttonDownPos(Qt::LeftButton); //获取鼠标在Item中的落点
    QRgb rgb = pix.toImage().pixel(pos.toPoint());      //获得当前坐标的像素的rgb
    
    /*QList<QGraphicsItem*> iList;
    if(rgb ==0){
        iList = scene()->items(pos);
        for (auto temp : iList) {
            
            QRgb newrgb = i.pix.toImage().pixel(pos.toPoint());
            if(newrgb != 0){
                i.mousePressEvent(event);
                return;
            }
        }
    }
    int a = 0;*/
    //QObject::connect(this,SIGNAL(pressEvent),g,fun);
    qDebug() << pixPath<<" "<< QString::number(rgb,16) << " " << " 按下\n";
    const char* ch;
    QByteArray ba = fun.toLatin1();
    ch = ba.data();
    QMetaObject::invokeMethod(g,ch, Qt::DirectConnection);
    
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    
    //qDebug() <<pixPath<< "抬起\n";
}


void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   
    painter->drawPixmap(boundingRect().toRect(),pix);  //(QRect(0,0,pix.width(),pix.height())
    
}

QRectF Item::boundingRect() const
{
    //qreal penwidth = 0;   
    //return QRectF(-pix.width()/2,-pix.height()/2,pix.width(),pix.height());  //绘制范围
    return QRectF(0,0,pix.width(),pix.height());
}





