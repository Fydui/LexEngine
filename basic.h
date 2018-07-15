#ifndef BASIC_H
#define BASIC_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
#include <windows.h>
#include <QEvent>
#include <QByteArray>
#include "item.h"
enum type{Fix, Android, Flow};

//这个类是比较底层的一些基本管理 他们会在程序运行的时候首先运行 你可以在Basic类中自定义自己的需求
class Basic : public QWidget
{
    Q_OBJECT
    
public:
    Basic(QWidget *parent = 0);
    Basic(type t , QWidget *parent = 0);
    ~Basic();
    void getWindowSize();   //获得窗口大小
    void setWindowSize(int w, int h);//设置窗口大小
    void setFixed(type s = type::Fix); //在Windows固定窗口大小与Android全屏自适应之间切换 默认固定
    void addScene(Scene &s);
    void addItem(Item &i);
    void removeItem(Item &i);
    void resizeEvent(QResizeEvent * event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*event);
    void changeEvent(QEvent* event);
    int judgeWidthRatio();  //判断当前窗口宽是否符合比例
    int judgeHeightRatio(); //判断当前窗口高是否符合比例
    //bool event(QEvent *event);
    
    QString titleName = "新项目";             //窗口标题的名字
    int defaultWindowHeight = 720;        //窗口的大小
    int defaultWindowWidth = 1280;   
    int screenWindowHeight;          //可用桌面的大小
    int screenWindowWidth;
    double deskWidth;                   //单块屏幕总大小
    double deskHeight;
    double screenHeightDifference;      //总大小与可用大小的差值
    double screenWidthDifference;  
    double widthZoomVar=1;              //默认长宽与当前长宽的比值 用于缩放图元
    double heightZoomVar=1;
    double zoomVar=1;
    double WindowRatioH = 1;        //窗口宽高比
    double WindowRatioW = 1;
    
    QString prePath = ""; //安卓下的预路径 请在sdcard下自建MengDieOBJ梦蝶工程文件夹 将包放在该目录下
    
private:
    HWND getWindowHWND();
    type nt;    //当前模式
    View  view;
    Scene  scene;
};

#endif // BASIC_H
