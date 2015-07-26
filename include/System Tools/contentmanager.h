#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "eventhandler.h"
#include "dungeon.h"


class ContentManager
{
    public:
        ContentManager();
        virtual ~ContentManager();

        EventHandler* eventHandler;
        Dungeon* dungeon;

        void setEventHandler(EventHandler*);
        void setDungeon(Dungeon*);

    protected:
    private:
};

#endif // CONTENTMANAGER_H
