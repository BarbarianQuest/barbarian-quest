#pragma once

#ifndef CONTENT_H
#define CONTENT_H

#include <SFML/Graphics.hpp>
#include <Functions/debugtools.h>
#include <System Tools/eventhandler.h>
#include <System Tools/resourcemanager.h>
#include <Graphics/animation.h>
#include <Graphics/layeredanimation.h>
#include <Physics/compoundhitbox.h>
#include <Physics/raygun.h>
#include <Physics/particleemitter.h>


using namespace std;

class Content: public sf::Drawable
{
    public:
        Content();
        virtual ~Content();

        std::string alphaTag;

        void generateTag()
        {
            alphaTag = "";
            std::string alphaNum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
            int i;
            for(i=0; i<10; i++)
            {
                alphaTag+=alphaNum[maths->randomInt(0,alphaNum.length())];
            }
        }

        bool blocksLOS;

        DebugTools debug;

        vector<Content*> children;

        void clearChildren()
        {
            children.clear();
        }

        vector<Content*> getChildren()
        {
            return(children);
        }

        bool hasChunk;
        void bind();
        void free();
        bool isBound();

        virtual void trigger()
        {

        }

        void triggerEvent(string);
        void setEventHandler(EventHandler* );

        EventHandler* events;

        ResourceManager* assets;
        vector<string> spriteAddresses;

        vector <sf::Vector2i> linkedTiles;

        sf::Vector2i parentChunkIndex;
        void setParentChunkIndex(sf::Vector2i);
        void setParentChunkIndex(int, int);

        void addLinkedTile(int, int);

        virtual void detects(Content*);

        Animation shadow;
        string shadowString;
        bool showShadow;
        void initialiseShadow();
        void moveShadow(sf::Vector2f);
        void moveShadow(float, float);

        void setMaths(fastMaths*);
        fastMaths* maths;

        LayeredAnimation objSprite;
        CompoundHitbox objHitbox;
        Raygun objRays;
        //CompoundHitbox auraHitbox; //for interactive stuff, must finish
        ParticleEmitter objParticles;
        sf::Vector2f particleOffset;

        bool render;

        void setManager(ResourceManager* manager)
        {
            assets = manager;
            setRayManager();
        }
        void setRayManager()
        {
            objRays.setManager(assets);
        }
        virtual void allocateAssets();
        virtual void initialiseAssets(ResourceManager*);

        bool idContains(string);

        virtual void setTexture(sf::Texture tex)
        {

            objSprite.addLayer(tex);
        }

        CompoundHitbox* getHitbox();

        string content_id;
        string content_type;

        sf::Vector2f objPosition;
        float objRotation;

        sf::Clock objClock;
        sf::Clock inertClock;
        sf::Clock airClock;

        sf::Time objTime;
        sf::Time inertTime;
        sf::Time airTime;

        float inertForThisLong;

        void updateClocks();


        bool drawHitbox;
        bool inContact; //is it in contact with another object

        sf::Vector2i roomPosition; //position of the parent room on the dungeon map

        sf::Vector2f relPosition; //the relative position of the time in the room
        sf::Vector2f appPosition; //apparent position of the tile on the screen
        sf::Vector2i mapPosition; //position of the tile on the dungeon tilemap
        sf::Vector2i roomMapPosition; //position of the tile on the room tilemap

        void setLocalPosition(int, int); //sets the position of the content in the room
        void setGlobalPosition(int, int); //sets the position of the content in the dungeon (should not be used directly)
        void setParentRoomPosition(int, int); //if a room moves, this should be called

        sf::Vector2f origin;

        virtual void evolveMovement();
        virtual void notInContact();
        virtual void hits(Content *)
        {

        }

        void Animate();

        void setPosition(sf::Vector2f);
        void setPosition(float, float);
        virtual void alterVelocity(sf::Vector2f);
        virtual void setVelocity(sf::Vector2f);
        virtual void Move(sf::Vector2f);
        void Move(float,float);
        void Rotate(float);
        void Scale(float);

        bool stopsRays;

        void setOrigin(sf::Vector2f);
        void setOrigin(float,float);
        void moveOrigin(sf::Vector2f);
        void moveOrigin(float,float);
        void shiftFromOrigin(sf::Vector2f); //moves the sprite and hitbox this distance from its origin
        void shiftFromOrigin(float,float);
        void setOriginAsFraction(float,float);

        sf::Vector2f getOrigin();

        virtual void update();
        void setContact(bool);
        int getRenderPriority();
        float getMass();
        void setMass(float);
        void increaseMass(float);
        void setImmovable(bool);

        void makeInert(float); //makes inert from specific interactions for a set period of time (in seconds)
        void makeInert();

        void makeAir(float);

        void setImpulse(sf::Vector2f); //applies an impulse to the object, pushing it
        void setVerticalImpulse(float);
        void setElevation(float);
        void elevate();
        float getElevation();

        float verticalImpulse;

        sf::Vector2f elevatedPosition;

        int health, maxhealth;
        bool dead;
        bool solid;

        virtual void evolveHitbox()
        {

        }

        void increaseMaxHealth(int);
        void damageBy(int);
        void healBy(int);

        float airForThisLong;

        float acceleration,diagacceleration;

        vector <Content*> *dungeonContent;

        void setDungeon(vector <Content*> *dunCont)
        {
            dungeonContent = dunCont;
        }

        virtual void unlock()
        {
        }

        void checkHealth()
        {
            if(destructable && health <=0)
            {
                isDestroyed();
            }
        }

        virtual void isDestroyed()
        {
            dead = true;
            destroyMe = true;
        }

        int renderPriority;

        bool isSolid();
        bool isImpassable();

        void resetFlags();

        bool destroyMe;

        sf::Vector2f getPosition();

        int facing, animFPS;

        bool dynamic, movable, impassable, destructable, inert;
        //inert stops damage, pickups etc from being interacted with, but won't stop physics
        bool wall;
        float mass, basemass, recipmass;

        //Level* parentLevel;

        //void setParentGame(Game*);
        void setDelta(float);
        float delta;
        float friction;

        void makeSolid();
        void makeAir();

        float rotation;

        float elevation;

        float frameDiff;
        float oneOverSixty;
        float frameRateDiff;

        sf::Vector2f adjustedVelocity;
        sf::Vector2f adjustedImpulse;

        virtual void extraAllocations()
        {

        }

        bool locked;
        bool moved;
        float rotationSpeed;

        sf::Vector2f velocity, impulse;

        //okay, so dynamic means it is propelled by it's own velocity value, movable means it can pushed by someone elses
        //solid means it can't be passed through, so for example:

        //a player is dynamic, movable and solid
        //a wall is non dynamic, non movable and solid
        //a floor tile is non dynamic, non movable and non solid
        //a companion cube is non dynamic, movable and solid
        //a ghost is dynamic, non movable and non solid

        //virtual void updateContentInformation();


    protected:
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(showShadow)
            {
                target.draw(shadow);
            }
            target.draw(objSprite);
            if(drawHitbox)
            {
                target.draw(objHitbox);
            }
            target.draw(objParticles);
            if(drawHitbox)
            {
                target.draw(objRays);
            }
        }


};

#endif // CONTENT_H
