#include "Flower.h"
#include <cmath>

Flower::Flower(sf::RenderWindow* window) : window(window)
{
    minRadius = 15;
    maxRadius = 20;
    centerRadius = maxRadius;
    growing = false;

    center.setRadius(centerRadius);
    center.setFillColor(sf::Color::Yellow);
    center.setPosition(sf::Vector2f(100 - centerRadius, 100 - centerRadius));
    center.setOrigin(sf::Vector2f(0, 0));

    const int petalCount = 6;
    for (int i = 0; i < petalCount; ++i) {
        sf::CircleShape petal;
        petal.setRadius(26);
        petal.setFillColor(sf::Color::Red);
        petals.push_back(petal);
    }

    // Create stem
    stem.setSize(sf::Vector2f(8, 80));
    stem.setFillColor(sf::Color(0, 150, 0));
    stem.setPosition(sf::Vector2f(96, 100));
}

void Flower::draw()
{
    float elapsed = frameClock.getElapsedTime().asSeconds();
    if (elapsed > 0.04) {
        if (growing) {
            centerRadius += 0.2;
            if (centerRadius >= maxRadius) {
                centerRadius = maxRadius;
                growing = false;
            }
        }
        else {
            centerRadius -= 0.2;
            if (centerRadius <= minRadius) {
                centerRadius = minRadius;
                growing = true;
            }
        }

        center.setRadius(centerRadius);
        center.setPosition(sf::Vector2f(100 - centerRadius, 100 - centerRadius));

        frameClock.restart();
    }

    window->draw(stem);

    const float petalDistance = centerRadius + 15.f;
    const int petalCount = petals.size();

    for (int i = 0; i < petalCount; ++i) {
        float angle = i * 2 * 3.14 / petalCount;
        float x = 100 + cos(angle) * petalDistance - petals[i].getRadius();
        float y = 100 + sin(angle) * petalDistance - petals[i].getRadius();

        petals[i].setPosition(sf::Vector2f(x, y));
        window->draw(petals[i]);
    }

    window->draw(center);
}