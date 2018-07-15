#include "basic.h"


int W = 0, H = 0;

Basic::Basic( QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(titleName);
    setBaseSize(deskWidth,deskHeight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //关闭横竖滚动栏
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   
}

Basic::Basic(type t, QWidget *parent)
    : Basic(parent)
{    
    setFixed(t);
    view.setParent(this);
    //scene.addPixmap(QPixmap("C:/My/code/MyObj/MengDie_Widget/resources/image/Lexington_Strap_bikini.png"));
    //scene.addText("Hello");
    scene.setParent(this);
    view.resize(deskWidth,deskHeight );          //设置视图范围      
    view.setScene(&scene);
    //setWindowFlags(Qt::FramelessWindowHint);
    //setWindowFlag(Qt::WindowTitleHint);
    
    nt = t;
    
}



Basic::~Basic()
{
}

void Basic::getWindowSize()
{
    QDesktopWidget desktopWidget;
    QRect deskRect = desktopWidget.availableGeometry(); //获得可用窗口大小(去除通知栏/任务栏的大小)
    QRect screenRect = desktopWidget.screenGeometry();  //获得当前桌面的大小(整块屏幕总大小)
    
    screenWindowHeight = deskRect.height();             
    screenWindowWidth = deskRect.width(); 
    
    deskHeight = screenRect.height();
    deskWidth = screenRect.width();
    
    screenHeightDifference = screenRect.height() - screenWindowHeight;
    screenWidthDifference = screenRect.width() - screenWindowWidth;
    
}

void Basic::setWindowSize(int w, int h)
{
    screenWindowHeight = h;            
    screenWindowWidth = w; 
    
    deskHeight = h;
    deskWidth = w;
    
    screenHeightDifference = 0;
    screenWidthDifference = 0;
    
}

void Basic::setFixed(type s)
{
    if(s == Android){
        deskWidth = screenWindowWidth;
        deskHeight = screenWindowHeight;
    }
    else if(s == Fix){
        deskHeight = defaultWindowHeight;
        deskWidth = defaultWindowWidth;
        setFixedSize(deskWidth,deskHeight);        //固定窗口大小
    }
    else{
        deskHeight = defaultWindowHeight;
        deskWidth = defaultWindowWidth;
        setMinimumHeight(deskHeight);
        setMinimumWidth(deskWidth);
        
        //获取窗口长宽比例:
        int temp = 1;
        int x = (deskHeight > deskWidth) ? deskHeight : deskWidth;
        int y = (deskHeight < deskWidth) ? deskHeight : deskWidth;
        while(x % y != 0){ //辗转相除 获取最大公因数
            temp = x%y;
            x = y;
            y = temp;
        }
        WindowRatioH = deskHeight/temp; //获得约分比例
        WindowRatioW = deskWidth/temp;
        
    }
}

void Basic::addScene(Scene &s)
{
    view.setScene(&s);
}
void Basic::addItem(Item &i)
{
    scene.addItem(&i);
}
void Basic::removeItem(Item &i)
{
    scene.removeItem(&i);
    i.~Item();
}

bool flag = 0;
void Basic::resizeEvent(QResizeEvent *event)
{
    /*qDebug() << judgeHeightRatio();
    qDebug() << judgeWidthRatio();
    int w = judgeWidthRatio();
    int h = judgeHeightRatio();
    if(w == h == 0)
        return;//resize(event->oldSize());
    if(w != 0 && h != 0)*/
    
    
    int W = width()+width()*0.05;   //假设一个比例
    int H = height()+height()*0.03;
    //MessageBox(NULL,TEXT("test"),TEXT("ohh"),MB_OK);
    //return;    
    //SetWindowPos(getWindowHWND(),HWND_NOTOPMOST,0,0,W,H,SWP_NOMOVE);
    int w = judgeWidthRatio();
    int h = judgeHeightRatio();
    if(w == h == 0) //如果比例不相等
        return;
    else
        resize(w,h); //比例相等就设置

    //qDebug() << "resize";
    
}

void Basic::mousePressEvent(QMouseEvent *event)
{
    //if(event->buttons()==Qt::LeftButton)
    qDebug() <<"press";
    getWindowHWND();
    //resize(tW,newH);
    
}

void Basic::mouseReleaseEvent(QMouseEvent *event)
{
    //if(event->buttons()==Qt::LeftButton)
    qDebug() << "release";
    
}

void Basic::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::MouseTrackingChange)
        qDebug() << "change Event";
}

int Basic::judgeWidthRatio()
{
    int w = width();    //获取当前窗口的宽 qt的函数
    for(int i = 1; i< sqrt(w); i++){
        if(w%i == 0){
            if(i == WindowRatioW || w/i == WindowRatioW) //WindowRationW == 16
                return w;
        }
    }
    return 0;
}

int Basic::judgeHeightRatio()
{
    int h = height();   //获取当前窗口的高 qt的函数
    for(int i = 1; i< sqrt(h); i++){
        if(h%i == 0){
            if(i == WindowRatioH || h/i == WindowRatioH) //WindowRationH == 9
                return h;
        }
    }
    return 0;
}

HWND Basic::getWindowHWND()
{
    //char title[225];
    //GetConsoleTitle(title,225);
    //return FindWindow(NULL,title);
    std::wstring title = titleName.toStdWString();
    const wchar_t* str = title.c_str();
          
    HWND hq = FindWindow(NULL,str);
    return hq;
}
/*
bool Basic::event(QEvent *event)
{

    if(event->type() == QEvent::MouseButtonPress)
    {
        //一般情况下我们不鼠标按键直接通过QEvent函数处理，而是经过其子类QMouseEvent类来处理
        QMouseEvent *ev1 = (QMouseEvent *)event;
        if(ev1->type() == QMouseEvent::MouseButtonPress)
        {
            qDebug()<<"mouse pressed!";
        }
    }
    
    //注意，函数最后必须返回原来的event函数，即返回父类的event
    return QWidget::event(event);
    
}

 */




