#include "barrierobject.h"

BarrierObject::BarrierObject(int x, int y, int s)
{
    X = x;
    Y = y;
    Speed = s;
}

BarrierObject::~BarrierObject()
{

}

void BarrierObject::Draw(QPainter *p)
{
    QPixmap pixmap;
    if ( pixmap.load("/home/dima/Projects/F1_Race/003.png") )
        p->drawPixmap(X - pixmap.width(), Y - pixmap.height(), pixmap);
}
