#include "basic.h"
#include "math.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Basic w(WindowType::ScaleIn,nullptr);
    
    Item my("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/UI/user_detail_bg1.png",0,0);
    w.addItem(my);
    
    //Item my1("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/image/Lexington_Strap_bikini.png");
    //w.addItem(my1);
    
    Item my2("E:/文档/图片/沈霍伊.jpg");
    w.addItem(my2);
    my2.moveBy(600,300);
    my.moveBy(0,0);
    
    //w.removeItem(my1);
    
    w.show();
   
    return a.exec();
}
