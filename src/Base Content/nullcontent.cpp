#include <Base Content/content.h>
#include <Base Content/nullcontent.h>

nullContent::nullContent() : Content()
{
    //ctor
    content_id += "_NULL";
    dynamic = false;
    movable = false;
    impassable = false;
    solid = false;
    stopsRays = false;
}

nullContent::~nullContent()
{
    //dtor
}
