#ifndef PASSIVECONTENT_H
#define PASSIVECONTENT_H

#include "content.h"


class PassiveContent : public Content
{
    public:
        PassiveContent();
        virtual ~PassiveContent();

        void update();

    protected:
    private:
};

#endif // PASSIVECONTENT_H
