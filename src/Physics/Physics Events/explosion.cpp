#include <Physics/Physics Events/physicsevent.h>
#include <Physics/Physics Events/explosion.h>

Explosion::Explosion(): PhysicsEvent()
{
    //ctor
    content_id += "_explosion";
    setOrigin(0,0);
    setParameters(0,0,0,0);
    sf::Vector2f null(0,0);
    objHitbox.addCircularHitbox(null,20);
    makeSolid();
    impassable = false;
}

Explosion::Explosion(float time_set, float imp_set, float rad_set, int dam_set) : PhysicsEvent()
{
    content_id += "_explosion";
    setOrigin(0,0);
    sf::Vector2f null(0,0);
    objHitbox.addCircularHitbox(null,20);
    setParameters( time_set, imp_set, rad_set, dam_set);
}

Explosion::~Explosion()
{
    //dtor
}

void Explosion::setExplosionDamage(int dam_set)
{
    boom_damage = dam_set;
}

void Explosion::setExplosionDuraton(float time_set)
{
    boom_duration = time_set;
    inv_duration = 1.0/boom_duration;
    eventClock.restart();
}

void Explosion::setExplosionImpulse(float imp_set)
{
    boom_impulse = imp_set;
}

void Explosion::setExplosionRadius(float rad_set)
{
    boom_radius = rad_set;
    drawHitbox = true;
}

void Explosion::setParameters(float time_set, float imp_set, float rad_set, int dam_set)
{
    setExplosionDuraton(time_set);
    setExplosionImpulse(imp_set);
    setExplosionRadius(rad_set);
    setExplosionDamage(dam_set);
}

void Explosion::evolveHitbox()
{
    if(eventTimer.asSeconds() < boom_duration)
    {
        if(objHitbox.circs.back().radius < boom_radius)
        {
            objHitbox.circs.back().setRadius(objHitbox.circs.back().radius + delta*inv_duration*boom_radius);
        }
    }
    if(eventTimer.asSeconds() > boom_duration)
    {
        objHitbox.circs.back().setRadius(0);
        destroyMe = true;
    }
}

void Explosion::update()
{

    objSprite.sortLayers();
    objHitbox.update();
    updateClocks();
    eventTimer = eventClock.getElapsedTime();
    evolveHitbox();
    evolveMovement();
}

void Explosion::allocateAssets()
{

}

void Explosion::hits(Content* obj)
{
    if(obj->destructable)
    {
        obj->damageBy(boom_damage);
        //obj->makeInert(boom_duration);
    }
    if(obj->idContains("bomb"))
    {
        obj->trigger();
    }
    if(obj->movable || obj->dynamic)
    {
        sf::Vector2f unit = maths->unitVector(getPosition() - obj->getPosition());
        //obj->makeInert(boom_duration);
        //other->velocity.x = 0;
        //other->velocity.y = 0;
        obj->impulse += (-boom_impulse*unit);
    }
}
