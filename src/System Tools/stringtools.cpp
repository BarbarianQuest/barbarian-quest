#include <System Tools/stringtools.h>

using namespace std;

StringTools::StringTools()
{
    //ctor
    permittedClean = " ()[]\n\r;,{}.";
    permittedIsolated = " \n\r";
    valueDelimiters = "(,)";
    commandDelimiters = ";\n\r";
    phraseDelimiters = ".";
    permittedNumericalFloat = ".0123456789";
    permittedNumericalInt = "0123456789";
}

StringTools::~StringTools()
{
    //dtor
}

std::vector<float> StringTools::parseFloatValues(std::string phrase, std::string arg)
{
    int i,j,k;
    std::vector<float>valuesAsFloats;
    std::vector<std::string> valuesAsStrings = parseStringValues(phrase,arg);
    for(i=0; i<valuesAsStrings.size(); i++)
    {
        bool parseable = true;
        for(j=0; j<valuesAsStrings[i].length(); j++)
        {
            for(k=0; j<permittedNumericalFloat.length(); k++)
            {
                if(valuesAsStrings[i][j] != permittedNumericalFloat[k]) {parseable = false;}
            }
        }
        if(parseable)
        {
            valuesAsFloats.push_back(boost::lexical_cast<int>(valuesAsStrings[i]));
        }
        else
        {
            cout << "could not parse value " << valuesAsStrings[i] << endl;
        }
    }
    return(valuesAsFloats);
}

std::vector<int> StringTools::parseIntValues(std::string phrase, std::string arg)
{
    int i,j,k;
    std::vector<int>valuesAsInts;
    std::vector<std::string> valuesAsStrings = parseStringValues(phrase,arg);
    for(i=0; i<valuesAsStrings.size(); i++)
    {
        bool parseable = true;
        for(j=0; j<valuesAsStrings[i].length(); j++)
        {
            for(k=0; j<permittedNumericalInt.length(); k++)
            {
                if(valuesAsStrings[i][j] != permittedNumericalInt[k]) {parseable = false;}
            }
        }
        if(parseable)
        {
            valuesAsInts.push_back(boost::lexical_cast<int>(valuesAsStrings[i]));
        }
        else
        {
            cout << "could not parse value " << valuesAsStrings[i] << endl;
        }
    }
    return(valuesAsInts);
}

std::vector<std::string> StringTools::parseStringValues(std::string phrase, std::string arg)
{
    int i,j;
    bool braceOpen, braceClosed;
    std::vector<std::string> valuesAsStrings(0);
    int numberOfValues = 0;
    for(i=0; i<phrase.length(); i++)
    {
        if(phrase.at(i) == ')') {braceClosed = true; braceOpen = false;}
        if(valuesAsStrings.size() != numberOfValues)
        {
            valuesAsStrings.resize(numberOfValues);
        }
        if(braceOpen)
        {
            bool permitted = true;
            if(phrase[i] == ','){numberOfValues += 1; continue;}
            for(j=0; j<valueDelimiters.length(); j++)
            {
                if(phrase[i] == valueDelimiters[j])
                {
                    permitted = false;
                }
            }
            if(permitted)
            {
                valuesAsStrings[numberOfValues-1]+=phrase[i];
            }
        }

        if(!braceOpen && phrase[i] == '(')
        {
            numberOfValues += 1;
            braceOpen == true;
        }
    }
    return(valuesAsStrings);
}

std::vector<std::string> StringTools::parseSinglePhrase(std::string phrase)
{
    int i;
    int lBracePos = -1;
    int rBracePos = -1;
    int commaPos = -1;
    std::vector<std::string> phraseValues(0);
    for(i=0; i<phrase.length(); i++)
    {
        if(phrase[i] == '(')
        {
            lBracePos = i;
        }
        if(phrase[i] == ',' && lBracePos != -1)
        {
            commaPos = i;
        }
        if(phrase[i] == ')' && commaPos != -1)
        {
            rBracePos = i;
        }
    }
    if(rBracePos != -1)
    {
        std::string subStr = "";
        subStr.insert(subStr.begin(),phrase.begin()+lBracePos+1,phrase.begin()+commaPos-1);
        phraseValues.push_back(subStr);

        subStr = "";
        subStr.insert(subStr.begin(),phrase.begin()+commaPos+1,phrase.begin()+rBracePos-1);
        phraseValues.push_back(subStr);

        return(phraseValues);
    }
    phraseValues.push_back("0");
    phraseValues.push_back("0");
    return(phraseValues);
}

std::string StringTools::parseObject(std::string inArg)
{
    std::vector<std::string> phrases = parsePhrases(inArg);
    if(phrases.size() >= 1)
    {
        return(phrases[0]);
    }
    else
    {
        return("error");
    }
}

std::vector<std::string> StringTools::parsePhrases(std::string command)
{
    std::vector<std::string> phraseList(0);
    int i,j;
    int lastStart = 0;

    phraseDelimiters = '.';

    cout << "phraseDel size: " << phraseDelimiters.length() << endl;

    cout << "is the error" << endl;

    for(i=0; i<command.length(); i++)
    {
        for(j=0; j<phraseDelimiters.length(); j++)
        {
            if(command[i] == phraseDelimiters[j])
            {
                cout << command[i] << "matched" << phraseDelimiters[j] << endl;
                std::string subStr = "";
                subStr.insert(subStr.begin(),command.begin()+lastStart,command.begin()+i);
                cout << "phrase" << ": " << subStr << endl;
                phraseList.push_back(subStr);
                lastStart = i+1;
            }
        }
        if(i==command.length()-1)
        {
            std::string subStr = "";
            subStr.insert(subStr.begin(),command.begin()+lastStart,command.begin()+i+1);
            cout << "last phrase" << ": " << subStr << endl;
            phraseList.push_back(subStr);
        }

    }

    for(i=0; i<phraseList.size(); i++)
    {
        std::cout << phraseList[i] << endl;
    }

    cout << "in here?" << endl;

    return(phraseList);
}

std::vector<std::string> StringTools::parseCommands(std::string commandSet)
{
    std::vector<std::string> commandList(0);
    int i,j;
    int lastStart = 0;
    for(i=0; i<commandSet.length(); i++)
    {
        for(j=0; j<commandDelimiters.length(); j++)
        {
            if(commandSet[i] == commandDelimiters[j])
            {
                std::string subStr = "";
                subStr.insert(subStr.begin(),commandSet.begin()+lastStart,commandSet.begin()+i);
                commandList.push_back(subStr);
                lastStart = i+1;
            }
        }
        if(i==commandSet.length()-1)
        {
            std::string subStr = "";
            subStr.insert(subStr.begin(),commandSet.begin()+lastStart,commandSet.begin()+i+1);
            commandList.push_back(subStr);
        }

    }
    for(i=0; i<commandList.size(); i++)
    {
        std::cout << commandList[i] << endl;
    }
    return(commandList);
}

std::string StringTools::beforeFirstSpace(std::string phrase)
{
    int i;
    std::string beforeSpace = "";
    for(i=0; i<phrase.length(); i++)
    {
        if(phrase[i]==' ')
        {
            beforeSpace.insert(beforeSpace.begin(),phrase.begin(),phrase.begin()+i);
            return(beforeSpace);
        }
    }
}

std::string StringTools::afterFirstSpace(std::string phrase)
{
    int i;
    std::string afterSpace = "";
    for(i=0; i<phrase.length(); i++)
    {
        if(phrase[i]==' ')
        {
            afterSpace.insert(afterSpace.begin(),phrase.begin()+i+1,phrase.end());
            return(afterSpace);
        }
    }
}

bool StringTools::containsIsolated(std::string toCheck, std::string phraseToFind)
{
    bool cleanInstance = false;
    bool cleanLeft = false;
    bool cleanRight = false;
    bool found = false;
    bool firstLetter = false;
    if(phraseToFind.length() == 0)
    {
        return true;
    }
    if (toCheck.find(phraseToFind) != std::string::npos)
    {
        found = true;
        int i,j;
        int pos = toCheck.find(phraseToFind);

        int endSec = pos+phraseToFind.length();
        if(i==0){cleanLeft = true;}
        if(endSec>=toCheck.length()-1){cleanRight = true;}
        if(i!=0)
        {
            for(j=0; j<permittedIsolated.length(); j++)
            {
                if(toCheck[i-1] == permittedIsolated[j]){cleanLeft = true;}
            }
        }

        if(endSec<toCheck.length()-1)
        {
            for(j=0; j<permittedIsolated.length(); j++)
            {
                if(toCheck[endSec] == permittedIsolated[j]){cleanRight = true;}
            }
        }
        cleanInstance = cleanLeft && cleanRight;
        return(cleanInstance);
    }
    else
    {
        return(false);
    }
}


bool StringTools::containsClean(std::string toCheck, std::string phraseToFind)
{
    bool cleanInstance = false;
    bool cleanLeft = false;
    bool cleanRight = false;
    bool found = false;
    bool firstLetter = false;
    if(phraseToFind.length() == 0)
    {
        return true;
    }
    if (toCheck.find(phraseToFind) != std::string::npos)
    {
        found = true;
        int i,j;
        int pos = toCheck.find(phraseToFind);

        int endSec = pos+phraseToFind.length();
        if(i==0){cleanLeft = true;}
        if(endSec>=toCheck.length()-1){cleanRight = true;}
        if(i!=0)
        {
            for(j=0; j<permittedClean.length(); j++)
            {
                if(toCheck[i-1] == permittedClean[j]){cleanLeft = true;}
            }
        }

        if(endSec<toCheck.length()-1)
        {
            for(j=0; j<permittedClean.length(); j++)
            {
                if(toCheck[endSec] == permittedClean[j]){cleanRight = true;}
            }
        }
        cleanInstance = cleanLeft && cleanRight;
        return(cleanInstance);
    }
    else
    {
        return(false);
    }
}
