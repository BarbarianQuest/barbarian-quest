#ifndef LAYEREDANIMATION_H
#define LAYEREDANIMATION_H

#pragma once

#include<animation.h>

#include <SFML/Graphics.hpp>


class LayeredAnimation : public sf::Drawable
{
    public:
        LayeredAnimation();
        virtual ~LayeredAnimation();

        sf::Vector2f origin;

        void Move(sf::Vector2f);

        void addLayer(const Animation &);
        void addLayer(const sf::Texture &);

        sf::Vector2f getBounds();

        void Rotate(float);

        void setOrigin();
        void setOrigin(sf::Vector2f);
        sf::Vector2f getOrigin();

        void playLayer(int);
        void stopLayer(int);
        void playAll();
        void stopAll();

        void setAlpha(float);
        void setLayerAlpha(int,float);

        void sortLayers();

        void setPosition(sf::Vector2f);

        sf::Vector2f getPosition();

        void setLayerRenderPriority(int, int);

        vector<Animation> layers;
        vector<Animation*> sortedLayers;


    protected:
    private:





    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {

            int i;
            for(i=0; i<layers.size(); i++)
            {
                target.draw(*sortedLayers[i]);
            }
        }
};

#endif // LAYEREDANIMATION_H
