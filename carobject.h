#ifndef CAROBJECT_H
#define CAROBJECT_H

#include "baseobject.h"

class CarObject : public BaseObject
{
public:
    CarObject();
    ~CarObject();

    void Draw(QPainter *p);

    void SetAccuracy(int a);
    int GetAccuracy();

    void SetAccelerator(int a);
    int GetAccelerator();

    void SetBrake(int b);
    int GetBrake();

private:
    int accuracy = 5;
    int accelerator = 10;
    int brake = 15;
};

#endif // CAROBJECT_H
