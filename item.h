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
public:
    Item(){}
    Item(QString path, qreal x = 0, qreal y = 0);
    //void setScale(qreal a, AnchorPoint ap = Center);   
    ~Item();
    qreal px;
    qreal py;
    
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;
    QPixmap pix;
    
};

#endif // ITEM_H
