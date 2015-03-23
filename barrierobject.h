#ifndef BARRIEROBJECT_H
#define BARRIEROBJECT_H

#include "baseobject.h"

class BarrierObject : public BaseObject
{
public:
    BarrierObject(float x, float y, float s);
    ~BarrierObject();

    void Draw(QPainter *p);
};

#endif // BARRIEROBJECT_H
