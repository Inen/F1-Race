#include "baseobject.h"

BaseObject::BaseObject()
{
    X = 0;
    Y = 0;
}

BaseObject::~BaseObject()
{

}

float BaseObject::GetX()
{
    return X;
}

void BaseObject::SetX(float x)
{
    X = x;
}

float BaseObject::GetY()
{
    return Y;
}

void BaseObject::SetY(float y)
{
    Y = y;
}

unsigned BaseObject::GetId()
{
    return Id;
}

void BaseObject::SetId(unsigned id)
{
    Id = id;
}

void BaseObject::SetSpeed(float s)
{
    Speed = s;
}

float BaseObject::GetSpeed()
{
    return Speed;
}
