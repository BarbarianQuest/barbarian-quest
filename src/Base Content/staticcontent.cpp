
#include <Base Content/staticcontent.h>


StaticContent::StaticContent() : Content()
{
    //ctor
    content_id += "_sta";
    dynamic = false;
    stopsRays = true;
}

StaticContent::~StaticContent()
{
    //dtor
}
