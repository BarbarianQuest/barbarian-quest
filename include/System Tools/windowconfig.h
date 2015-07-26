#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<random.hpp>
#include<fastmaths.h>

using namespace std;


class WindowConfig
{
    public:
        WindowConfig();
        virtual ~WindowConfig();

        sf::VideoMode resolution;
        fastMaths maths;

        string title;

        void randomiseTitle();
        void loadConfig();
        void saveConfig();
        void appendConfig(vector<bool>,vector<bool>);
        void applyConfig();
        void clearConfig();

        int window_x,window_y;
        long style;
        bool openLauncher;
        bool r720x480,r960x600,r1024x768,r1360x768;
        bool fullscreen;

    protected:
    private:
        string rawstring;
        vector<bool> allConfig;
        vector<string> prefixes;
        vector<string> suffixes;
        int startOfRes;


};

#endif // WINDOWCONFIG_H
