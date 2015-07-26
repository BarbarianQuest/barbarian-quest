#pragma once

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <fastmaths.h>
#include <debugtools.h>

using namespace std;
using namespace sf;


class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();

        fastMaths maths;
        DebugTools debug;

        void addDirectory(string);
        void addFiletype(string);
        inline bool checkExists(string);

        const Texture& getTex(const string&);
        const SoundBuffer& getSound(const string&);
        const Font& getFont(const string&);
        const string& getFile(const string&);

    protected:
    private:

        Texture blank;
        Font def_font;

        vector<string> directories;
        vector<string> filetypes;
        map<string,Texture> Textures;
        map<string,Font> Fonts;
        map<string,string> Files;

};

#endif // RESOURCEMANAGER_H
