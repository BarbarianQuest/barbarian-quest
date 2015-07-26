#include <Base Content/passivecontent.h>
#include <Objects/Weapons/weapon.h>

Weapon::Weapon(): PassiveContent()
{
    //ctor
    makeAir();
    impassable = false;
    movable = false;
    renderPriority = 1;
    reach = 0;
    attackTime = 0;
    front_delay = 0;
    back_delay = 0;
    knockback = 0;
    fl_damage = 0;

    setOrigin(35,45);

    weapsize = 70;

    readyToAttack = false;
    attacking = false;
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::evolveHitbox()
{

}

void Weapon::initialiseWeapon(Content* owner)
{
    setOwner(owner);
    allocateAssets();
    setHitboxProperties();
}

void Weapon::setOwner(Content* owner)
{
    heldBy = owner;
    setPosition(owner->getPosition());
    return;
}

void Weapon::startAttack()
{
    if(readyToAttack && attacking == false)
    {
        attackClock.restart();
        attacking = true;
    }
}

void Weapon::hits(Content* other)
{
    if(other->destructable)
    {
        other->damageBy(maths.roundAndCast(fl_damage));
        other->makeInert(attackTime-attackTimer.asSeconds());
    }
    if(other->idContains("projectile"))
    {
        other->velocity.x = 0;
        other->velocity.y = 0;
        other->rotationSpeed = 10;
    }
    if(other->idContains("bomb"))
    {
        other->trigger();
    }
    if(other->movable)
    {
        sf::Vector2f unit = maths.unitVector(getPosition() - other->getPosition());
        other->makeInert(attackTime-attackTimer.asSeconds());
        //other->velocity.x = 0;
        //other->velocity.y = 0;
        other->impulse += (-knockback*unit);
    }
}

void Weapon::attack()
{

}

void Weapon::update()
{
    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    attackTimer = attackClock.getElapsedTime();
    makeAir();
    if(attackTimer.asSeconds() <= front_delay && readyToAttack)
    {
        //do nothing
        readyToAttack = false;
    }
    if(attackTimer.asSeconds() > front_delay && attackTimer.asSeconds() <= attackTime + front_delay)
    {
        //do the actual attacking
        if(attacking)
        {
            makeSolid();
            evolveHitbox();
            attack();
        }
    }
    if(attackTimer.asSeconds() > attackTime + front_delay && attackTime <= attackTime+front_delay+back_delay)
    {
        //pause a bit longer
    }
    if(attackTimer.asSeconds() > attackTime+front_delay+back_delay)
    {
        readyToAttack = true;
        attacking = false;
    }
    evolveMovement();
}

void Weapon::setAnimationProperties()
{
    animFPS = maths.roundAndCast(7.0/attackTime);
}

void Weapon::allocateAssets()
{
    sf::Vector2u sizeOfSheet;
    objSprite.addLayer(assets->getTex(spriteAddresses[0]));
    sizeOfSheet = objSprite.layers.back().getSheetSize();

    framenum = sizeOfSheet.y/weapsize;

    setAnimationProperties();

    objSprite.layers.back().addReel(0,0,weapsize,weapsize,framenum,"down");
    objSprite.layers.back().addReel(70,0,weapsize,weapsize,framenum,"up");
    objSprite.layers.back().addReel(140,0,weapsize,weapsize,framenum,"right");
    objSprite.layers.back().addReel(210,0,weapsize,weapsize,framenum,"left");
    objSprite.layers.back().setFPS(animFPS);
    objSprite.layers.back().changeReel(0);

}
