#include "basic.h"
#include "math.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Basic w(WindowType::ScaleIn,nullptr);
    
    //Item my("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/UI/user_detail_bg1.png",0,0);
    //w.addItem(my);

    
    //Item my2("E:/文档/图片/沈霍伊.jpg",150,0);
    //my2.setItemScale(1.5);
    //my2.setItemRotation(60);
    
    Item my3 = Item("E:/文档/图片/52529731_p0.jpg",0,0);
     
    
    //w.addItem(my2);
    //w.addItem(my3);
    
    Item my4(my3);
    Item my5 = my4;
    w.addItem(my5);
    w.show();
   
    return a.exec();
}
