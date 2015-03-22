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

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);
    unsigned GetId();
    void SetId(unsigned id);
    int GetSpeed();
    void SetSpeed(int s);


    typedef std::vector <BaseObject *> Container;
    typedef std::vector <BaseObject *>::iterator Iterator;

protected:
    int X = 0;
    int Y = 0;
    unsigned Id = 0;
    int Speed = 15;
};

#endif // BASEOBJECT_H
