#include "debugtools.h"

DebugTools::DebugTools()
{
    //ctor
}

DebugTools::~DebugTools()
{
    //dtor
}

void DebugTools::println(std::string println)
{
    std::cout << println << endl;
}

void DebugTools::printNumber(std::string name, float num)
{
    std::cout << name << ": " << num << endl;
}

void DebugTools::printNumber(std::string name, int num)
{
    std::cout << name << ": " << num << endl;
}

void DebugTools::printVector(std::string name, sf::Vector2f vec)
{
    std::cout << name << ": [" << vec.x << ", " << vec.y << "]" << endl;
}


