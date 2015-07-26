#include <Base Content/content.h>

Content::Content()
{
    //ctor
    drawHitbox = false;
    content_id = "";
    rotation = 0;
    content_type = "null";
    delta = 1/60;

    hasChunk = false;

    objParticles.setRadius(10);
    objParticles.setImpulseRange(0,0,0,0,0,0);
    objParticles.setLifetimeRange(0,1);
    objParticles.setParticleSizeRange(1,1);

    parentChunkIndex.x = parentChunkIndex.y = 0;

    rotationSpeed = 0;

    frameDiff = 0;

    shadowString = "null";
    moved = true;
    showShadow = false;
    stopsRays = false;
    friction = 100;

    renderPriority = 0;

    velocity.x = 0;
    velocity.y = 0;

    origin.x = 0;
    origin.y = 0;

    elevation = 0;

    movable = false;
    dynamic = false;
    impassable = false;
    destructable = false;
    inert = false;
    solid = false;

    blocksLOS = false;

    render = true;

    locked = false;

    wall = false;
    dead = false;

    acceleration = 0;
    diagacceleration = 0;

    objHitbox.parent = this;
    destroyMe = false;
    inertForThisLong = 0;
    airForThisLong = 0;
    mass = 0;
    basemass = 0;
    recipmass = 0;
    impulse.x = 0;
    impulse.y = 0;
    particleOffset.x = 0;
    particleOffset.y = 0;
    oneOverSixty = 1/60;
    setOrigin(0,0);
}

Content::~Content()
{
    //dtor
}

void Content::bind()
{
    hasChunk = true;
}

void Content::free()
{
    hasChunk = false;
}

bool Content::isBound()
{
    return(hasChunk);
}

void Content::setEventHandler(EventHandler* newEvents)
{
    events = newEvents;
}

void Content::setMaths(fastMaths* overMaths)
{
    maths = overMaths;
}

void Content::initialiseShadow()
{
    shadow.setSpriteSheet(assets->getTex(shadowString));
    shadow.centreOrigin();
    //shadow.setPosition(0.5*objSprite.getBounds().x, 0.5*objSprite.getBounds().y);
    setPosition(getPosition());
    showShadow = true;
}

void Content::addLinkedTile(int tilex, int tiley)
{
    sf::Vector2i tilepos(tilex, tiley);
    linkedTiles.push_back(tilepos);
}

void Content::setParentChunkIndex(sf::Vector2i ind)
{
    parentChunkIndex = ind;
}

void Content::setParentChunkIndex(int g_x, int g_y)
{
    sf::Vector2i inde(g_x,g_y);
    setParentChunkIndex(inde);
}

void Content::setMass(float newMass)
{
    basemass = newMass;
    mass = newMass;
    recipmass = 1/mass;
    friction = mass*500;
}

void Content::makeInert(float forthislong)
{
    inertClock.restart();
    inertForThisLong = forthislong;
}

void Content::increaseMaxHealth(int amount)
{
    if(!destructable) {return;}
    maxhealth += amount;
}

void Content::damageBy(int amount)
{
    if(!destructable) {return;}
    health -= amount;
    checkHealth();
}

void Content::healBy(int amount)
{
    if(!destructable) {return;}
    if(health > 0)
    {
    health += amount;
    }
}


void Content::makeSolid()
{
    objHitbox.makeSolid();
}

void Content::makeAir()
{
    objHitbox.makeAir();
}

bool Content::idContains(string in_str)
{
    return(content_id.find(in_str) != std::string::npos);
}

void Content::allocateAssets()
{
    int i;
    for(i=0; i<spriteAddresses.size(); i++)
    {
        objSprite.addLayer((assets->getTex(spriteAddresses[i])));
        //objSprite.layers.back().changeReel(0);
        objSprite.layers.back().setFPS(animFPS);

        //objSprite.layers.back().splitStaticSheet(objSprite.layers.back().getSize().x, objSprite.layers.back().getSize().y);
        //objSprite.layers.back().update();
    }

    if(shadowString != "null")
    {
        initialiseShadow();
    }
    setPosition(objPosition);

}

void Content::initialiseAssets(ResourceManager* manager)
{
    setManager(manager);
    setMaths(&(manager->maths));
    allocateAssets();
    extraAllocations();
}


void Content::setLocalPosition(int xpos, int ypos)
{
    roomMapPosition.x = xpos;
    roomMapPosition.y = ypos;
    relPosition.x = xpos*64;
    relPosition.y = ypos*64;

}

void Content::setGlobalPosition(int xpos, int ypos)
{
    mapPosition.x = xpos;
    mapPosition.y = ypos;
    appPosition.x = xpos*64;
    appPosition.y = ypos*64;
    objPosition = appPosition;
    setPosition(appPosition);
}

void Content::setParentRoomPosition(int xpos, int ypos)
{
    roomPosition.x = xpos;
    roomPosition.y = ypos;
    setGlobalPosition(xpos+roomMapPosition.x, ypos + roomMapPosition.y);
}

CompoundHitbox* Content::getHitbox()
{
    return(&objHitbox);
}

float Content::getMass()
{
    return mass;
}

void Content::alterVelocity(sf::Vector2f amount)
{
    velocity += amount;
}

void Content::setVelocity(sf::Vector2f new_vel)
{
    velocity = new_vel;
}

void Content::setContact(bool in_con)
{
    inContact = in_con;
    objHitbox.inContact = in_con;
}

void Content::setImmovable(bool isImmovable)
{
    movable = !isImmovable;
    if(!movable)
    {
        objHitbox.setColor(sf::Color::Green);
    }
    else
    {
        objHitbox.setColor(sf::Color::White);
    }
}

void Content::notInContact()
{

}

bool Content::isSolid()
{
    return(objHitbox.solid);
}

bool Content::isImpassable()
{
    return impassable;
}

int Content::getRenderPriority()
{
    return(renderPriority);
}

void Content::Move(sf::Vector2f amount)
{
    setPosition(objPosition + amount);
    moved = true;
    return;
}

void Content::Move(float dx, float dy)
{
    sf::Vector2f amount(dx,dy);
    Move(amount);
    return;
}

sf::Vector2f Content::getPosition()
{
    return objPosition;
}

float Content::getElevation()
{
    return(elevation);
}

void Content::setPosition(sf::Vector2f newPosition)
{
    elevatedPosition.x = newPosition.x;
    elevatedPosition.y = newPosition.y - elevation;
    objSprite.setPosition(elevatedPosition);
    objHitbox.setPosition(elevatedPosition);
    if(showShadow)
    {
        shadow.setPosition(newPosition.x, newPosition.y);
    }
    objParticles.setPosition(newPosition + particleOffset);
    objRays.setPosition(newPosition);
    objPosition = newPosition;
}

sf::Vector2f Content::getOrigin()
{
    sf::Vector2f ret_orig;
    ret_orig = origin;
    return(ret_orig);
}

void Content::Rotate(float amount)
{
    int i;
    rotation += amount;
    objSprite.Rotate(amount);
    float sin = maths->SinDeg(rotation);
    float cos = maths->CosDeg(rotation);
    sf::Vector2f offset = origin - objSprite.getPosition();
    float magoff = maths->magnitude(offset);
    sf::Vector2f moveby;
    moveby.x = sin*magoff;
    moveby.y = cos*magoff;
    //objSprite.Move(moveby);
    for(i=0; i<objHitbox.circs.size(); i++)
    {
        sf::Vector2f diff = objHitbox.circs[i].getRelativePosition();
        float magdiff = maths->magnitude(diff);
        sf::Vector2f newNull;
        newNull.x = sin*magdiff;
        newNull.y = -cos*magdiff;
        objHitbox.circs[i].setRelativePosition(newNull);
    }
}

void Content::detects(Content* obj)
{

}

void Content::setOrigin(sf::Vector2f new_origin)
{
    origin = new_origin;
    objSprite.setOrigin(new_origin);
    //objHitbox.setLocalPosition(new_origin);
    setPosition(objPosition);
}

void Content::moveOrigin(sf::Vector2f amount)
{
    sf::Vector2f current_origin = getOrigin();
    setOrigin(current_origin+amount);
}

void Content::moveOrigin(float dx,float dy)
{
    sf::Vector2f amount;
    amount.x = dx;
    amount.y = dy;
}

void Content::shiftFromOrigin(sf::Vector2f amount)
{
    sf::Vector2f current_origin = getOrigin();
    objSprite.setOrigin(current_origin + amount);
    setPosition(objPosition);
}

void Content::shiftFromOrigin(float dx, float dy)
{
    sf::Vector2f amount;
    amount.x = dx;
    amount.y = dy;
    shiftFromOrigin(amount);
}




void Content::setOrigin(float x,float y)
{
    sf::Vector2f new_origin(x,y);
    setOrigin(new_origin);
}

void Content::setOriginAsFraction(float frac_x, float frac_y)
{

}

void Content::setPosition(float x, float y)
{
    sf::Vector2f newPos(x,y);
    setPosition(newPos);
}

void Content::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    evolveMovement();
}

void Content::setImpulse(sf::Vector2f newImpulse)
{
    impulse = newImpulse;

}

void Content::makeAir(float thislong)
{
    airClock.restart();
    airForThisLong = thislong;
}


void Content::setDelta(float newdel)
{
    delta = newdel;
}

void Content::updateClocks()
{
    int i;
    adjustedVelocity = delta*velocity;
    adjustedImpulse = delta*impulse;
    objTime = objClock.getElapsedTime();
    inertTime = inertClock.getElapsedTime();
    airTime = airClock.getElapsedTime();
    moved = false;
    if(inertTime.asSeconds() < inertForThisLong)
    {
        inert = true;
    }
    else
    {
        inert = false;
    }
    if(airTime.asSeconds() < airForThisLong)
    {
        makeAir();
    }
    else
    {
        if(solid)
        {
            makeSolid();
        }
    }
    elevate();
    Animate();
    objRays.update();
    objParticles.update();
}

void Content::setElevation(float new_elev)
{
    elevation = new_elev;
}

void Content::elevate()
{

}

void Content::Animate()
{
    int i;
    for(i=0; i<objSprite.layers.size(); i++)
    {
        objSprite.layers[i].Animate();
        objSprite.layers[i].update();
    }
}

void Content::resetFlags()
{
    moved = false;
}

void Content::evolveMovement()
{
    if(!movable && !dynamic) {return;}
    /*if(impulse.x !=0 || impulse.y != 0)
    {
        //Move(adjustedImpulse*recipmass);
        sf::Vector2f unit = maths->unitVector(impulse);
        if(fabs(impulse.x) > delta*friction*fabs(unit.x))
        {
            impulse.x -= delta*(friction)*unit.x;
        }
        else
        {
            impulse.x = 0;
        }
        if(fabs(impulse.y) > delta*friction*fabs(unit.y))
        {
            impulse.y -= delta*(friction)*unit.y;
        }
        else
        {
            impulse.y = 0;
        }
    }*/

    if(velocity.x !=0 || velocity.y != 0)
    {

        //Move(adjustedImpulse*recipmass);
        if(friction > 0)
        {
            sf::Vector2f unit = maths->unitVector(velocity);
            sf::Vector2f fricRed = maths->constantMag(friction, unit);
            if(fabs(fricRed.x) > 0.01)
            {
            if(fabs(velocity.x) > delta*fabs(fricRed.x))
            {
                velocity.x -= delta*fricRed.x;
            }
            else
            {
                velocity.x = 0;
            }
            }
            else
            {
                velocity.x = 0;
            }
            if(fabs(fricRed.y) > 0.01)
            {
            if(fabs(velocity.y) > delta*fabs(fricRed.y))
            {
                velocity.y -= delta*fricRed.y;
            }
            else
            {
                velocity.y = 0;
            }
            }
            else
            {
                 velocity.y = 0;
            }
            }
    }
    velocity += impulse*recipmass;
    impulse.x = 0;
    impulse.y = 0;
    if(rotationSpeed != 0)
    {
        Rotate(rotationSpeed);
    }
    if(velocity.x != 0 || velocity.y != 0 || impulse.x !=0 || impulse.y != 0)
    {
        adjustedVelocity = delta*velocity;
        moved = true;
        Move(adjustedVelocity);
    }
    else
    {
        if(inContact)
        {
            moved = true;
        }
    }
}
