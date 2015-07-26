#ifndef DYNAMICCONTENT_H
#define DYNAMICCONTENT_H


#include "content.h"


class DynamicContent : public Content
{
    public:
        DynamicContent();
        virtual ~DynamicContent();

        float maxSpeed, rootMaxSpeed, absMaxSpeed, absRootMaxSpeed;

        void update();

    protected:
    private:



};

#endif // DYNAMICCONTENT_H
