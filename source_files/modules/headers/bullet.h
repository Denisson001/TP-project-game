#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <geometry.h>

class Bullet{
public:
    std::shared_ptr<sf::Shape> shape;
    Vector position, vector;
    double damage, range;
    Bullet(sf::Color color, Vector position, Vector vector, double damage, double range);
    void update(double time);
    sf::FloatRect getBounds();
};
