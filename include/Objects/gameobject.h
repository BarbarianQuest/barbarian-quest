#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <destructable.h>
#include <Base Content/passivecontent.h>


class GameObject : public PassiveContent
{
    public:
        GameObject();
        virtual ~GameObject();

        void allocateAssets();
        void setManager(ResourceManager*);

        int objectID;

    protected:
    private:
};

#endif // GAMEOBJECT_H
