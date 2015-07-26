#include "player.h"

Player::Player() : DynamicContent()
{
    //ctor
    basemass = 10;
    absMaxSpeed = 600;
    absRootMaxSpeed = sqrt(0.5)*absMaxSpeed;
    maxSpeed = absMaxSpeed;
    rootMaxSpeed = absRootMaxSpeed;
    velocity.x = 0;
    velocity.y = 0;
    facing = 0;
    move_up = sf::Keyboard::W;
    move_down = sf::Keyboard::S;
    move_left = sf::Keyboard::A;
    move_right = sf::Keyboard::D;
    attack_key =sf::Keyboard::Period;
    animFPS = 16;
    setOrigin(35,45);
    sf::Vector2f nullVec(8,0);
    objHitbox.addCircularHitbox(nullVec,16);
    objHitbox.addRectangularHitbox(nullVec,13,13);
    objHitbox.makeSolid();
    setMass(basemass);
    acceleration = 2.5*maxSpeed;
    //diagacceleration = sqrt(0.5)*acceleration;

    content_id += "_player";

    destructable = true;
    maxhealth = 6;
    health = 6;

    shadowString = "heroshadow";

    //spriteAddresses.push_back("maleBarb_feet");
    //feet_layer = spriteAddresses.size()-1;
    spriteAddresses.push_back("all_barb");
    body_layer = spriteAddresses.size()-1;
    /*spriteAddresses.push_back("maleBarb_weapon");
    weapon_layer = spriteAddresses.size()-1;*/
    //spriteAddresses.push_back("maleBarb_head");
    //head_layer = spriteAddresses.size()-1;

    setElevation(0);

}

Player::~Player()
{
    //dtor
}

void Player::notInContact()
{
    mass = basemass;
    maxSpeed = absMaxSpeed;
    rootMaxSpeed = absRootMaxSpeed;
}

vector<Content*> Player::returnChildren()
{
    vector<Content*> children;
    children.push_back(equippedWeapon);
    return(children);
}

void Player::setTexture(const sf::Texture & in_Tex)
{
    Animation playerSprite;

    playerSprite.setSpriteSheet(in_Tex);
    playerSprite.addReel(0,0,72,70,7,"down_static");
    playerSprite.addReel(72,0,72,70,7,"up_static");
    playerSprite.addReel(144,0,72,70,7,"right_static");
    playerSprite.addReel(216,0,72,70,7,"left_static");
    playerSprite.setFPS(animFPS);
    objSprite.addLayer(playerSprite);
    heroSprite = &objSprite.layers[0];
    return;
}

void Player::setManager(ResourceManager* manager)
{
    assets = manager;
    setMaths(&manager->maths);
}


void Player::allocateAssets()
{
    Animation playerSprite;

    int headsize = 72;
    int bodysize = 72;
    int feetsize = 72;
    int weapsize = 72;
    sf::Vector2u sizeOfSheet;
    int framenum;

    /*objSprite.addLayer(assets->getTex(spriteAddresses[feet_layer]));
    sizeOfSheet = objSprite.layers.back().getSheetSize();
    framenum = sizeOfSheet.y/feetsize;

    objSprite.layers.back().addReel(0,0,feetsize,feetsize,framenum,"down_feet");
    objSprite.layers.back().addReel(70,0,feetsize,feetsize,framenum,"up_feet");
    objSprite.layers.back().addReel(140,0,feetsize,feetsize,framenum,"right_feet");
    objSprite.layers.back().addReel(210,0,feetsize,feetsize,framenum,"left_feet");
    objSprite.layers.back().setFPS(animFPS);*/

    objSprite.addLayer(assets->getTex(spriteAddresses[body_layer]));
    sizeOfSheet = objSprite.layers.back().getSheetSize();
    framenum = sizeOfSheet.y/bodysize;

    objSprite.layers.back().addReel(0,0,bodysize,bodysize,framenum-1,"down_body");
    objSprite.layers.back().addReel(72,0,86,bodysize,framenum-1,"up_body");
    objSprite.layers.back().addReel(226,0,62,bodysize,framenum,"right_body");
    objSprite.layers.back().addReel(156,0,62,bodysize,framenum,"left_body");
    objSprite.layers.back().changeReel(0);
    objSprite.layers.back().setFPS(animFPS);

    /*objSprite.addLayer(assets->getTex(spriteAddresses[weapon_layer]));
    sizeOfSheet = objSprite.layers.back().getSheetSize();
    framenum = sizeOfSheet.y/weapsize;

    objSprite.layers.back().addReel(0,0,weapsize,weapsize,framenum,"down_body");
    objSprite.layers.back().addReel(70,0,weapsize,weapsize,framenum,"up_body");
    objSprite.layers.back().addReel(140,0,weapsize,weapsize,framenum,"right_body");
    objSprite.layers.back().addReel(210,0,weapsize,weapsize,framenum,"left_body");
    objSprite.layers.back().changeReel(0);
    objSprite.layers.back().setFPS(animFPS);*/

    setWeapon(new BaseAxe);
    //equippedWeapon.initialiseWeapon(this);

    //objSprite.addLayer(equippedWeapon.objSprite.layers[0]);

    /*objSprite.addLayer(assets->getTex(spriteAddresses[head_layer]));
    sizeOfSheet = objSprite.layers.back().getSheetSize();
    framenum = sizeOfSheet.y/headsize;

    objSprite.layers.back().addReel(0,0,headsize, headsize,4,"down_head");
    objSprite.layers.back().addReel(headsize,0,headsize, headsize,4,"up_head");
    objSprite.layers.back().addReel(2*headsize,0,headsize, headsize,4,"right_head");
    objSprite.layers.back().addReel(3*headsize,0,headsize, headsize,4,"left_head");
    objSprite.layers.back().changeReel(0);
    objSprite.layers.back().setFPS(animFPS);*/

    heroSprite = &objSprite.layers[0];

    initialiseShadow();

    return;
}



void Player::passKeyBoardInput(vector<bool> input)
{
    int d = 0;
    int u = 1;
    int l = 2;
    int r = 3;

    bool down = input[d];
    bool up = input[u];
    bool left = input[l];
    bool right = input[r];

    bool horiz = left || right;
    bool vertic = up || down;
    bool any = up || down || left || right;
    float x_axis = 0;
    float y_axis = 0;
    sf::Vector2f dir;

    if(any)
    {
        objSprite.playLayer(body_layer);
    }

    if(!any)
    {
        objSprite.stopLayer(body_layer);
    }
    if(down && up)
    {

    }
    if(left && right)
    {

    }
    if(up)
    {
        y_axis -= 1;
    }
    if(down)
    {
        y_axis += 1;
    }
    if(left)
    {
        x_axis -= 1;
    }
    if(right)
    {
        x_axis += 1;
    }


    dir.x = x_axis;
    dir.y = y_axis;

        /*if(dir.y > 0)
        {
            facing = 0;
        }
        if(dir.y < 0)
        {
            facing = 1;
        }
        if(dir.x > 0)
        {
            facing = 2;
        }
        if(dir.x < 0)
        {
            facing = 3;
        }*/
    if(fabs(dir.y) > fabs(dir.x))
    {
        if(dir.y > 0)
        {
            facing = 0;
        }
        if(dir.y < 0)
        {
            facing = 1;
        }
    }
    if(fabs(dir.y) < fabs(dir.x))
    {
        if(dir.x > 0)
        {
            facing = 2;
        }
        if(dir.x < 0)
        {
            facing = 3;
        }
    }


    sf::Vector2f newimp = maths->constantMag(acceleration, dir);

    if(maths->magnitude(velocity + recipmass*newimp) <= maxSpeed)
    {
        impulse += newimp;
    }
    if(maths->magnitude(velocity + recipmass*newimp) > maxSpeed)
    {
        sf::Vector2f idealSpeed = maths->constantMag(maxSpeed,velocity + recipmass*newimp);
        velocity = idealSpeed;
    }



    if(sf::Keyboard::isKeyPressed(attack_key))
    {
        equippedWeapon->startAttack();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        setElevation(getElevation() + 5);
    }
    else if(getElevation() > 0)
    {
        setElevation(getElevation() - 6);
    }
}



void Player::Move(sf::Vector2f amount)
{
    moved = true;
    setPosition(objPosition + amount);
    equippedWeapon->setElevation(elevation);
    equippedWeapon->setPosition(getPosition());
    return;
}


vector<sf::Keyboard::Key> Player::getKeyMap()
{
    vector<sf::Keyboard::Key> keyMap;
    keyMap.push_back(move_down);
    keyMap.push_back(move_up);
    keyMap.push_back(move_left);
    keyMap.push_back(move_right);

    return keyMap;
}

void Player::setKeyMap(vector<sf::Keyboard::Key> keyConfig)
{
    //if(keyConfig.size() < 4) {cout << "key configuration set up incorrectly, returning to defaults"; return;}
    move_down = keyConfig[0];
    move_up = keyConfig[1];
    move_left = keyConfig[2];
    move_right = keyConfig[3];

    return;
}

void Player::setWeapon(Weapon* newWep)
{
    equippedWeapon = newWep;
    equippedWeapon->setManager(assets);
    equippedWeapon->initialiseWeapon(this);
}

void Player::animate()
{
    int i;
    for(i=0; i<objSprite.layers.size(); i++)
    {
        objSprite.layers[i].changeReel(facing);
    }
}

void Player::animate(sf::Time elapsed, bool loop)
{
    int i;
    if(facing == 2)
    {
        //objSprite.setLayerRenderPriority(weapon_layer,1);
    }
    else
    {
        //objSprite.setLayerRenderPriority(weapon_layer,0);
    }
    for(i=0; i<objSprite.layers.size(); i++)
    {
        objSprite.layers[i].changeReel(facing);
        equippedWeapon->objSprite.layers[0].changeReel(facing);
        //objSprite.layers[0].Animate();//facing,elapsed,loop);
    }

}

void Player::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
    equippedWeapon->setElevation(elevation);
    equippedWeapon->setPosition(getPosition());
    equippedWeapon->update();
}


void Player::updateDebug()
{
    objHitbox.update();
}

void Player::hits(Content * Object)
{
    if(Object->locked)
    {
        Object->unlock();
    }
    if(Object->idContains("key"))
    {
        keys++;
    }
    if(Object->idContains("ball"))
    {

    }
    if(Object->idContains("wall"))
    {



    }
    if(Object->movable)
    {
        float ang = maths->angleBetween(velocity,Object->getPosition() - getPosition());
        float magI = 0.5*Object->mass*recipmass*ang;
        Object->impulse.x += magI*velocity.x;
        Object->impulse.y += magI*velocity.y;
        impulse.x -= magI*velocity.x;
        impulse.y -= magI*velocity.y;
    }

}

void Player::isHitBy(Content* Object)
{

}


