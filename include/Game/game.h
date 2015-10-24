#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <Base Content/content.h>
#include <System Tools/resourcemanager.h>
#include "player.h"
#include "dungeon.h"
#include "wall.h"

#include "physicsengine.h"
#include <Functions/fastmaths.h>

#include <System Tools/contentmanager.h>
#include <System Tools/renderengine.h>
#include <Base Content/dynamiccontent.h>
#include <Base Content/staticcontent.h>
#include <System Tools/debugdisplay.h>
#include <System Tools/eventhandler.h>


using namespace std;


class Game : public sf::Drawable
{
    public:
        Game();
        virtual ~Game();

        fastMaths maths;
        DebugTools debug;
        EventHandler eventHandler;
        ContentManager contentManager;



        void loadNew();
        void start();
        void stop();
        void pause();
        void resume();
        void update();
        void updateViewInfo(const sf::View &);
        void populateAllContent();

        void endAndClean();
        void restart();

        float getDelta();
        void setDelta();
        float delta;
        void calculateDelta();

        void addText(sf::String);

        bool requestQuit();
        bool requestFullscreen();

        Player* getPlayerData(int);

        string currentUserInput;
        sf::Text terminalText;

        bool debugMode, hitboxMode, noClip;
        bool toggleDebug, toggleHitbox, toggleNoClip,toggleNewGame;

        bool fullscreen, quit;
        bool toggleFullscreen, toggleQuit;

        bool terminal, toggleTerminal;

        sf::Vector2f getWindowPosition();

        vector <Content*> renderContent;
        vector <Content*> playerMetaContent;

        void setDungeonTextures(int, const sf::Texture &); //this is a strange way of handling floor tiles...
        //might be worth updating this system to be more in tune with the classes I've built since.

        debugDisplay debugger;

    protected:
    private:

        int numberofplayers;
        int numberoflevels;
        int currentlevel;
        float prefactor;

        float renderRange;

        vector<vector<sf::Keyboard::Key> > keyMaps;

        vector<bool> wasdKeyPresses;

        vector<float> runningFpsAvg;


        ResourceManager gameFiles;
        RenderEngine gameRenderEngine;
        PhysicsEngine gamePhysicsEngine;

        vector<Content*> allContent;
        vector<Content*> allNPContent;
        vector<vector<Content*> > zonedContent;
        vector<DynamicContent*> dynContent;
        vector<StaticContent*> statContent;

        sf::Texture testTex;
        sf::Sprite testSpr;

        float current_fps,avgFPS;


        sf::View currentView;
        sf::Vector2f debuggerPosition;

        sf::Clock gameClock,fpsClock,debugClock;
        sf::Time gameTimer, fpsTimer,debugTimer;

        vector<Player> players;

        vector<Dungeon> levels;
        Player* p1;
        bool drawchunks;
        bool toggleChunks;
        bool controlsActive;
        bool acceptingInput;
        bool returnKeyReleased;

        bool printDebug;



        string terminalBuffer;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            int i,j;
            //target.draw(testSpr);
            target.draw(gameRenderEngine);

            for(i=0; i<allContent.size(); i++)
            {
                //target.draw(*allContent[i]);
            }
            //target.draw(levels[currentlevel]);
            for(i=0; i<players.size(); i++)
            {
                //target.draw(players[i]);
            }
            if(drawchunks)
            {
            for(i=0; i<levels[currentlevel].chunks.size(); i++)
            {
                for(j=0; j<levels[currentlevel].chunks[i].size(); j++)
                {
                    if(!levels[currentlevel].chunks[i][j].active){continue;}
                    target.draw(levels[currentlevel].chunks[i][j]);
                }
            }
            }

            //target.draw(levels[currentlevel].testGun);

            if(debugMode)
            {
                target.draw(debugger);
            }
            /*if(terminal)
            {
                target.draw(terminalText);
            }*/
        }

};

#endif // GAME_H
