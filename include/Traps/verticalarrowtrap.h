#ifndef VERTICALARROWTRAP_H
#define VERTICALARROWTRAP_H

#include <trap.h>
#include <projectile.h>


class VerticalArrowTrap : public Trap
{
    public:
        VerticalArrowTrap();
        virtual ~VerticalArrowTrap();

        Content* arrow;

        void detects(Content*);
    protected:
    private:
};

#endif // VERTICALARROWTRAP_H
