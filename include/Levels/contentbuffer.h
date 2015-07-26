#ifndef CONTENTBUFFER_H
#define CONTENTBUFFER_H

#include <Base Content/content.h>
#include <System Tools/stringtools.h>


class ContentBuffer
{
    public:
        ContentBuffer();
        virtual ~ContentBuffer();

        vector<Content*> activeBuffer;

        void addContent(Content*);
        void addContent(vector<Content*>);

        vector<Content*> getContent();
        void clean();

        Content* requestContent(std::string);

        StringTools stringtools;

    protected:
    private:
};

#endif // CONTENTBUFFER_H
