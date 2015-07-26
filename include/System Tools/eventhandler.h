#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "stringtools.h"
#include "event.h"

using namespace std;

class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();

        StringTools stringTools;

        void newEvent(std::string );

        void newScript(std::string);

        vector<GameEvent*> events;

        void parseEvent(GameEvent*);

        void clean();

    protected:
    private:
};

#endif // EVENTHANDLER_H
