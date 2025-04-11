#include "Flower.h"
#include <cmath>

Flower::Flower(sf::RenderWindow* window) : window(window)
{
    minRadius = 15.f;
    maxRadius = 20.f;
    centerRadius = maxRadius;
    growing = false;

    center.setRadius(centerRadius);
    center.setFillColor(sf::Color::Yellow);
    center.setPosition(sf::Vector2f(100.f - centerRadius, 100.f - centerRadius));
    center.setOrigin(sf::Vector2f(0.f, 0.f));

    const int petalCount = 6;
    for (int i = 0; i < petalCount; ++i) {
        sf::CircleShape petal;
        petal.setRadius(26.f);
        petal.setFillColor(sf::Color::Red);
        petals.push_back(petal);
    }

    // Create stem
    stem.setSize(sf::Vector2f(8.f, 80.f));
    stem.setFillColor(sf::Color(0, 150, 0));
    stem.setPosition(sf::Vector2f(96.f, 100.f));
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
        center.setPosition(sf::Vector2f(100.f - centerRadius, 100.f - centerRadius));

        frameClock.restart();
    }

    window->draw(stem);

    const float petalDistance = centerRadius + 15.f;
    const int petalCount = petals.size();

    for (int i = 0; i < petalCount; ++i) {
        float angle = static_cast<float>(i) * 2.f * 3.14f / petalCount;
        float x = 100.f + cos(angle) * petalDistance - petals[i].getRadius();
        float y = 100.f + sin(angle) * petalDistance - petals[i].getRadius();

        petals[i].setPosition(sf::Vector2f(x, y));
        window->draw(petals[i]);
    }

    window->draw(center);
}