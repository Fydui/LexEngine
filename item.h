#ifndef ITEM_H
#define ITEM_H
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

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
    
};




class Item : public QGraphicsItem
{
public:
    Item(){}
    Item(QString path);
    ~Item();
    
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;
    QPixmap pix;
    
};

#endif // ITEM_H
