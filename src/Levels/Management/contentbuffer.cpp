#include <Base Content/nullcontent.h>
#include "contentbuffer.h"

ContentBuffer::ContentBuffer()
{
    //ctor
}

ContentBuffer::~ContentBuffer()
{
    //dtor
}

void ContentBuffer::addContent(Content* newContent)
{
    activeBuffer.push_back(newContent);
}

void ContentBuffer::addContent(vector<Content*> newContent)
{
    int i;
    for(i=0; i<newContent.size(); i++)
    {
        addContent(newContent[i]);
    }
}

vector<Content*> ContentBuffer::getContent()
{
    return(activeBuffer);
}

void ContentBuffer::clean()
{
    activeBuffer.clear();
}

Content* ContentBuffer::requestContent(std::string contentType)
{
    //here I will parse the name of a piece of content, build a null safe pointer to a new instance and send it back to the level.
    Content* toReturn = new nullContent;

}
