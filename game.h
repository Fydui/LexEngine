#ifndef GAME_H
#define GAME_H
#include "basic.h"

class game : public Basic
{
   Q_OBJECT
public:
     void start();
public slots:
     void test(){
         qDebug()<<"!!!!!!!!!!!!!!!!!!";
     }
};

#endif // GAME_H
