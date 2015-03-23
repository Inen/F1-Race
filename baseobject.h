#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QPainter>
#include <vector>


class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject();

    virtual void Draw(QPainter *p) = 0;

    float GetX();
    void SetX(float x);
    float GetY();
    void SetY(float y);
    unsigned GetId();
    void SetId(unsigned id);
    float GetSpeed();
    void SetSpeed(float s);


    typedef std::vector <BaseObject *> Container;
    typedef std::vector <BaseObject *>::iterator Iterator;

protected:
    float X = 0;
    float Y = 0;
    unsigned Id = 0;
    float Speed = 2;
};

#endif // BASEOBJECT_H
