#include "baseobject.h"

BaseObject::BaseObject()
{
    X = 0;
    Y = 0;
}

BaseObject::~BaseObject()
{

}

int BaseObject::GetX()
{
    return X;
}

void BaseObject::SetX(int x)
{
    X = x;
}

int BaseObject::GetY()
{
    return Y;
}

void BaseObject::SetY(int y)
{
    Y = y;
}

void BaseObject::Draw(QPainter *p)
{

}

unsigned BaseObject::GetId()
{
    return Id;
}

void BaseObject::SetId(unsigned id)
{
    Id = id;
}

void BaseObject::SetSpeed(int s)
{
    Speed = s;
}

int BaseObject::GetSpeed()
{
    return Speed;
}
