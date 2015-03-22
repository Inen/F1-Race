#include "objectmanager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
    for(auto it = Objects.begin(); it != Objects.end(); ++it)
    {
        delete (*it);
    }
}

void ObjectManager::AddObject(BaseObject * b)
{
    b->SetId(currentId);

    if (currentId <= sizeof(unsigned))
            currentId++;
    else currentId = 1;

    Objects.push_back(b);
}

BaseObject::Container * ObjectManager::GetObjects()
{
    return &Objects;
}
