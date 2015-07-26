#ifndef PLAYER_H
#define PLAYER_H

#include <Base Content/dynamiccontent.h>
#include <destructable.h>
#include <tile.h>
#include <math.h>
#include <Weapons/weapon.h>
#include <Weapons/weapons.h>
#include <Base Content/dynamiccontent.h>
#include <Objects/Weapons/weapon.h>


class Player : public DynamicContent
{
    public:
        Player();
        virtual ~Player();


        void Move(sf::Vector2f);
        void setTexture(const sf::Texture &);
        void animate();
        void animate(sf::Time,bool);
        void hits(Content*);
        void isHitBy(Content*);
        void notInContact();
        //void Move(sf::Vector2f);
        void setMaxSpeed(float);
        void Attack();
        void passKeyBoardInput(vector<bool>);
        vector<sf::Keyboard::Key> getKeyMap();
        void setKeyMap(vector<sf::Keyboard::Key>);
        void updateDebug();

        void allocateAssets();
        void setManager(ResourceManager* );

        void setWeapon(Weapon*);

        vector<Content*> returnChildren();

        int feet_layer, body_layer, weapon_layer, head_layer;

        int keys, coins, ammo;
        bool bosskey,compass;

        bool hasBossKey();
        bool hasCompass();

        void update();


    protected:
    private:

        sf::Vector2i activeTile;

        sf::Keyboard::Key move_up, move_down, move_right, move_left,attack_key;

        Animation* heroSprite;

        Weapon* equippedWeapon;

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
        }
};

#endif // PLAYER_H
