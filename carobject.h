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

    void SetWidth(int w);
    int GetWidth();

    void SetHeight(int h);
    int GetHeight();

private:
    int accuracy = 10;
    int accelerator = 10;
    int brake = 15;
    int width, height;
};

#endif // CAROBJECT_H
