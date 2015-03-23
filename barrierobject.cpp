#include "barrierobject.h"

BarrierObject::BarrierObject(float x, float y, float s)
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
    if ( pixmap.load(":/Images/Barrier.png") )
        p->drawPixmap(X - pixmap.width(), Y - pixmap.height(), pixmap);
}
