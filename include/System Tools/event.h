#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "stringtools.h"

class GameEvent
{
    public:
        GameEvent();
        GameEvent(std::string);
        virtual ~GameEvent();

        StringTools* stringTools;

        void setStringTools(StringTools*);

        void setString(std::string);
        std::string getString();
        std::string getCommand();
        std::string getArgs();
        std::vector<std::string> getVariables();
        std::string getObject();

    protected:
    private:

        void* content;
        std::string eventAsString;
        std::string command;
        std::string args;
        std::string object;
        std::vector<std::string> phrases;
        std::vector<std::string> variables;
        std::vector<std::string> buildObjects;
        std::vector<sf::Vector2f> buildPositions;

};

#endif // EVENT_H
