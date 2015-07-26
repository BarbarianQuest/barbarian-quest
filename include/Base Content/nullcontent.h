#ifndef NULLCONTENT_H
#define NULLCONTENT_H

#include <iostream>
#include "content.h"

class nullContent : public Content
{
    public:
        nullContent();
        virtual ~nullContent();
    protected:
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            cout << "null content present! Please review the crappy code you wrote...";
        }
};

#endif // NULLCONTENT_H
