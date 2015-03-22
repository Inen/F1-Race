#ifndef BARRIEROBJECT_H
#define BARRIEROBJECT_H

#include "baseobject.h"

class BarrierObject : public BaseObject
{
public:
    BarrierObject(int x, int y, int s);
    ~BarrierObject();

    void Draw(QPainter *p);
};

#endif // BARRIEROBJECT_H
