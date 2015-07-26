#ifndef FASTMATHS_H
#define FASTMATHS_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <random.hpp>


using namespace std;



class fastMaths
{
    public:
        fastMaths();
        virtual ~fastMaths();

        typedef boost::mt19937 RNGType;
        RNGType rng;


        vector<float> fastSin;
        vector<float> fastCos;
        vector<float> fastTan;

        float sqrt(float);
        float magnitude(sf::Vector2f);
        float Sin(float);
        float Cos(float);
        float Tan(float);
        float SinDeg(float);
        float CosDeg(float);
        float TanDeg(float);
        float round(float);

        float dotProduct(sf::Vector2f, sf::Vector2f);
        float angleBetween(sf::Vector2f, sf::Vector2f);
        float unitDotProduct(sf::Vector2f,sf::Vector2f);

        sf::Vector2f constantMag(float, sf::Vector2f);


        sf::Color randomColor();

        int randomInt(int, int);
        float randomFloat(float, float);

        int roundAndCast(float);
        bool contains(std::string, std::string);
        sf::Vector2f unitVector(sf::Vector2f);
        sf::Vector2f randomVector(float);

        float pi;
        float degToRad;
        float radToDeg;

    protected:
    private:
};

#endif // FASTMATHS_H
