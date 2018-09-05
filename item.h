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
    struct PointValue{
      QPointF point;
      AnchorPoint anchor;
      qreal value;
    };
    
public:
    Item(){}
    ~Item();    
    Item(QString path, qreal x = 0, qreal y = 0, qreal k = 1,
         AnchorPoint scalePoint = UpperLeftCorner, qreal rotation = 0,
         AnchorPoint rotationPoint = Center);
    
    void setItemScale(qreal x, AnchorPoint ap = UpperLeftCorner);       //按照某锚点缩放图元
    void setItemRotation(qreal f,AnchorPoint ap = Center);              //按照某锚点旋转图元
    void moveItem(qreal x, qreal y, AnchorPoint ap = UpperLeftCorner);  //按照某锚点移动图元
    PointValue getItemValue() const;         //获取Item的坐标
    PointValue getScaleValue() const;        //获取缩放参数
    PointValue getRotationValue() const;     //获取旋转参数
    QPointF getCornerPoint(AnchorPoint ap);  //给定ap获得相对于item的坐标
    
    
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);  //绘制函数
    QRectF boundingRect() const; //绘制范围
    QPointF getAnchorValue(AnchorPoint ap = UpperLeftCorner);
    QPixmap pix;
    PointValue itemValue;        //图元坐标
    PointValue scaleValue;       //缩放参数
    PointValue rotationValue;    //旋转参数
    
};

#endif // ITEM_H
