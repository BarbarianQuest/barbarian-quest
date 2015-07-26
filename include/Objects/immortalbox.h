#ifndef IMMORTALBOX_H
#define IMMORTALBOX_H

#include <gameobject.h>


class ImmortalBox : public GameObject
{
    public:
        ImmortalBox();
        virtual ~ImmortalBox();

        void notInContact();
        void hits(Content*);

        void allocateAssets();
    protected:
    private:
};

#endif // IMMORTALBOX_H
