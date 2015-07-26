#ifndef CONTAINER_H
#define CONTAINER_H

#include <gameobject.h>


class Container : public GameObject
{
    public:
        Container();
        virtual ~Container();

        vector <Content*> contents;

        void update();

        virtual void allocateContents()
        {

        }
        virtual void addContent(Content* newContent)
        {
            contents.push_back(newContent);
        }
    protected:
    private:
};

#endif // CONTAINER_H
