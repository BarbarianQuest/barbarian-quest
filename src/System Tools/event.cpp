#include <System Tools/event.h>

GameEvent::GameEvent()
{
    //ctor
}

GameEvent::GameEvent(std::string script)
{
    setString(script);
}

GameEvent::~GameEvent()
{
    //dtor
}

void GameEvent::setStringTools(StringTools* newTools)
{
    stringTools = newTools;
}

std::vector<std::string> GameEvent::getVariables()
{
    return(variables);
}

std::string GameEvent::getObject()
{
    return(object);
}

void GameEvent::setString(std::string script)
{
    eventAsString = script;
    command = stringTools->beforeFirstSpace(eventAsString);
    args = stringTools->afterFirstSpace(eventAsString);
    phrases = stringTools->parsePhrases(args);
    if(phrases.size() >= 1)
    {
        object = phrases[0];
    }
    if(phrases.size() > 1)
    {
        variables.insert(variables.begin(),phrases.begin()+1,phrases.end());
    }
}
std::string GameEvent::getString(){
    return eventAsString;
}

std::string GameEvent::getCommand(){
    return command;
}

std::string GameEvent::getArgs(){
    return args;
}
