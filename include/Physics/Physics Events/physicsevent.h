#ifndef PHYSICSEVENT_H
#define PHYSICSEVENT_H


#include <Base Content/content.h>


class PhysicsEvent : public Content
{
    public:
        PhysicsEvent();
        virtual ~PhysicsEvent();

        sf::Clock eventClock;
        sf::Time eventTimer;

        virtual void allocateAssets();

        virtual void hits(Content*)
        {

        }

        virtual void evolveHitbox()
        {

        }

    protected:
    private:
};

#endif // PHYSICSEVENT_H
