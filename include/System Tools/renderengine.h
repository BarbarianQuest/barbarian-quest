#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SFML/Graphics.hpp>
#include <list>
#include <Base Content/content.h>
#include <System Tools/windowconfig.h>
#include <Functions/fastmaths.h>

using namespace std;

class RenderEngine : public sf::Drawable
{
    public:
        RenderEngine();
        virtual ~RenderEngine();

        void setRenderRange(float);
        void populateContentList(vector<Content*>,sf::Vector2f);
        void updateContentList(const vector<Content*> &,sf::Vector2f);
        void updatePosition(sf::Vector2f);
        void appendNewContent(vector<Content*>);
        void appendNewContent(Content*);
        void sortContent();
        void setHitboxMode(bool);
        bool checkCollision(Content*, Content*);
        vector <Content*> returnRenderedContent();
        vector<vector<Content*> > returnZones();

        bool drawHitboxes;

    protected:
    private:
        float renderRange,zonesize, left,right,top,bottom;
        int numberofzones;
        int totalsize;
        vector<sf::IntRect> zoneAreas;
        vector<Content*> renderContent;
        vector<Content*> toBeRendered;
        vector<vector<Content*> > allContent;
        vector<std::list<Content*> >  sortedContent;
        vector<int> activeZones;
        fastMaths maths;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        int i;
        for(i=0; i<toBeRendered.size(); i++)
        {
            target.draw(*toBeRendered[i]);
        }
    }
};

#endif // RENDERENGINE_H
