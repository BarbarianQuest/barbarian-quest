#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

//todo: add string
#include<string>
#include<vector>
#include<iostream>
#include<lexical_cast.hpp>

class StringTools
{
    public:
        StringTools();
        virtual ~StringTools();

        std::string permittedClean;
        std::string permittedIsolated;
        std::string phraseDelimiters;
        std::string commandDelimiters;
        std::string valueDelimiters;
        std::string permittedNumericalInt;
        std::string permittedNumericalFloat;

        std::vector<std::string> parseCommands(std::string);

        std::string beforeFirstSpace(std::string);
        std::string afterFirstSpace(std::string);

        std::vector<std::string> parsePhrases(std::string);
        std::vector<std::string> parseSinglePhrase(std::string);

        std::vector<int> parseIntValues(std::string, std::string);
        std::vector<float> parseFloatValues(std::string, std::string);
        std::vector<std::string> parseStringValues(std::string, std::string);

        std::string parseObject(std::string);


        bool containsIsolated(std::string, std::string);
        bool containsClean(std::string,std::string);
        bool containsDirty(std::string,std::string);

    protected:
    private:
};

#endif // STRINGTOOLS_H
