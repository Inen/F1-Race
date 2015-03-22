#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "baseobject.h"

class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    void AddObject(BaseObject * b);

    BaseObject::Container * GetObjects();

private:
    BaseObject::Container Objects;
    unsigned currentId = 1;
};

#endif // OBJECTMANAGER_H
