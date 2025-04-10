#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Flower
{
private:
    sf::RenderWindow* window;
    sf::CircleShape center;
    std::vector<sf::CircleShape> petals;
    sf::RectangleShape stem;

    // Animation properties
    sf::Clock frameClock;
    float centerRadius;
    float minRadius;
    float maxRadius;
    bool growing;

public:
    Flower(sf::RenderWindow* window);

    ~Flower() = default;

    Flower(const Flower&) = delete;

    void draw();
};