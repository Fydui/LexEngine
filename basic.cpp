#include "basic.h"
Basic::Basic( QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(titleName);
    setBaseSize(windowWidth,windowHeight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //关闭横竖滚动栏
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
    
    setFixed(WindowType::ScaleIn);
    view.setParent(this);
    view.resize(windowWidth,windowHeight);          //设置视图范围      
    view.setScene(&scene);
    scene.setSceneRect(0,0,windowWidth,windowHeight);
    viewLastH = lastHeight = windowHeight;
    viewLastW = lastWidth = windowWidth;
    windowType = WindowType::ScaleIn;
}
/*
Basic::Basic(WindowType t, QWidget *parent)
    : Basic(parent)
{    
    setFixed(t);
    view.setParent(this);
    view.resize(windowWidth,windowHeight);          //设置视图范围      
    view.setScene(&scene);
    scene.setSceneRect(0,0,windowWidth,windowHeight);
    viewLastH = lastHeight = windowHeight;
    viewLastW = lastWidth = windowWidth;
    windowType = t;
    
}*/

Basic::~Basic()
{
}

void Basic::getScreenPara()
{
    QDesktopWidget desktopWidget;
    QRect deskRect = desktopWidget.availableGeometry(); //获得可用窗口大小(去除通知栏/任务栏的大小)
    QRect screenRect = desktopWidget.screenGeometry();  //获得当前桌面的大小(整块屏幕总大小)
    
    screenWindowHeight = deskRect.height();             
    screenWindowWidth = deskRect.width(); 
    
    deskHeight = screenRect.height();
    deskWidth = screenRect.width();
 
}

void Basic::setWindowSize(int w, int h)
{
    screenWindowHeight = h;            
    screenWindowWidth = w; 
    
    deskHeight = h;
    deskWidth = w;    
}

QPoint Basic::getWindowSize()
{
    return QPoint(windowHeight,windowWidth);
}

void Basic::setFixed(WindowType s)
{
    if(s == Android){
        deskWidth = screenWindowWidth;
        deskHeight = screenWindowHeight;
    }
    else if(s == Fix){
        deskHeight = windowHeight;
        deskWidth = windowWidth;
        setFixedSize(windowHeight,windowWidth);        //固定窗口大小
    }
    else{
        deskHeight = windowHeight;
        deskWidth = windowWidth;
        //setMinimumHeight(windowHeight);
        //setMinimumWidth(windowWidth);
        /*
        //获取窗口长宽比例:
        int temp = 1;
        int x = (deskHeight > deskWidth) ? deskHeight : deskWidth;
        int y = (deskHeight < deskWidth) ? deskHeight : deskWidth;
        while(x % y != 0){ //辗转相除 获取最大公因数
            temp = x%y;
            x = y;
            y = temp;
        }*/
    }
}

WindowType Basic::getFixedValue(){
    return windowType;
}

void Basic::addScene(Scene &s)
{
    view.setScene(&s);
}
void Basic::addItem(Item* i)
{
    /*
    i.moveItem(i.getItemValue().point.x(), i.getItemValue().point.y(), i.getItemValue().anchor);  //处理Item类构造函数中的移动参数
    i.setItemScale(i.getScaleValue().value,i.getScaleValue().anchor);    //处理Item类构造函数中的缩放参数
    i.setItemRotation(i.getRotationValue().value,i.getRotationValue().anchor);*/
    i->moveItem(i->getItemValue().point.x(), i->getItemValue().point.y(), i->getItemValue().anchor);  //处理Item类构造函数中的移动参数
    i->setItemScale(i->getScaleValue().value,i->getScaleValue().anchor);    //处理Item类构造函数中的缩放参数
    i->setItemRotation(i->getRotationValue().value,i->getRotationValue().anchor);
    //scene.addItem(i);  //添加进scene
    scene.QGraphicsScene::addItem(i);
}
Item *Basic::addItem(QString path, int x, int y,  QString fun)
{
    Item* temp = new Item(path,x,y,fun);
    scene.addItem(temp);
    return temp;
}
void Basic::removeItem(Item &i)
{
    scene.removeItem(&i);
    i.~Item();
}

void Basic::removeItem(Item *i)
{
    scene.removeItem(i);
    i->~Item();
}

void Basic::resizeEvent(QResizeEvent *event)
{
    if(windowType == WindowType::Scale){      //scale模式: 缩放窗口时 窗口大小和窗口内画面全部会符合某个比例
        if(timerEventFlag){
            killTimer(timerEventFlag); 
            timerEventFlag = 0;
        }
        timerEventFlag = startTimer(50); //使用计时器拉开resizeEvent触发间隔 避免内循环(resizeEvent <-> resize)
    }
    else if(windowType == WindowType::ScaleIn){//scaleIn模式 缩放窗口时 仅窗口内内容保持以某个比例缩放
        
        int tempW = baseSize().width(), tempH = baseSize().height();
        int baseW = baseSize().width(), baseH = baseSize().height();
        
        if(width() > baseW){
            if(view.height() < height() && (view.width() >= width())){
                tempW = width();
                tempH = width()* baseH / baseW;
                //qDebug() << "1 2";
            }
            else{
                if(baseW <= width() && width() < height()* baseW / baseH){
                    tempW = width();
                    tempH = width()* baseH / baseW;
                    //qDebug() << "1 3";
                }
                else{
                    tempW = height()* baseW / baseH;
                    tempH = height();
                    //qDebug() << "1 1";
                }
            }
        }
        else if(width() < baseW){
            if(view.width() < width() && width() < baseSize().width() && height() <= view.height()){               
                tempW = height()* baseW / baseH;
                tempH = height();
                //qDebug() << "2 1";                
            }
            else{
                if(height() <= width()* baseH / baseW){
                    tempW = height()* baseW / baseH;
                    tempH = height();
                    //qDebug() << "2 3";
                }
                else{
                    tempW = width();
                    tempH = width()* baseH / baseW;
                    //qDebug() << "2 2"; 
                }
            }         
        }
        else if(height() > baseH){
            tempW = width();
            tempH = width() * baseH / baseW;
            //qDebug() << "3";
        }
        else if(height() < baseH){
            tempH = height();
            tempW = height()*baseW / baseH;
            //qDebug() << "4";
        }
        
        
        viewLastW = view.width();
        viewLastH = view.height();
        lastHeight = tempH;
        lastWidth = tempW;
        view.resize(tempW,tempH);
        view.scale(view.width()/qreal(viewLastW), view.width()/qreal(viewLastW)); 
        //scene.setSceneRect(0,0,tempW+1,tempH+1);                
        
        //view.centerOn(0,0);           
      
        //将view居中
        view.move(width()/2 - view.width()/2, height()/2 - view.height()/2);
    }
    else if(windowType ==WindowType::Debug){
        view.resize(width(),height());
    }
    else if(windowType == WindowType::Free) return;
    return;
}

void Basic::timerEvent(QTimerEvent *event)
{       
    getScreenPara();  //获取屏幕大小等信息
    int viewSceneW = 0, viewSceneH = 0;
    
    if(width() == deskWidth && height() == deskHeight){       //如果窗口最大化, 则对其进行显示优化
        int reduceW = geometry().x(), reduceH = geometry().y(); 
        
        //减去windows通知栏的大小, 这样设置窗口大小,窗口就不会被windows通知栏遮挡
        viewSceneW = width()-reduceW;
        viewSceneH = height()-reduceH;        
    }
    else if(width() == windowWidth){ 
        
        //竖着拉保持比例不变
        viewSceneW = windowWidth = height()* baseSize().width()/baseSize().height();
        viewSceneH = windowHeight = height();          
    }
    else{
        //横着拉保持比例不变
        viewSceneW = windowWidth = width();
        viewSceneH = windowHeight = width()*baseSize().height()/baseSize().width();         
    }
    
    killTimer(event->timerId());    //结束计时器 (不及时结束窗口似乎会鬼畜    
    timerEventFlag = 0;             //重置计时器事件ID
    
    resize(windowWidth,windowHeight);   //设置窗口大小
    view.resize(viewSceneW,viewSceneH); //设置view大小
    view.scale(qreal(viewSceneW)/lastWidth,qreal(viewSceneW)/lastWidth); //对view的内容进行缩放
    view.centerOn(0,0);         //将view居中
    
    lastHeight = height();
    lastWidth = width();
    
}


/*
int Basic::judgeWidthRatio()
{
    int w = windowWidth();    //获取当前窗口的宽 qt的函数
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
    int h = windowHeight();   //获取当前窗口的高 qt的函数
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





