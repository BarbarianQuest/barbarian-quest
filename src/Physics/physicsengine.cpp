#include "physicsengine.h"

PhysicsEngine::PhysicsEngine()
{
    //ctor
    physics_range = 600;
}

PhysicsEngine::~PhysicsEngine()
{
    //dtor
}

void PhysicsEngine::makeGrid(int x_size, int y_size, int zoneSize, int min_x, int min_y)
{
    int i,j;
    int c=0;
    chunkZones.resize(x_size*y_size);
    chunkActive.resize(x_size*y_size);
    chunkContactSize.resize(x_size*y_size);
    min_zone_x = min_x;
    min_zone_y = min_y;
    for(i=0; i<y_size; i++)
    {
        for(j=0; j<x_size; j++)
        {
            chunkZones[c].left = (j*zoneSize + min_x)*64;
            chunkZones[c].top = (i*zoneSize+ min_y)*64;
            chunkZones[c].height = chunkZones[c].width = zoneSize*64;
            chunkActive[c] = false;
            chunkContactSize[c] = 0;
            c++;
        }
    }
}

void PhysicsEngine::updateActiveZones(vector <vector <Chunk> > * chunks)
{
    int i, j;
    for(i = 0; i< (*chunks).size(); i++)
    {
        for(j=0; j<(*chunks)[i].size(); j++)
        {
            chunkActive[i+j] = (*chunks)[i][j].active;
            chunkContactSize[i+j] = (*chunks)[i][j].inContact.size();
        }
    }
}

bool PhysicsEngine::checkCollision(sf::Vector2f point, CompoundHitbox* obj)
{
    int j;
    bool runCheck = false;
    for(j=0; j<obj->rects.size(); j++)
        {
            if(!obj->rects[j].solid) {continue;}
            if(point.x > obj->rects[j].getAbsolutePosition().x - obj->rects[j].width*0.5
                && point.x < obj->rects[j].getAbsolutePosition().x + obj->rects[j].width*0.5
                && point.y > obj->rects[j].getAbsolutePosition().y - obj->rects[j].height*0.5
                && point.y < obj->rects[j].getAbsolutePosition().y + obj->rects[j].height*0.5)
            {
                runCheck = true;
            }
        }
        for(j=0; j<obj->circs.size(); j++)
        {
            if(obj->circs[j].simpleShape.contains(point))
            {
                if(!obj->circs[j].solid) {continue;}
                if(maths.magnitude(point-obj->circs[j].getAbsolutePosition()) < obj->circs[j].radius)
                {
                    runCheck = true;
                }
            }
        }
        return(runCheck);
}

sf::Vector2i PhysicsEngine::getZone(sf::Vector2f point)
{
    int x,y;
    x = 0;
    y = 0;
    int i;
    sf::Vector2i out(0,0);
    if(chunkZones.size()==0)
    {
        debug.println("grid not present, try initialising the grid first");
        return(out);
    }
    float prevTop = chunkZones[0].top;
    for(i=0; i<chunkZones.size(); i++)
    {
        //if(!chunkActive[i]) {continue;}
        if(chunkZones[i].top > prevTop)
        {
            prevTop = chunkZones[i].top;
            y++;
            x=0;
        }
        if(chunkZones[i].contains(point))
        {
            out.x = x;
            out.y = y;
            return(out);
        }
        //cout << x << ", " << y << endl;
        x++;
    }
    debug.println("error! no zone found");
    return(out);
}

bool PhysicsEngine::checkCollision(Content* firstContent, Content* secondContent)
{
    int i,j;
    CompoundHitbox* firstHitbox = firstContent->getHitbox();
    CompoundHitbox* secondHitbox = secondContent->getHitbox();
    vector<CircularHitbox*> circsInContact;
    vector<RectangularHitbox*> rectsInContact;

    sf::Vector2f diff = firstHitbox->getPosition() - secondHitbox->getPosition();
    float mag = diff.x*diff.x + diff.y*diff.y;

    bool in_collision = false;

    if(fabs(firstContent->getElevation() - secondContent->getElevation()) > 32)
    {
        return false;
    }

    if(firstContent->isSolid() && secondContent->isSolid())
    {
        in_collision = false;
        for(i=0; i<firstHitbox->circs.size(); i++)
        {
            for(j=0; j<secondHitbox->rects.size(); j++)
            {
                if(hitboxOverlap(&firstHitbox->circs[i],&secondHitbox->rects[j]))
                {
                    in_collision = true;
                    break;
                }
            }
            for(j=0; j<secondHitbox->circs.size(); j++)
            {
                if(hitboxOverlap(&firstHitbox->circs[i],&secondHitbox->circs[j]))
                {
                    in_collision = true;
                    break;
                }
            }
        }
        for(i=0; i<firstHitbox->rects.size(); i++)
        {
            for(j=0; j<secondHitbox->rects.size(); j++)
            {
                if(hitboxOverlap(&firstHitbox->rects[i],&secondHitbox->rects[j]))
                {
                    in_collision = true;
                    break;
                }
            }
            for(j=0; j<secondHitbox->circs.size(); j++)
            {
                if(hitboxOverlap(&firstHitbox->rects[i],&secondHitbox->circs[j]))
                {
                    in_collision = true;
                    break;
                }
            }

        }

    }

    if(!firstContent->inContact && in_collision)
    {
        firstContent->setContact(in_collision);
    }
    if(!secondContent->inContact && in_collision)
    {
        secondContent->setContact(in_collision);
    }

    return(in_collision);
}

void PhysicsEngine::loopOverTwoVectors(vector<Content*> first, vector<Content*> second)
{
    int i,j;
    vector<Content*> mixedBag;
    for(i=0; i<first.size(); i++)
    {
        first[i]->notInContact();
    }
    for(j=0; j<second.size(); j++)
    {
        second[j]->notInContact();
    }
    for(i=0; i<first.size(); i++)
    {
        if((!first[i]->dynamic && !first[i]->movable && !first[i]->isSolid()) || !first[i]->render)
        {continue;}
        mixedBag.erase(mixedBag.begin(),mixedBag.end());
        for(j=0; j<first.size(); j++)
        {
            if(j==i) {continue;}
            if((!first[j]->dynamic && !first[j]->movable && !first[j]->isSolid()) || !first[j]->render)
            {continue;}
            /*if(maths.magnitude(first[j]->getPosition()-first[i]->getPosition()) > physics_range)
            {continue;}*/
            mixedBag.push_back(first[j]);
        }
        for(j=0; j<second.size(); j++)
        {
        if((!second[j]->dynamic && !second[j]->movable && !second[j]->isSolid()) || !second[j]->render)
            {continue;}
        /*if(maths.magnitude(second[j]->getPosition()-first[i]->getPosition()) > physics_range)
            {continue;}*/

            mixedBag.push_back(second[j]);
        }
        loopOverOneVector(first[i],mixedBag);
    }
}

void PhysicsEngine::autoLoopOverVector(vector<Content*> contentArray)
{
    int i,j;
    //vector<Content*> otherContent;
    sf::Vector2f overlap;
    for(i=0; i<contentArray.size(); i++)
    {
        contentArray[i]->setContact(false);
        /*if((!contentArray[i]->dynamic && !contentArray[i]->movable && !contentArray[i]->isSolid()) || !contentArray[i]->render)
        {continue;}*/
        //otherContent.erase(otherContent.begin(),otherContent.end());
        for(j=0; j<contentArray.size(); j++)
        {
            /*if((!contentArray[j]->dynamic && !contentArray[j]->movable && !contentArray[j]->isSolid()) || !contentArray[j]->render)
            {continue;}*/
            if(j==i) {continue;}
            contentArray[j]->setContact(false);

            if(contentArray[j]->isSolid())
            {
                if(checkCollision(contentArray[i],contentArray[j]))
                {
                    if(!contentArray[i]->inert && !contentArray[j]->inert)
                    {
                        contentArray[i]->hits(contentArray[j]);
                        contentArray[j]->hits(contentArray[i]);
                    }
                    if(contentArray[i]->isImpassable() && contentArray[j]->isImpassable())
                    {
                        overlap = getOverlap(contentArray[i], contentArray[j]);

                    }
                }
                else
                {

                }
            }

            //otherContent.push_back(contentArray[j]);
        }
        //loopOverOneVector(contentArray[i],otherContent);
    }
}

void PhysicsEngine::loopOverOneVector(Content* particle, vector<Content*> contentArray)
{
    int i;
    particle->setContact(false);
    sf::Vector2f overlap;
    for(i=0; i<contentArray.size(); i++)
    {
        /*if(maths.magnitude(particle->getPosition()-contentArray[i]->getPosition()) > physics_range)
            {continue;}*/
        contentArray[i]->setContact(false);
        if(contentArray[i]->isSolid())
        {
            if(checkCollision(particle,contentArray[i]))
            {
                if(!particle->inert && !contentArray[i]->inert)
                {
                    particle->hits(contentArray[i]);
                    contentArray[i]->hits(particle);
                }
                if(particle->isImpassable() && contentArray[i]->isImpassable())
                {
                    overlap = getOverlap(particle, contentArray[i]);

                }
            }
            else
            {

            }
        }
    }
}

bool PhysicsEngine::hitboxOverlap(RectangularHitbox* first, RectangularHitbox* second)
{
    if(!first->simpleShape.intersects(second->simpleShape)) {return(false);}

    sf::Vector2f diff = -first->getAbsolutePosition() + second->getAbsolutePosition();
    sf::Vector2f area;

    area.x = 0.5*first->getBounds().x + 0.5*second->getBounds().x;
    area.y = 0.5*first->getBounds().y + 0.5*second->getBounds().y;

    bool overlap = abs(diff.x) < area.x && abs(diff.y) < area.y;

    //= neg_zone_x && neg_zone_y && pos_zone_x && pos_zone_y;

    return(overlap);
}

bool PhysicsEngine::hitboxOverlap(RectangularHitbox* second, CircularHitbox* first)
{
    return(hitboxOverlap(first,second));
}

bool PhysicsEngine::hitboxOverlap(CircularHitbox* first, RectangularHitbox* second)
{
    //if(!first->simpleShape.intersects(second->simpleShape)) {return(false);}
    sf::Vector2f diff = -first->getAbsolutePosition() + second->getAbsolutePosition();
    sf::Vector2f area;

    area.x = first->getRadius() + 0.5*second->getBounds().x;
    area.y = first->getRadius() + 0.5*second->getBounds().y;

    bool overlap = abs(diff.x) < area.x && abs(diff.y) < area.y;

    //= neg_zone_x && neg_zone_y && pos_zone_x && pos_zone_y;

    return(overlap);
}

bool PhysicsEngine::hitboxOverlap(CircularHitbox* first, CircularHitbox* second)
{
    if(!first->simpleShape.intersects(second->simpleShape)) {return(false);}
    sf::Vector2f diff = -first->getAbsolutePosition() + second->getAbsolutePosition();
    float mag = maths.magnitude(diff);
    float radsum = first->getRadius() + second->getRadius();
    return(mag < radsum);
}

void PhysicsEngine::doCollision(Content* first, Content* second, sf::Vector2f overlap)
{
                if(first->dynamic && !second->movable)
                    {
                        first->Move(overlap);
                        first->impulse.x = first->impulse.y = 0;
                        return;
                    }
                /*if(!first->movable && second->dynamic)
                    {
                        second->Move(-floor(overlap.x), -floor(overlap.y));
                        return;
                    }*/

                    if((first->dynamic && second->movable))
                    {
                        float totalmass = first->mass + second->mass;
                        float reciptot = 1/totalmass;
                        float particle_mom = first->mass*reciptot;
                        float cont_mom = second->mass*reciptot;
                        first->Move(cont_mom*overlap);
                        second->Move(-particle_mom*overlap);
                    }
                    if((first->movable && second->movable))
                    {
                        float Cr = 0.9;
                        float totalmass = first->mass + second->mass;
                        float reciptot = 1/totalmass;
                        float particle_mom = first->mass*reciptot;
                        sf::Vector2f totalV_1 = /*first->velocity + */ first->velocity;
                        sf::Vector2f totalV_2 = /*second->velocity + */ second->velocity;
                        float coeff_1_1 = Cr*second->mass*reciptot;
                        float coeff_1_2 =  (first->mass)*reciptot;
                        float coeff_1_3 = (second->mass)*reciptot;
                        float coeff_2_1 = Cr*first->mass*reciptot;
                        float coeff_2_2 = coeff_1_2;
                        float coeff_2_3 = coeff_1_3;
                        sf::Vector2f diff_V = totalV_2 - totalV_1;
                        sf::Vector2f newV_1 = (coeff_1_1*diff_V + coeff_1_2*totalV_1 + coeff_1_3*totalV_2);
                        sf::Vector2f newV_2 = (-coeff_2_1*diff_V + coeff_2_2*totalV_2 + coeff_2_3*totalV_2);
                        float cont_mom = second->mass*reciptot;
                        first->Move(cont_mom*overlap);
                        second->Move(-particle_mom*overlap);

                        first->velocity = (newV_1);
                        second->velocity = (newV_2);

                        //cout << "PHYSICS ENGINE " << "first: " << first->moved << ", second: " << second->moved << endl;

                        /*if(checkCollision(first,second))
                        {
                            overlap = getOverlap(first, second);
                            if(first->dynamic)
                            {
                                first->Move(floor(overlap.x), floor(overlap.y));
                            }
                        }*/
                    }
                    if(first->movable && !second->movable && !second->dynamic && !first->dynamic)
                    {
                        float Cr = 0.9;
                        first->Move(overlap);
                        if(fabs(overlap.x) >= fabs(overlap.y))
                        {
                            first->velocity.x = -Cr*first->velocity.x;
                        }
                        if(fabs(overlap.y) > fabs(overlap.x))
                        {
                            first->velocity.y = -Cr*first->velocity.y;
                        }
                        return;
                        //particle->setImmovable(true);
                    }
                    /*if(second->movable && !first->movable && !second->dynamic && !first->dynamic)
                    {
                        second->Move(overlap);
                        return;
                    }*/
}


sf::Vector2f PhysicsEngine::getOverlap(Content* firstContent, Content* secondContent)
{
    int i,j;
    sf::Vector2f totalOverlap, tempOverlap;
    vector<sf::Vector2f> overlaps;
    for(i=0; i<firstContent->objHitbox.rects.size(); i++)
    {
        for(j=0; j<secondContent->objHitbox.rects.size(); j++)
        {
            totalOverlap = getOverlap(&firstContent->objHitbox.rects[i],&secondContent->objHitbox.rects[j]);
            doCollision(firstContent,secondContent,totalOverlap);
        }
        for(j=0; j<secondContent->objHitbox.circs.size(); j++)
        {
            totalOverlap = getOverlap(&firstContent->objHitbox.rects[i],&secondContent->objHitbox.circs[j]);
            //cout << totalOverlap.x << ", " << totalOverlap.y << endl;
            doCollision(firstContent,secondContent,totalOverlap);
        }
    }

    for(i=0; i<firstContent->objHitbox.circs.size(); i++)
    {
        for(j=0; j<secondContent->objHitbox.rects.size(); j++)
        {
            totalOverlap = getOverlap(&firstContent->objHitbox.circs[i],&secondContent->objHitbox.rects[j]);
            doCollision(firstContent,secondContent,totalOverlap);
        }
        for(j=0; j<secondContent->objHitbox.circs.size(); j++)
        {
            totalOverlap = getOverlap(&firstContent->objHitbox.circs[i],&secondContent->objHitbox.circs[j]);
            doCollision(firstContent,secondContent,totalOverlap);
        }
    }
    return(totalOverlap);
}

sf::Vector2f PhysicsEngine::getOverlap(CircularHitbox* first, RectangularHitbox* second)
{


    bool neg_x, neg_y, pos_x, pos_y, overlap_x, overlap_y;
    bool inCollision;
    float grad, constant;
    float pos_y_thresh;
    float neg_y_thresh;

    bool above_pos;
    bool above_neg;

    sf::Vector2f overlap(0,0); //measured from first to second!
    sf::Vector2f correct_mag;

     sf::Vector2f pos_first, pos_second, difference;

    inCollision = hitboxOverlap(first,second);

    if(inCollision)
    {



        pos_first = first->getAbsolutePosition();
        pos_second = second->getAbsolutePosition();
        difference = pos_second - pos_first;

        grad = second->getBounds().y/second->getBounds().x;
        constant = pos_second.y;


        pos_y_thresh = grad*(pos_second.x - pos_first.x) + constant;
        neg_y_thresh = -grad*(pos_second.x - pos_first.x) + constant;

        above_pos = pos_first.y > pos_y_thresh;
        above_neg = pos_first.y > neg_y_thresh;

        neg_x = above_pos && !above_neg;
        pos_x = above_neg && !above_pos;
        neg_y = !above_neg && !above_pos;
        pos_y = above_neg && above_pos;

        overlap.x = ((1*pos_x + -1*neg_x)*(abs(difference.x) - first->radius - 0.5*second->getBounds().x));
        overlap.y = (-1*pos_y + 1*neg_y)*(abs(difference.y) - first->radius - 0.5*second->getBounds().y);

    }
    return(overlap);
}

sf::Vector2f PhysicsEngine::getOverlap(RectangularHitbox* second, CircularHitbox* first)
{
    return(-getOverlap(first,second));
}

sf::Vector2f PhysicsEngine::getOverlap(RectangularHitbox* first, RectangularHitbox* second)
{
    sf::Vector2f overlap(0,0); //measured from first to second!

    bool neg_x, neg_y, pos_x, pos_y, overlap_x, overlap_y;
    bool inCollision;
    sf::Vector2f pos_first = first->getAbsolutePosition();
    sf::Vector2f pos_second = second->getAbsolutePosition();
    sf::Vector2f difference = pos_second - pos_first;


    float grad = second->getBounds().y/second->getBounds().x;
    float constant = pos_second.y;


        float pos_y_thresh = grad*(pos_second.x - pos_first.x) + constant;
        float neg_y_thresh = -grad*(pos_second.x - pos_first.x) + constant;

        bool above_pos = pos_first.y > pos_y_thresh;
        bool above_neg = pos_first.y > neg_y_thresh;

        neg_x = above_pos && !above_neg;
        pos_x = above_neg && !above_pos;
        neg_y = !above_neg && !above_pos;
        pos_y = above_neg && above_pos;

    inCollision = hitboxOverlap(first,second);


    if(inCollision)
    {
        overlap.x = ((1*pos_x + -1*neg_x)*(abs(difference.x) - 0.5*first->getBounds().x - 0.5*second->getBounds().x));
    }
    if(inCollision)
    {
        overlap.y = (-1*pos_y + 1*neg_y)*(abs(difference.y) - 0.5*first->getBounds().y - 0.5*second->getBounds().y);
    }
    return(overlap);
}

sf::Vector2f PhysicsEngine::getOverlap(CircularHitbox* first, CircularHitbox* second)
{

    sf::Vector2f pos_first = first->getAbsolutePosition();
    sf::Vector2f pos_second = second->getAbsolutePosition();
    float first_rad = first->getRadius();
    float sec_rad = second->getRadius();
    float sum_rad = first_rad + sec_rad;
    sf::Vector2f difference = pos_second - pos_first;
    sf::Vector2f unitVec = maths.unitVector(difference);
    sf::Vector2f correctVec;
    correctVec = sum_rad*unitVec;
    sf::Vector2f overlap = difference - correctVec;
    return(overlap);

}

