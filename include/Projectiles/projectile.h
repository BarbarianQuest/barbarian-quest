#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Base Content/dynamiccontent.h>


class Projectile : public DynamicContent
{
    public:
        Projectile();
        virtual ~Projectile();

        void hits(Content*);
        void update();
    protected:
    private:
};

#endif // PROJECTILE_H
