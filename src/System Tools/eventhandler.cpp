#include <System Tools/eventhandler.h>

EventHandler::EventHandler()
{
    //ctor
}

EventHandler::~EventHandler()
{
    //dtor
}

void EventHandler::clean()
{
    events.clear();
}

void EventHandler::newScript(std::string newSc)
{
    int i;
    std::vector<std::string> newEvs = stringTools.parseCommands(newSc);
    for(i=0;i<newEvs.size();i++)
    {
        newEvent(newEvs[i]);
    }
}

void EventHandler::newEvent(std::string newEv)
{
    events.push_back(new GameEvent);
    events.back()->setString(newEv);
    events.back()->setStringTools(&stringTools);
}
