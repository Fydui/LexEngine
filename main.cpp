//#include "basic.h"
#include "game.h"
//#include "item.h"
#include <QApplication>
game* g;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    g = new game;
    g->Basic::show();
    g->start();
    
    return a.exec();
}
