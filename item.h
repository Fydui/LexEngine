#ifndef ITEM_H
#define ITEM_H
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsSceneEvent>
#include <QMetaObject>
#include <QColor>
enum AnchorPoint{UpperLeftCorner,UpperRightCorner,BottomRightCorner,BottomLeftCorner,Center};
class View  :public QGraphicsView
{
    Q_OBJECT
public:
    View(){}
    ~View(){}
    void wheelEvent(QWheelEvent *event){}
    
};



class Item : public QObject,public QGraphicsItem
{
    Q_OBJECT    
    struct PointValue{
      QPointF point;
      AnchorPoint anchor;
      qreal value;
    };
public:
    Item();
    ~Item();
    Item(QString path, qreal x=0 , qreal y=0 , QString f="");
    
    Item(const Item& i);            //拷贝构造函数
    Item& operator=(const Item i);
    
    void setItemScale(qreal x, AnchorPoint ap = UpperLeftCorner);       //按照某锚点缩放图元
    void setItemRotation(qreal f,AnchorPoint ap = Center);              //按照某锚点旋转图元
    void moveItem(qreal x, qreal y, AnchorPoint ap = UpperLeftCorner);  //按照某锚点移动图元
    PointValue getItemValue() const;         //获取Item的坐标
    PointValue getScaleValue() const;        //获取缩放参数
    PointValue getRotationValue() const;     //获取旋转参数
    QPointF getCornerPoint(AnchorPoint ap);  //给定ap获得相对于item的坐标
    signals:
       void ItemClickedPress();
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);  //绘制函数
    QRectF boundingRect() const; //绘制范围
    QPointF getAnchorValue(AnchorPoint ap = UpperLeftCorner);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    QPixmap pix;
    QString pixPath;
    QString fun;
    PointValue itemValue;        //图元坐标
    PointValue scaleValue;       //缩放参数
    PointValue rotationValue;    //旋转参数
    
};
class Scene :public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(){}
    ~Scene(){}
    void keyPressEvent(QKeyEvent* event){}
    
};

#endif // ITEM_H
