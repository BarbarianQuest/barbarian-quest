#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <System Tools/menu.h>


using namespace std;
using namespace sf;

#include "game.h"

int native_x = 600;
int native_y = 400;
int numRes = 4; //number of resolutions
int numOther = 2; //number of radio buttons
int numStart = 2; //number of start buttons
int numMain = 5; //number of main menu options
int numPause = 3; //number of pause menu options
int numMainOptions = 1; //number of options menu options


int main()
{

    std::ofstream out("log.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::cout << "Hi!";


    //Launcher.display();
    RenderWindow Game_Window;
    View heroview;
    FloatRect viewport;



    Vector2i pos_m; //mouse position
    bool L_m; //left mouse
    bool R_m;//right mouse
    bool m_L, m_R, m_U, m_D; //move left, right, up, down
    bool a_L, a_R, a_U, a_D; //attack left, right, up, down
    bool _r, _t; //activate rage, throw
    bool _esc, _tab, L_shift, R_shift;

    bool active=true; //checks if the window is the active window.

    sf::Clock inputClock;
    sf::Time inputTimer;


    VideoMode screen_info;
    screen_info = VideoMode::getDesktopMode();
    Vector2i central_point, launcher_pos, game_pos;
    central_point.x = 0.5*screen_info.width;
    central_point.y = 0.5*screen_info.height;
    launcher_pos.x = central_point.x - 0.5*native_x;
    launcher_pos.y = central_point.y - 0.5*native_y;

    WindowConfig G_Conf; //the game window configuration
    G_Conf.loadConfig();

    Game game;

    int window_x, window_y;

    ResourceManager cache;

    cache.addDirectory("./assets/mainmenu/");
    cache.addDirectory("./assets/pausemenu/");

    //MENUS SO MANY MENUS

    Menu mainMenu;
    mainMenu.basicConfig(true,0,0,100);
    mainMenu.textConfig(cache.getFont("qest"),38,sf::Text::Bold,sf::Color::Black);
    mainMenu.addBackdrop(cache.getTex("M_Backdrop"));

    mainMenu.addButton(cache.getTex("M_Buttons"),"Start Game");
    mainMenu.addButton(cache.getTex("M_Buttons"),"Options");
    mainMenu.addButton(cache.getTex("M_Buttons"),"Statistics");
    mainMenu.addButton(cache.getTex("M_Buttons"),"Credits");
    mainMenu.addButton(cache.getTex("M_Buttons"),"Quit Game");

    vector<bool> mainOptions;

    Menu optionsMenu;
    optionsMenu.basicConfig(false,0,0,100);
    optionsMenu.textConfig(cache.getFont("qest"),38,sf::Text::Bold,sf::Color::Black);
    optionsMenu.addBackdrop(cache.getTex("M_Backdrop"));

    optionsMenu.addButton(cache.getTex("M_Buttons"),"Controls");
    optionsMenu.addButton(cache.getTex("M_Buttons"),"Audio");
    optionsMenu.addHardButton(cache.getTex("M_Tick_Buttons"),"Gore",true);
    optionsMenu.addButton(cache.getTex("M_Buttons"),"Back");

    vector<bool> optionsOptions; //jesus christ Joel...

    Menu audioMenu;
    audioMenu.basicConfig(false,0,0,100);
    audioMenu.textConfig(cache.getFont("qest"),26,sf::Text::Bold,sf::Color::Black);
    audioMenu.addBackdrop(cache.getTex("O_Backdrop"));
    audioMenu.addSlider(cache.getTex("M_SliderBack"),cache.getTex("M_SliderNub"),100,50,"Music");
    audioMenu.addSlider(cache.getTex("M_SliderBack"),cache.getTex("M_SliderNub"),100,50,"Sounds");
    audioMenu.addButton(cache.getTex("M_Buttons"),"Back");

    vector<bool> audioOptions;

    Menu keyBindMenu;
    keyBindMenu.basicConfig(true,0,0,40);
    keyBindMenu.textConfig(cache.getFont("qest"),24,sf::Text::Bold,sf::Color::Black);
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Move Up","w");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Move Left","a");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Move Right","d");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Move Down","s");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Attack Up","1");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Attack Left","2");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Attack Right","3");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Atack Down","4");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Throw","5");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Rage","e");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Cast","q");
    keyBindMenu.addKeyMap(cache.getTex("O_Keys"),"Pause","6");
    keyBindMenu.addButton(cache.getTex("O_Slim"),"Back");
    keyBindMenu.addBackdrop(cache.getTex("M_Backdrop"));

    vector<bool> keyBindOptions;


    Menu pauseMenu;
    pauseMenu.makeButtons(numPause,true,false,cache.getTex("P_Buttons"),0,0);
    //pauseMenu.addBackdrop(cache.getTex("P_Backdrop"));
    vector<bool> pauseOptions;

    //OKAY NO MORE MENUS

    //Level initialisations!


    if(G_Conf.openLauncher)
    {
        RenderWindow Launcher(sf::VideoMode(native_x, native_y),"BQII Launcher",Style::Close);
        Launcher.setPosition(launcher_pos);


        bool saveConfig,fullscreen,L_startGame,L_quitGame;

        cache.addDirectory("./assets/launcher/");

        //ugly menu initialisations
        Menu resolution;
        resolution.makeButtons(numRes,true,false,cache.getTex("res_banners"),100,145);
        vector<bool> resConfig(numRes);
        resolution.select(1); //selects the default resolution
        vector<string> res_strings(numRes);
        res_strings[0]="720x480";
        res_strings[1]="960x600";
        res_strings[2]="1024x768";
        res_strings[3]="1360x768";
        resolution.textInit(cache.getFont("dum"),22,res_strings);

        Menu otherOptions;
        otherOptions.makeButtons(numOther,false,true,cache.getTex("L_Other"),325,315);
        vector<bool> otherConfig(numOther);

        Menu startExit;
        startExit.makeButtons(numStart,true,true,cache.getTex("L_Start"),500,320);
        vector<bool> startConfig(numStart);

        resolution.open();
        otherOptions.open();
        startExit.open();

        //ugly launcher behaviours :(

        while (Launcher.isOpen()) //Launcher Stuff
        {
            Event L_Event; //events in the launcher window
            pos_m = Mouse::getPosition(Launcher);
            L_m = Mouse::isButtonPressed(Mouse::Left);
            _esc = Keyboard::isKeyPressed(Keyboard::Escape);
            while (Launcher.pollEvent(L_Event))
            {
                // Close window : exit
                if (L_Event.type == Event::Closed)
                    Launcher.close();
            }

            if(_esc)
            {
                Launcher.close();
            }
            /*

            if(L_Event.type == sf::Event::LostFocus)
            {
                active = false;
            }
            if(L_Event.type == sf::Event::GainedFocus)
            {
                active = true;
            }*/

            //if(!active) {continue;}

            resolution.update(pos_m,L_m,"");
            otherOptions.update(pos_m,L_m,"");
            startExit.update(pos_m,L_m,"");

            resConfig = resolution.chosenItem();
            otherConfig = otherOptions.chosenItem();
            startConfig = startExit.chosenItem();

            L_startGame = startConfig[0];
            L_quitGame = startConfig[1];
            saveConfig = otherConfig[0];

            if(L_startGame)
            {
                G_Conf.appendConfig(otherConfig,resConfig);
                if(saveConfig)
                {
                    G_Conf.saveConfig();
                }
                G_Conf.applyConfig();
                Game_Window.create(sf::VideoMode(G_Conf.window_x, G_Conf.window_y),G_Conf.title,G_Conf.style);
                Game_Window.setFramerateLimit(61);
                Game_Window.setVerticalSyncEnabled(false);
                Game_Window.display();
                Launcher.close();
            }

            if(L_quitGame)
            {
                Launcher.close();
            }

            //Draw cycles
            Launcher.clear();

            //draw menus
            Launcher.draw(resolution);
            Launcher.draw(otherOptions);
            Launcher.draw(startExit);
            Launcher.display();
            //Draw cycles end
        }
    }
    else
    {
        G_Conf.applyConfig();
        Game_Window.create(sf::VideoMode(G_Conf.window_x, G_Conf.window_y),G_Conf.title,G_Conf.style);
        Game_Window.setFramerateLimit(61);
        Game_Window.setVerticalSyncEnabled(false);
        Game_Window.display();


        viewport.width = G_Conf.window_x;
        viewport.height = G_Conf.window_y;
    }

    window_x = G_Conf.window_x;
    window_y = G_Conf.window_y;

    mainMenu.open();
    float windowScale_y =( (float) window_y)/600;
    float windowScale_x =( (float) window_y)/600;

    mainMenu.scale(windowScale_x,windowScale_y);
    optionsMenu.scale(windowScale_x,windowScale_x);

    mainMenu.centreMenu(0.2,0.5,window_x,window_y);
    optionsMenu.centreMenu(0.2,0.5,window_x,window_y);
    audioMenu.centreMenu(0.2,0.5,window_x,window_y);
    keyBindMenu.centreMenu(0.2,0.5,window_x,window_y);


    bool gameStart, openOptions, openStats, openCredits, quitGame;
    bool gameIsRunning = false;
    bool gameIsStarted = false;
    bool selectedOnce;
    sf::Clock clickClock;


    pauseMenu.centreMenu(window_x,window_y);

    while(Game_Window.isOpen())
    {

        sf::Time clickTimer = clickClock.getElapsedTime();
        if(selectedOnce)
        {
            clickClock.restart();
        }
        Event G_Event; //events in the game window
        if(G_Event.type == Event::MouseButtonReleased)
        {
            selectedOnce = false;
        }
        pos_m = Mouse::getPosition(Game_Window);
        L_m = (Mouse::isButtonPressed(Mouse::Left) && clickTimer.asSeconds()>0.1 && !selectedOnce);

        _esc = Keyboard::isKeyPressed(Keyboard::Escape);
        while (Game_Window.pollEvent(G_Event))
        {
            // Close window : exit
            if (G_Event.type == Event::Closed)
                Game_Window.close();
        }

        if(mainMenu.isOpen())
        {
            /*if(G_Event.type == sf::Event::LostFocus)
            {
                active = false;
            }
            if(G_Event.type == sf::Event::GainedFocus)
            {
                active = true;
            }*/

            mainMenu.update(pos_m,L_m,"");
            mainOptions = mainMenu.chosenItem();
            gameStart = mainOptions[0];
            openOptions = mainOptions[1];
            openStats = mainOptions[2];
            openCredits = mainOptions[3];
            quitGame = mainOptions[4];
            gameStart = true;

            if(gameStart)
            {
                mainMenu.close();
                gameIsRunning = true;
                selectedOnce = true;
                game.loadNew();
            }

            if(openOptions)
            {
                mainMenu.close();
                optionsMenu.open();
                selectedOnce = true;
            }
            if(openStats)
            {
                //need to do this

            }
            if(openCredits)
            {
                //and this

            }
            if(quitGame)
            {
                Game_Window.close();
            }
            if(_esc)
            {
                Game_Window.close();
                selectedOnce = true;
            }

            Game_Window.clear();
            //Draw cycles
            Game_Window.draw(mainMenu);

            Game_Window.display();
        }

        //check click timings
        if(selectedOnce) {clickClock.restart();}
        L_m = (Mouse::isButtonPressed(Mouse::Left) && clickTimer.asSeconds()>0.1 && !selectedOnce);
        //end timing check

        if(optionsMenu.isOpen())
        {
            optionsMenu.update(pos_m,L_m,"");
            optionsOptions = optionsMenu.chosenItem();
            bool backToMain = optionsOptions.back();
            bool openCtrls = optionsOptions[0];
            bool openAudio = optionsOptions[1];

            if(openAudio)
            {
                optionsMenu.close();
                audioMenu.open();
                selectedOnce = true;
            }

            if(openCtrls)
            {
                optionsMenu.close();
                keyBindMenu.open();
                selectedOnce = true;
            }

            if(backToMain)
            {
                optionsMenu.close();
                mainMenu.open();
                selectedOnce = true;
            }


            Game_Window.clear();
            //Draw cycles
            Game_Window.draw(optionsMenu);

            Game_Window.display();
        }

        //check click timings
        if(selectedOnce) {clickClock.restart();}
        L_m = (Mouse::isButtonPressed(Mouse::Left) && clickTimer.asSeconds()>0.1 && !selectedOnce);
        //end timing check

        if(keyBindMenu.isOpen())
        {
        string keyboardInput;
            if (G_Event.type == sf::Event::TextEntered)
            {
                if (G_Event.text.unicode < 128)
                {
                    keyboardInput = static_cast<char>(G_Event.text.unicode);
                }
            }
            keyBindMenu.update(pos_m,L_m,keyboardInput);
            keyBindOptions = keyBindMenu.chosenItem();
            bool backToOptions = keyBindOptions.back();

            if(backToOptions)
            {
                keyBindMenu.close();
                optionsMenu.open();
                selectedOnce = true;
            }

            Game_Window.clear();
            //Draw cycles
            Game_Window.draw(keyBindMenu);

            Game_Window.display();

        }


        //check click timings
        if(selectedOnce) {clickClock.restart();}
        L_m = (Mouse::isButtonPressed(Mouse::Left) && clickTimer.asSeconds()>0.1 && !selectedOnce);
        //end timing check

        if(audioMenu.isOpen())
        {
            audioMenu.update(pos_m,L_m,"");
            audioOptions = audioMenu.chosenItem();
            bool backToOptions = audioOptions.back();

            if(backToOptions)
            {
                audioMenu.close();
                optionsMenu.open();
                selectedOnce = true;
            }

            Game_Window.clear();
            //Draw cycles
            Game_Window.draw(audioMenu);

            Game_Window.display();

        }

        if(!gameIsRunning) {continue;}
        if(gameIsRunning && !gameIsStarted) {game.start(); gameIsStarted = true;}
        sf::String intoGame;



        inputTimer = inputClock.getElapsedTime();

        if (G_Event.type == sf::Event::TextEntered && inputTimer.asSeconds() > 0.15)
        {
                inputClock.restart();
                if (G_Event.text.unicode < 128)
                intoGame = G_Event.text.unicode;
                game.addText(intoGame);
        }


        game.update();

        if(game.requestQuit())
        {
            Game_Window.close();
        }



        heroview.setSize(G_Conf.window_x, G_Conf.window_y);
        heroview.setCenter(game.getWindowPosition());







        Game_Window.clear();

        Game_Window.draw(game);

        game.updateViewInfo(heroview);


        Game_Window.setView(heroview);

        Game_Window.display();


        //Draw cycles end
    }
}
