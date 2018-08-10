#include "basic.h"
#include "math.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Basic w(WindowType::Scalein,nullptr);
    int t = w.heightForWidth(1280);
    
    Item my("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/UI/user_detail_bg1.png");
    w.addItem(my);
    
    Item my1("C:/My/code/MyObj/MengDie_Widget/resources/Lexington/image/Lexington_Strap_bikini.png");
    w.addItem(my1);

    //w.removeItem(my1);
    
    w.show();
   
    return a.exec();
}
