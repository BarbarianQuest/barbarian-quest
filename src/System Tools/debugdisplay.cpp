#include <System Tools/debugdisplay.h>

debugDisplay::debugDisplay()
{
    //ctor
    displayed = true;
    textsize = 20;
}

debugDisplay::~debugDisplay()
{
    //dtor
}

void debugDisplay::setFont(const sf::Font & in_font)
{
    P1pos.setFont(in_font);
    P1tile.setFont(in_font);
    FPS.setFont(in_font);
    P1velocity.setFont(in_font);
    P1chunk.setFont(in_font);
    return;
}

void debugDisplay::setP1chunk(sf::Vector2i player_chunk)
{
    string xpos, ypos, prefix;
    prefix = "CHUNK INDEX: ";
    xpos = boost::lexical_cast<string>(player_chunk.x);
    ypos = boost::lexical_cast<string>(player_chunk.y);
    P1chunk_string = prefix+"x = "+xpos+", y = "+ypos;
    P1chunk.setString(P1chunk_string);
    P1chunk.setCharacterSize(textsize);
    P1chunk.setPosition(50,50);
    return;
}

void debugDisplay::setP1pos(sf::Vector2f player_position)
{
    string xpos, ypos, prefix;
    prefix = "ABS POSITION: ";
    xpos = boost::lexical_cast<string>(player_position.x);
    ypos = boost::lexical_cast<string>(player_position.y);
    P1pos_string = prefix+"x = "+xpos+", y = "+ypos;
    P1pos.setString(P1pos_string);
    P1pos.setCharacterSize(textsize);
    P1pos.setPosition(50,50);
    return;
}

void debugDisplay::setP1tile(sf::Vector2f player_tile)
{
    string xpos, ypos, prefix;
    prefix = "TILE POSITION: ";
    xpos = boost::lexical_cast<string>(player_tile.x);
    ypos = boost::lexical_cast<string>(player_tile.y);
    P1tile_string = prefix+"x = "+xpos+", y = "+ypos;
    P1tile.setString(P1tile_string);
    P1tile.setCharacterSize(textsize);
    P1tile.setPosition(50,100);
    return;
}

void debugDisplay::setFPS(float current_fps)
{
    fps_string = boost::lexical_cast<string>((int)current_fps);
    FPS.setString("FPS: " + fps_string);
    FPS.setCharacterSize(textsize);
    FPS.setPosition(100,100);
}

void debugDisplay::setP1velocity(sf::Vector2f vel)
{
    string xvel, yvel, prefix;
    prefix = "PLAYER VELOCITY: ";
    xvel = boost::lexical_cast<string>(vel.x);
    yvel = boost::lexical_cast<string>(vel.y);
    P1velocity_string = prefix + "dx = " + xvel + ", dy = " + yvel;
    P1velocity.setString(P1velocity_string);
    P1velocity.setCharacterSize(textsize);
    P1velocity.setPosition(P1pos.getPosition().x + P1pos.getGlobalBounds().width + 25, P1pos.getPosition().y);
}

void debugDisplay::update()
{

}

void debugDisplay::toggleDisplay()
{
    displayed = !displayed;
}

void debugDisplay::setPosition(sf::Vector2f newpos)
{
    P1pos.setPosition(newpos.x + 10, newpos.y +10);
    P1tile.setPosition(newpos.x + 10, newpos.y +2*textsize+10);
    FPS.setPosition(newpos.x + 10, newpos.y +3*textsize+10);
    P1velocity.setPosition(newpos.x + 10, newpos.y +1*textsize+10);
    P1chunk.setPosition(newpos.x + 10, newpos.y +4*textsize+10);
}

