#ifndef WALL_H
#define WALL_H

#include <tile.h>


class Wall : public Tile
{
    public:
        Wall();
        Wall(const sf::Texture &);
        virtual ~Wall();

        virtual void hits(Content*);

        int rect_t,rect_l;
    private:

};

class TopWall : public Wall
{
    public:
        TopWall();
        virtual ~TopWall();

    private:
};

class SecondTopWall : public Wall
{
    public:
        SecondTopWall();
        virtual ~SecondTopWall();

    private:
};

class TopTopWall : public Wall
{
    public:
        TopTopWall();
        virtual ~TopTopWall();

    private:
};

class BotWall : public Wall
{
    public:
        BotWall();
        virtual ~BotWall();
    private:
};

class SecondBotWall : public Wall
{
    public:
        SecondBotWall();
        virtual ~SecondBotWall();
    private:
};

class BotBotWall : public Wall
{
    public:
        BotBotWall();
        virtual ~BotBotWall();
    private:
};

class RightWall : public Wall
{
    public:
        RightWall();
        virtual ~RightWall();
    private:
};

class LeftWall : public Wall
{
    public:
        LeftWall();
        virtual ~LeftWall();
    private:
};

class TRCornerWall : public Wall
{
    public:
        TRCornerWall();
        virtual ~TRCornerWall();
    private:
};

class TLCornerWall : public Wall
{
    public:
        TLCornerWall();
        virtual ~TLCornerWall();
    private:
};

class BRCornerWall : public Wall
{
    public:
        BRCornerWall();
        virtual ~BRCornerWall();
    private:
};

class BLCornerWall : public Wall
{
    public:
        BLCornerWall();
        virtual ~BLCornerWall();
    private:
};


#endif // WALL_H
