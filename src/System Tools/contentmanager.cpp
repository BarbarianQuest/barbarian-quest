#include <System Tools/contentmanager.h>


ContentManager::ContentManager()
{
    //ctor
}

ContentManager::~ContentManager()
{
    //dtor
}

void ContentManager::setEventHandler(EventHandler* events)
{
    eventHandler = events;
    return;
}
