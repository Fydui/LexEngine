#include "basic.h"
#include "math.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Basic w(WindowType::ScaleIn,nullptr);
    
    Item my("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/UI/user_detail_bg1.png",0,0);
    w.addItem(my);

    
    Item my2("E:/文档/图片/沈霍伊.jpg",0,0);
    my2.setItemScale(1.5);
    my2.setItemRotation(90);
    
    w.addItem(my2);
        
    w.show();
   
    return a.exec();
}
