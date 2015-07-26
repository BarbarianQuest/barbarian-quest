#include "layeredanimation.h"

LayeredAnimation::LayeredAnimation()
{
    //ctor
}

LayeredAnimation::~LayeredAnimation()
{
    //dtor
}



void LayeredAnimation::Move(sf::Vector2f amount)
{
    int i;
    for(i=0; i<layers.size(); i++)
    {
        layers[i].Move(amount);
    }
}

void LayeredAnimation::setOrigin()
{
    int i;
    sf::Vector2f new_origin;
    new_origin.x = 0.5*getBounds().x;
    new_origin.y = 0.5*getBounds().y;
    origin = new_origin;
    for(i=0;i<layers.size();i++)
    {
        layers[i].setOrigin(new_origin);
    }
}

sf::Vector2f LayeredAnimation::getPosition()
{
    if(layers.size() > 0)
    {
        return(layers[0].getPosition());
    }
    else
    {
        sf::Vector2f nullVector(0,0);
        return(nullVector);
    }
}

void LayeredAnimation::setPosition(sf::Vector2f newPosition)
{
    int i;
    for(i=0;i<layers.size();i++)
    {
        layers[i].setPosition(newPosition);
    }
}

void LayeredAnimation::sortLayers()
    {
        int i;
        int priority = 0;
        sortedLayers.erase(sortedLayers.begin(), sortedLayers.end());
        while(sortedLayers.size()<layers.size())
            {
                for(i=0; i<layers.size(); i++)
                {
                    if(layers[i].localRenderPriority == priority)
                    {
                        sortedLayers.push_back(&layers[i]);
                    }
                }
                priority++;
            }
    }

void LayeredAnimation::addLayer(const Animation & newLayer)
{
    layers.push_back(newLayer);
    layers.back().setOrigin(origin);
    sortLayers();
}

void LayeredAnimation::setOrigin(sf::Vector2f new_origin)
{
    int i;
    origin = new_origin;
    for(i=0;i<layers.size();i++)
    {
        layers[i].setOrigin(new_origin);
    }
}

void LayeredAnimation::addLayer(const sf::Texture & newSheet)
{
    Animation newAnim;
    newAnim.setSpriteSheet(newSheet);
    //newAnim.addReel(0,0,newSheet.getSize().x,newSheet.getSize().y,1,"whole sheet");
    addLayer(newAnim);
    sortLayers();
    return;
}

sf::Vector2f LayeredAnimation::getOrigin()
{
    return(origin);
}

sf::Vector2f LayeredAnimation::getBounds() // will only work with a centred origin right now...
{
    /*int i;
    float min_x, max_x, min_y, max_y;
    sf::Vector2f size_layer1, position_layer1;
    size_layer1 = layers[0].getSize();
    position_layer1 = layers[0].getPosition();
    min_x = position_layer1.x - 0.5*size_layer1.x;
    min_y = position_layer1.y - 0.5*size_layer1.y;
    max_x = position_layer1.x + 0.5*size_layer1.x;
    max_y = position_layer1.y + 0.5*size_layer1.y;
    for(i=1; i<layers.size(); i++)
    {
        sf::Vector2f new_pos = layers[i].getPosition();
        sf::Vector2f new_size = layers[i].getSize();
        float new_min_x = new_pos.x - new_size.x;
        float new_max_x = new_pos.x + new_size.x
    }*/
    return(layers[0].getSize());
}

void LayeredAnimation::playLayer(int layernum)
{
    if(layernum<layers.size())
    {
        layers[layernum].Go();
    }
    else
    {
    }
}

void LayeredAnimation::stopLayer(int layernum)
{
    if(layernum<layers.size())
    {
        layers[layernum].Stop();
    }
    else
    {
        return;
    }
}

void LayeredAnimation::setLayerRenderPriority(int layernum, int newpriority)
{
    if(layernum >= layers.size())
    {
        return;
    }
    layers[layernum].setLocalRenderPriority(newpriority);
    sortLayers();
}

void LayeredAnimation::Rotate(float amount)
{
    int i;
    for(i=0;i<layers.size();i++)
    {
        layers[i].Rotate(amount);
    }
}

