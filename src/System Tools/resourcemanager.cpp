#include <System Tools/resourcemanager.h>

ResourceManager::ResourceManager()
{
    //ctor
    directories.resize(4);
    filetypes.resize(5);

    blank.loadFromFile("./assets/error.png");
    def_font.loadFromFile("./fonts/hype.ttf");

    directories[0]="./assets/";
    directories[1]="./sounds/";
    directories[2]="./fonts/";
    directories[3]="./data/";

    filetypes[0]=".png";
    filetypes[1]=".wav";
    filetypes[2]=".ttf";
    filetypes[3]=".dat";
    filetypes[4]=".txt";
    //filetypes[5]=".gif";
}

ResourceManager::~ResourceManager()
{
    //dtor
}

inline bool ResourceManager::checkExists(string name)
{
       ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

void ResourceManager::addDirectory(string newDir)
{
    directories.push_back(newDir);
    return;
}

const Font& ResourceManager::getFont(const string& name)
{
    for( std::map<std::string, Font>::const_iterator it = Fonts.begin();
         it != Fonts.end();
         ++it)
    {
        if( name == it->first )
        {
            return it->second;
        }
    }

    int i,j;
    Font _font;
    for(i=0; i<directories.size(); i++)
    {
        for(j=0; j<filetypes.size(); j++)
        {
            if(checkExists(directories[i]+name+filetypes[j]))
            {
                _font.loadFromFile(directories[i]+name+filetypes[j]);
                Fonts[name]=_font;
                return Fonts[name];
            }
        }
    }
    debug.println(" not found!");
    return def_font;
}

const Texture& ResourceManager::getTex(const string& name)
{
    for( std::map<std::string, Texture>::const_iterator it = Textures.begin();
         it != Textures.end();
         ++it)
    {
        if( name == it->first )
        {
            return it->second;
        }
    }

    int i,j;
    Texture _tex;
    for(i=0; i<directories.size(); i++)
    {
        for(j=0; j<filetypes.size(); j++)
        {
            if(checkExists(directories[i]+name+filetypes[j]))
            {
                _tex.loadFromFile(directories[i]+name+filetypes[j]);

                Textures[name]=_tex;
                return Textures[name];
            }
        }
    }
    debug.println(name+ " not found!");
    return blank;
}


