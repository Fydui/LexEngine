#ifndef ITEM_H
#define ITEM_H
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QKeyEvent>

enum AnchorPoint{UpperLeftCorner,UpperRightCorner,BottomRightCorner,BottomLeftCorner,Center};
class View : public QGraphicsView
{
public:
    View(){}
    
    void wheelEvent(QWheelEvent *event){}
    
};

class Scene : public QGraphicsScene
{
public:
    Scene(){}
    ~Scene(){}
    void keyPressEvent(QKeyEvent* event){}
    
};




class Item : public QGraphicsItem
{
    struct ScaleValue{qreal scaleValue;
                      AnchorPoint anchorPointType; };
public:
    Item(){}
    Item(QString path, qreal x = 0, qreal y = 0, qreal k = 1, AnchorPoint ap = AnchorPoint::UpperLeftCorner);
    void setScale(qreal x, AnchorPoint ap = UpperLeftCorner); //按照某锚点缩放图元
    void moveItem(qreal x, qreal y);
    QPointF getItemPoint();
    ScaleValue getScaleValue();  
    ~Item();

    
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;
    QPixmap pix;
    QPointF itemPoint;
    ScaleValue scaleValue;
    //qreal px = 0; //横坐标
    //qreal py = 0; //纵坐标
    //qreal scaleValue = 1;  //缩放倍数
    //AnchorPoint anchorPointType = AnchorPoint::UpperLeftCorner; //缩放锚点当前模式
    
};

#endif // ITEM_H
