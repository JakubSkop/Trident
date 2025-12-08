#include "Arrow.hpp"

ArrowShape::ArrowShape(sf::Vector2f dir, sf::ConvexShape h, sf::RectangleShape b) : direction(dir), head(h), body(b){};

void ArrowShape::update(){
    if (direction!=sf::Vector2f{0,0}){
        auto len = direction.length();
        auto angle = direction.angle();

        head = sf::ConvexShape();
        head.setPointCount(3);
        head.setPoint(0,sf::Vector2f(0, 0));
        head.setPoint(1, sf::Vector2f(-len/5, len/10));
        head.setPoint(2,sf::Vector2f(-len/5, -len/10));
        head.move(direction);
        head.rotate(angle);

        body = sf::RectangleShape({4*len/5, len/15});
        body.setOrigin({0, len/30});
        body.rotate(angle);
    } else {
        head = sf::ConvexShape();
        body = sf::RectangleShape();
    }
}

ArrowShape::ArrowShape(sf::Vector2f dir) : direction(dir){
    update();
};

void ArrowShape::setDirection(sf::Vector2f dir){
    direction = dir;
    update();
}

sf::Vector2f ArrowShape::getDirection() const{
    return direction;
}

void ArrowShape::setTip(sf::Vector2f dir){
    direction = dir-getPosition();
    update();
}

void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(head, states);
    target.draw(body, states);
};