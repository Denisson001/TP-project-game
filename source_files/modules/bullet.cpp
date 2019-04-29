#include <bullet.h>

#include <game_settings.h>

Bullet::Bullet(sf::Color color, Vector position, Vector vector, double damage, double range):
position(position), vector(vector), damage(damage), range(range){
    std::shared_ptr<sf::ConvexShape> polygon = std::make_shared<sf::ConvexShape>(3);
    polygon->setPoint(0, sf::Vector2f(0, 0));
    polygon->setPoint(1, sf::Vector2f(18, 0));
    polygon->setPoint(2, sf::Vector2f(9, 22));
    shape = polygon;
    shape->setOrigin(9, 11);
    shape->setFillColor(color);
    shape->rotate(vector.getAngleInDegrees() - 90);
    shape->setScale(BULLET_SHAPE_SCALE_X, BULLET_SHAPE_SCALE_Y);
}

void Bullet::update(double time){
    position += vector * time;
    range -= (vector * time).length();
}

sf::FloatRect Bullet::getBounds(){
    shape->setPosition(position.x, position.y);
    sf::FloatRect bounds = shape->getGlobalBounds();
    bounds.left += bounds.width * (1 - BULLET_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
    bounds.top += bounds.height * (1 - BULLET_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
    bounds.height *= BULLET_SHAPE_BOUNDS_COEFFICIENT;
    bounds.width *= BULLET_SHAPE_BOUNDS_COEFFICIENT;
    return bounds;
}
