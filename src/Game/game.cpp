#include "game.h"




Game::Game()
{
    //ctor
    contentManager.setEventHandler(&eventHandler);


    numberofplayers = 1;
    numberoflevels = 1;
    currentlevel = 0;
    players.resize(numberofplayers);
    levels.resize(numberoflevels);
    keyMaps.resize(numberofplayers);
    prefactor = 0.015625;

    drawchunks = false;
    toggleChunks = false;
    toggleTerminal = false;
    controlsActive = true;
    terminal = true;
    renderRange = 800;
    wasdKeyPresses.resize(4);

    debugger.setFont(gameFiles.getFont("pix"));
    terminalText.setFont(gameFiles.getFont("pix"));
    terminalText.setCharacterSize(18);


    hitboxMode = false;
    debugMode = true;
    noClip = false;
    toggleNewGame = false;
    fullscreen = false;
    quit = false;

    acceptingInput = false;
    returnKeyReleased = false;
    controlsActive = true;

    avgFPS = 0;

    p1 = &players[0];

    printDebug = true;

}

Game::~Game()
{
    //dtor
}

void Game::addText(sf::String addThis)
{
/*    if(addThis == "\b")
    {
        terminalBuffer = terminalBuffer.substr(0,terminalBuffer.size()-1);
    }
    if(addThis != "\b" && addThis != "\n" && addThis != "\r")
    {
        terminalBuffer += addThis;
    }*/
}

void Game::update()
{
    int i,j;
    bool anyKey;
    bool read = true;

    string report = "";



    gameTimer = gameClock.getElapsedTime();
    fpsTimer = fpsClock.restart();
    delta = fpsTimer.asSeconds();


    current_fps = (1.0/fpsTimer.asSeconds());

    report += "lastframeFPS {";
    report += boost::lexical_cast<string>(current_fps);
    report += "ms}; ";

    debugTimer = debugClock.getElapsedTime();
    report += "drawing {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();
    setDelta();

/*    terminalText.setString("");
    controlsActive = true;

    if(!acceptingInput)
    {
        terminalBuffer.clear();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && terminal && !acceptingInput && returnKeyReleased)
    {
        acceptingInput = true;
        returnKeyReleased = false;
    }

    if(acceptingInput)
    {
        controlsActive = false;
        terminalText.setString(terminalBuffer + "_");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && returnKeyReleased)
        {
            eventHandler.newScript(terminalBuffer);
            terminalBuffer.clear();
            acceptingInput = false;
            returnKeyReleased = false;
        }
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        returnKeyReleased = true;
    }*/

    runningFpsAvg.push_back(current_fps);

    int fpsRes = 10;

    if(runningFpsAvg.size()==fpsRes)
    {
        float totalfps = 0;
        for(i=0;i<runningFpsAvg.size();i++)
        {
            totalfps += runningFpsAvg[i];
        }
        avgFPS = totalfps/fpsRes;
        runningFpsAvg.clear();
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && !toggleDebug)
    {
        debugMode = !debugMode;
        toggleDebug = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && toggleDebug)
    {
        toggleDebug = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && !toggleHitbox)
    {
        hitboxMode = !hitboxMode;
        levels[currentlevel].setHitboxMode(hitboxMode);
        for(i=0; i<players.size(); i++)
        {
            players[i].drawHitbox = hitboxMode;
        }
        for(i=0; i<playerMetaContent.size(); i++)
        {
            playerMetaContent[i]->drawHitbox = hitboxMode;
        }
        toggleHitbox = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && toggleHitbox)
    {
        toggleHitbox = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5) && !toggleNoClip)
    {
        noClip = !noClip;
        toggleNoClip = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F5) && toggleNoClip)
    {
        toggleNoClip = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6) && !toggleChunks)
    {
        drawchunks = !drawchunks;
        toggleChunks = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F6) && toggleChunks)
    {
        toggleChunks = false;
    }

    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::F7) && !toggleTerminal)
    {
        terminal = !terminal;
        toggleTerminal = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F7) && toggleTerminal)
    {
        toggleTerminal = false;
    }*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !toggleNewGame)
    {
        restart();
        toggleNewGame = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && toggleNewGame)
    {
        toggleNewGame = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && !toggleFullscreen)
    {
        fullscreen = !fullscreen;
        toggleFullscreen = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && toggleFullscreen)
    {
        toggleFullscreen = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && !toggleQuit)
    {
        quit = true;
        toggleQuit = true;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && toggleQuit)
    {
        toggleQuit = false;
    }

    if(controlsActive)
    {

        for(i=0; i<numberofplayers; i++)
        {
            wasdKeyPresses[0] = sf::Keyboard::isKeyPressed(keyMaps[i][0]);
            wasdKeyPresses[1] = sf::Keyboard::isKeyPressed(keyMaps[i][1]);
            wasdKeyPresses[2] = sf::Keyboard::isKeyPressed(keyMaps[i][2]);
            wasdKeyPresses[3] = sf::Keyboard::isKeyPressed(keyMaps[i][3]);

            anyKey = wasdKeyPresses[0] || wasdKeyPresses[1] || wasdKeyPresses[2] || wasdKeyPresses[3];

            players[i].passKeyBoardInput(wasdKeyPresses);

        }
    }




    for(i=0; i<players.size(); i++)
    {
        players[i].animate(gameTimer,true);
        players[i].update();
    }

    int k,l;
    levels[0].updateWindowInfo(currentView.getCenter());

    debugTimer = debugClock.getElapsedTime();
    report += "player update {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    levels[0].updateRooms();

    debugTimer = debugClock.getElapsedTime();
    report += "room updates {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    if(!noClip)
    {
        gamePhysicsEngine.loopOverOneVector(&players[0],allNPContent);

        debugTimer = debugClock.getElapsedTime();
        report += "player physics {";
        report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
        report += "ms}; ";
        debugClock.restart();

        gamePhysicsEngine.loopOverOneVector(playerMetaContent[0],allNPContent);

        debugTimer = debugClock.getElapsedTime();
        report += "player meta physics {";
        report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
        report += "ms}; ";
        debugClock.restart();

        for(i=0; i<allNPContent.size(); i++)
        {
            if(allNPContent[i]->objRays.getSize() == 0) {continue;}
            for(j=0; j<allNPContent[i]->objRays.getSize(); j++)
            {
                    for(l=0; l<allNPContent[i]->objRays.rays[j].baseRay.getVertexCount(); l++)
                    {
                        if(gamePhysicsEngine.checkCollision(allNPContent[i]->objRays.rays[k].baseRay[l].position,&players[0].objHitbox))
                        {
                            allNPContent[i]->objRays.rays[k].baseRay.resize(l+1);
                            allNPContent[i]->detects(&players[0]);
                        }
                    }
            }
        }

        debugTimer = debugClock.getElapsedTime();
        report += "rays { ";
        report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
        report += " }; ";
        debugClock.restart();

    }




    populateAllContent();

    debugTimer = debugClock.getElapsedTime();
    report += "content population {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    gameRenderEngine.updateContentList(allNPContent,currentView.getCenter());

    debugTimer = debugClock.getElapsedTime();
    report += "content updates {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    gameRenderEngine.appendNewContent(&players[0]);
    for(i=0; i<playerMetaContent.size(); i++)
    {
        gameRenderEngine.appendNewContent(playerMetaContent[i]);
    }

    debugTimer = debugClock.getElapsedTime();
    report += "player appending {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    gameRenderEngine.sortContent();

    debugTimer = debugClock.getElapsedTime();
    report += "sprite sorting {";
    report += boost::lexical_cast<string>(debugTimer.asMilliseconds());
    report += "ms}; ";
    debugClock.restart();

    debug.println(report);

    return;
}

bool Game::requestQuit()
{
    return(quit);
}

bool Game::requestFullscreen()
{
    return(fullscreen);
}

void Game::setDungeonTextures(int levelNumber, const sf::Texture & floorsheet)
{
    levels[levelNumber].setBasicFloorSheet(floorsheet);


}

Player* Game::getPlayerData(int playernumber)
{
    if(playernumber < 0 || playernumber > numberofplayers-1)
    {
        debug.println("no such player, returning player one");
        return &players[0];
    }
    return &players[playernumber];
}

float Game::getDelta()
{
    return(fpsTimer.asSeconds());
}

void Game::setDelta()
{
    int i,j;
    if(avgFPS != 0)
    {
        delta = 1/avgFPS;
    }
    else
    {
        delta = 0.0167;
    }
    levels[currentlevel].updateDelta(delta);
    for(i=0; i<players.size(); i++)
    {
        players[i].setDelta(delta);
    }
    for(i=0; i<playerMetaContent.size(); i++)
    {
        playerMetaContent[i]->setDelta(delta);
    }
}

sf::Vector2f Game::getWindowPosition()
{
    sf::Vector2f pos;
    if(numberofplayers == 1)
    {
        pos.x = maths.round(p1->getPosition().x);
        pos.y = maths.round(p1->getPosition().y);

        return pos;
    }

    //add behaviours for multiplayer camera controls here.
}

void Game::endAndClean()
{
    levels.clear();
    players.clear();
    playerMetaContent.clear();
}

void Game::restart()
{
    endAndClean();
    gameClock.restart();
    players.resize(numberofplayers);
    p1 = &players[0];
    levels.resize(numberoflevels);
    loadNew();
}

void Game::loadNew()
{
    int i,j;
    srand(time(NULL));
    gameRenderEngine.setRenderRange(renderRange);

    p1->setManager(&gameFiles);
    p1->allocateAssets();

    p1->setPosition(6*64,6*64);
    playerMetaContent = p1->returnChildren();
    vector<Content*> playerAll;
    playerAll.push_back(p1);
    playerAll.insert(playerAll.begin(), playerMetaContent.begin(), playerMetaContent.end());




    levels[0].setManager(&gameFiles);
    levels[0].setPhysics(&gamePhysicsEngine);
    levels[0].setEventHandler(&eventHandler);
    levels[0].players.push_back(p1);

    levels[0].addBasicRoom(-20,35,20,20);
    levels[0].addBasicRoom(-15,-15,30,25);
    levels[0].addBasicRoom(-10,-5,40,4);
    levels[0].addBasicRoom(-10,-5,4,45);
    levels[0].addBasicRoom(35,-15,24,20);
    levels[0].addBasicRoom(-10,20,4,40);
    levels[0].addBasicRoom(30,9,24,20);
    levels[0].addBasicRoom(20,-20,40,4);
    levels[0].addBasicRoom(20,-20,4,10);
    levels[0].addBasicRoom(31,-15,10,4);
    levels[0].addBasicRoom(30,-30,20,20);

    /*levels[0].addBasicRoom(5,5,16,4);
    levels[0].addBasicRoom(0,-15,12,5);
    levels[0].addBasicCircularRoom(-5,-25,7);
    levels[0].addBasicRoom(9,12,4,25);
    levels[0].addBasicRoom(-5,-5,10,15);
    levels[0].addBasicRoom(26,5,20,4);
    levels[0].addBasicRoom(9,5,4,25);*/

    /*levels[0].addObject(0,0,5);

    levels[0].addObject(2,2,8);

    levels[0].addObject(5,2,3);

    levels[0].addObject(5,-2,6);

    levels[0].addObject(2,-2,2);*/

    //levels[0].addObject(4,-2,9);


    /*for(i=3; i<6; i++)
    {
        for(j=6; j<12; j++)
        {
            levels[0].addObject(i,j,9);
        }
    //levels[0].addObject(-5,-5,4);
    //levels[0].addObject(-4,-5,4);
    }*/


    for(i=0; i<5; i++)
    {
        for(j=-5; j<5; j++)
        {
            //levels[0].addObject(i,j,4);
        }
    //levels[0].addObject(-5,-5,4);
    //levels[0].addObject(-4,-5,4);
    }


    levels[currentlevel].populateTileSheet();


    for(i=-10; i<10; i++)
    {
        for(j=-10; j<10; j++)
        {
            //levels[0].addObject(i,j,1);
        }
    }

    for(i=0; i<12; i++)
    {
        //levels[0].addObject(2*i - 14,-15,6);
    }

    for(i=-15; i<0; i++)
    {
        for(j=-15; j<5; j++)
        {
            int obj = 3+rand()%6;
            levels[0].addObject(i,j,obj);
        }
    }

    levels[0].addHorizDoor(-10,15,0);
    levels[0].addHorizDoor(20,0,0);
    levels[0].addHorizDoor(20,-7,0);
    levels[0].addHorizDoor(20,19,0);
    levels[0].addHorizDoor(-10,32,0);

    levels[0].addVertDoor(11,-6,0);
    levels[0].addVertDoor(29,-6,0);
    levels[0].addVertDoor(28,19,0);
    levels[0].addVertDoor(-6,19,0);
    levels[0].addVertDoor(29,-21,0);


    levels[currentlevel].updateChunkObjects();

    populateAllContent();

    gameRenderEngine.populateContentList(allContent,currentView.getCenter());


    return;
}

void Game::populateAllContent()
{

    vector<Content*> levelIterator;
    allContent.erase(allContent.begin(),allContent.end());
    int i,j;
    for(i=0; i<levels.size(); i++)
    {
        levelIterator = levels[i].returnAllContent();
        allContent.insert(allContent.end(),levelIterator.begin(),levelIterator.end());
    }
    allNPContent = allContent;
    allContent.push_back(&players[0]);
    playerMetaContent = players[0].returnChildren();
    allContent.insert(allContent.end(),playerMetaContent.begin(),playerMetaContent.end());
}

void Game::updateViewInfo(const sf::View & currentwindow)
{
    debugger.setP1pos(players[0].getPosition());
    debugger.setP1velocity(players[0].adjustedVelocity);
    debugger.setFPS(avgFPS);
    sf::Vector2f tempTileVector;
    sf::Vector2f terminalPos;
    sf::Vector2f tempPosVector = players[0].getPosition();

    tempTileVector.x = floor(prefactor*tempPosVector.x);
    tempTileVector.y = floor(prefactor*tempPosVector.y);
    debugger.setP1tile(tempTileVector);


    debugger.setP1chunk(levels[0].getParentChunkIndex(&players[0]));

    sf::Vector2f sizeOfWindow, positionOfWindow;
    currentView = currentwindow;
    sizeOfWindow = currentwindow.getSize();
    positionOfWindow = currentwindow.getCenter();
    debuggerPosition.x = positionOfWindow.x - 0.5*sizeOfWindow.x;
    debuggerPosition.y = positionOfWindow.y - 0.5*sizeOfWindow.y;
    terminalPos.x = positionOfWindow.x - 0.475*sizeOfWindow.x;
    terminalPos.y = positionOfWindow.y + 0.45*sizeOfWindow.y;
    debugger.update();
    debugger.setPosition(debuggerPosition);

    terminalText.setPosition(terminalPos);

    levels[currentlevel].updateWindowInfo(positionOfWindow);
    return;
}

void Game::start()
{
    int i;
    for(i=0; i<numberofplayers; i++)
    {
        keyMaps[i] = players[i].getKeyMap();
    }

    return;
}

void Game::stop()
{

    return;
}

void Game::pause()
{

    return;
}

void Game::resume()
{

    return;
}


