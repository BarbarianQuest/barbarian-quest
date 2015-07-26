#include <System Tools/renderengine.h>

RenderEngine::RenderEngine()
{
    //ctor
    zonesize = 100*64;
    drawHitboxes = false;
    totalsize = 0;
}

RenderEngine::~RenderEngine()
{
    //dtor
}

void RenderEngine::populateContentList(vector <Content*> gameContent,sf::Vector2f windowPosition)
{
    int i,j, castdifference, zone;
    float distance,squdifference,this_x, this_y;
    sf::Vector2f difference;
    top = (*gameContent[0]).getPosition().y;
    bottom = (*gameContent[0]).getPosition().y;
    left = (*gameContent[0]).getPosition().x;
    right = (*gameContent[0]).getPosition().x;
    for(i=1; i<gameContent.size(); i++)
    {
        this_x = (*gameContent[i]).getPosition().x;
        this_y = (*gameContent[i]).getPosition().y;
        if(this_x < left) {left = this_x;}
        if(this_x > right) {right = this_x;}
        if(this_y < top) {top = this_y;}
        if(this_y > bottom) {bottom = this_y;}
    }
    float scale_y = (bottom-top);
    float scale_x = (right-left);

    int zones_x = ceil(scale_x/zonesize);
    int zones_y = ceil(scale_y/zonesize);

    numberofzones = zones_x*zones_y;

    allContent.resize(numberofzones);
    zoneAreas.resize(numberofzones);
    int current_x = 0;
    int current_y = 0;
    for(i=0; i<numberofzones; i++)
    {

        if(current_x == zones_x)
        {
            if(current_y == zones_y)
            {break;}
            current_x = 0;
            current_y++;
        }
        zoneAreas[i].left = left + current_x*zonesize;
        zoneAreas[i].top = top + current_y*zonesize;
        zoneAreas[i].width = zonesize;
        zoneAreas[i].height = zonesize;
        current_x++;
    }
    sf::Vector2f pos;
    for(i=0; i<gameContent.size(); i++)
    {
        pos = (*gameContent[i]).getPosition();
        for(j=0; j<allContent.size(); j++)
        {
            if(zoneAreas[j].contains(pos.x,pos.y));
            {
                allContent[j].push_back(gameContent[i]);
            }
        }
    }
    totalsize = gameContent.size();

    updatePosition(windowPosition);


/*    renderContent.erase(renderContent.begin(),renderContent.end());

    for(i=0; i<gameContent.size(); i++)
    {
        difference = gameContent[i]->getPosition() - windowPosition;
        squdifference = (difference.x*difference.x + difference.y*difference.y);

        distance = maths.sqrt(squdifference);
        if(distance < renderRange)
        {
            renderContent.push_back(gameContent[i]);
        }
    }*/
}

vector<vector<Content*> > RenderEngine::returnZones()
{
    return(allContent);
}

void RenderEngine::appendNewContent(Content* newContent)
{
    int i,j;

    sf::Vector2f pos;
     pos = newContent->getPosition();
        /*for(j=0; j<activeZones.size(); j++)
        {

            if(zoneAreas[activeZones[j]].contains(pos.x,pos.y));
            {
                allContent[activeZones[j]].push_back(newContent);
            }
        }*/
    renderContent.push_back(newContent);
}

void RenderEngine::updateContentList(const vector <Content*> & gameContent,sf::Vector2f windowPosition)
{
    updatePosition(windowPosition);

    /*int i,j;
    for(j=0; j<activeZones.size(); j++)
    {

        allContent[activeZones[j]].erase(allContent[activeZones[j]].begin(),allContent[activeZones[j]].end());
    }

    sf::Vector2f pos;
        for(j=0; j<activeZones.size(); j++)
        {
            for(i=0; i<gameContent.size(); i++)
            {
                pos = gameContent[i]->getPosition();
                    if(zoneAreas[activeZones[j]].contains(pos.x,pos.y));
                    {
                        allContent[activeZones[j]].push_back(gameContent[i]);
                    }
            }
        }*/
    renderContent = gameContent;

}

void RenderEngine::setHitboxMode(bool drawOrNot)
{
    int i,j;
    if(drawHitboxes != drawOrNot)
    {
        drawHitboxes = drawOrNot;
        for(i=0; i<renderContent.size(); i++)
        {
                renderContent[i]->drawHitbox=drawHitboxes;
        }
    }
}

void RenderEngine::updatePosition(sf::Vector2f windowPosition)
{
    /*int i, castdifference;
    float distance,squdifference;
    sf::Vector2f difference;
    renderContent.erase(renderContent.begin(),renderContent.end());
    activeZones.erase(activeZones.begin(),activeZones.end());
    float shortSide = 0;
    for(i=0; i<zoneAreas.size(); i++)
    {
        if(zoneAreas[i].contains(windowPosition.x,windowPosition.y))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x - shortSide, windowPosition.y))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x + shortSide, windowPosition.y))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x, windowPosition.y + shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x, windowPosition.y - shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x - shortSide, windowPosition.y + shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x + shortSide, windowPosition.y + shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x + shortSide, windowPosition.y - shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
        if(zoneAreas[i].contains(windowPosition.x - shortSide, windowPosition.y - shortSide))
        {
            activeZones.push_back(i);
            continue;
        }
    }
    int j;
    float squRange = renderRange*renderRange;
    for(j=0; j<activeZones.size(); j++)
    {

        for(i=0; i<allContent[activeZones[j]].size(); i++)
        {

            difference = allContent[activeZones[j]][i]->getPosition() - windowPosition;
            squdifference = (difference.x*difference.x + difference.y*difference.y);

            distance = squdifference;
            if(distance < squRange)
            {
                renderContent.push_back(allContent[activeZones[j]][i]);
            }
        }
    }*/
}

bool compare_y_position(Content* first, Content* second)
{
    return(first->getPosition().y < second->getPosition().y);
}

vector <Content*> RenderEngine::returnRenderedContent()
{
    return(toBeRendered);
}

void RenderEngine::sortContent()
{
int i,j;
toBeRendered.clear();
sortedContent.clear();
std::list<Content* >::iterator it;
int numberOfLayers = 1;
    for(i=0; i<renderContent.size(); i++)
    {
        if(renderContent[i]->getRenderPriority() > numberOfLayers - 1)
        {
            numberOfLayers = renderContent[i]->getRenderPriority() + 1;
        }
    }
    sortedContent.resize(numberOfLayers);
    for(i=0; i<renderContent.size(); i++)
    {
        sortedContent[renderContent[i]->getRenderPriority()].push_back(renderContent[i]);
    }
    for(i=0; i<numberOfLayers; i++)
    {
        sortedContent[i].sort(compare_y_position);
    }
    for(i=0; i<numberOfLayers; i++)
    {
        for (it=sortedContent[i].begin(); it!=sortedContent[i].end(); ++it)
        toBeRendered.push_back(*it);
    }

}

void RenderEngine::setRenderRange(float range)
{
    renderRange = range;
}
