#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;


class DebugTools
{
    public:
        DebugTools();
        virtual ~DebugTools();

        void println(std::string);
        void println(int);
        void println(float);
        void printVector(std::string, sf::Vector2f);
        void printNumber(std::string, int);
        void printNumber(std::string, float);

    protected:
    private:
};

#endif // DEBUGTOOLS_H
