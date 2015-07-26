#include <System Tools/windowconfig.h>

WindowConfig::WindowConfig()
{
    //ctor
    window_x = 960;
    window_y = 600;
    title = "BQII";
    resolution.width=window_x;
    resolution.height=window_y;
    style = sf::Style::Close;
    openLauncher = true;
    randomiseTitle();
}

WindowConfig::~WindowConfig()
{
    //dtor
}

void WindowConfig::loadConfig()
{
    int i;
    ifstream preferences ("./data/config.dat");
    if (preferences.is_open())
    {
        getline (preferences,rawstring);
        preferences.close();
    }
    for(i=0; i<rawstring.size(); i++)
    {
        allConfig.push_back(rawstring[i]=='1');
    }
    if(allConfig[0]==true)
    {
        openLauncher = false;
    }
    startOfRes = 2;
}

void WindowConfig::appendConfig(vector<bool> other, vector<bool> res)
{
    int i;
    int totalsize = other.size() + res.size();
    startOfRes = other.size();
    allConfig.resize(totalsize);
    for(i=0; i<other.size(); i++)
    {
        allConfig[i]=other[i];
    }
    for(i=other.size();i<totalsize;i++)
    {
        allConfig[i]=res[i-other.size()];
    }
}

void WindowConfig::saveConfig()
{
    int i;
    ofstream preferences_out ("./data/config.dat");
    if (preferences_out.is_open())
    {
        for(i=0; i<allConfig.size();i++)
        {
            if(allConfig[i])
            {
                preferences_out << "1";
            }
            else if (!allConfig[i])
            {
                preferences_out << "0";
            }
        }
        preferences_out.close();
    }
}

void WindowConfig::clearConfig()
{
    int i;
    ofstream preferences_out ("./data/config.dat");
    if (preferences_out.is_open())
    {
        for(i=0; i<allConfig.size();i++)
        {
            preferences_out << "0";
        }
        preferences_out.close();
    }
}

void WindowConfig::applyConfig()
{
    r720x480 = allConfig[startOfRes];
    r960x600 = allConfig[startOfRes+1];
    r1024x768 = allConfig[startOfRes+2];
    r1360x768 = allConfig[startOfRes+3];
    fullscreen = allConfig[1];

    if(r720x480) {window_x = 720; window_y = 480;}
    if(r960x600) {window_x = 960; window_y = 600;}
    if(r1024x768) {window_x = 1024; window_y = 768;}
    if(r1360x768) {window_x = 1360; window_y = 768;}

    resolution.width=window_x;
    resolution.height=window_y;

    if(fullscreen) {style = sf::Style::Fullscreen;}


}

void WindowConfig::randomiseTitle()
{
    string line;
    ifstream prefix_data ("./data/prefix.dat");
    if (prefix_data.is_open())
    {
        while ( getline (prefix_data,line) )
        {

            prefixes.push_back(line);
        }
    }
    ifstream suffix_data ("./data/suffix.dat");
    if (suffix_data.is_open())
    {
        while ( getline (suffix_data,line) )
        {
            suffixes.push_back(line);
        }
    }
    /*typedef boost::mt19937 RNGType;
    RNGType rng(time(0));
    RNGType rng2(time(0));
    boost::uniform_int<> pref_int( 0, prefixes.size() -1);
    boost::variate_generator< RNGType, boost::uniform_int<> > rand_pref(rng, pref_int);
    boost::uniform_int<> suff_int( 0, suffixes.size() -1);
    boost::variate_generator< RNGType, boost::uniform_int<> > rand_suff(rng2, suff_int);*/


    int pre_num = maths.randomInt(0,prefixes.size()-1);
    int suff_num = maths.randomInt(0,suffixes.size()-1);

    title= "stop crashing";

    title = "Barbarian Quest II: The " + prefixes[pre_num] + " of the " + suffixes[suff_num];
    return;

}
