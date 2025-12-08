#pragma once

#include <SFML/Graphics.hpp>

class ArrowShape : public sf::Transformable, public sf::Drawable{
    public:
        ArrowShape(sf::Vector2f dir, sf::ConvexShape h, sf::RectangleShape b);
        ArrowShape(sf::Vector2f dir);

        void update();

        void setDirection(sf::Vector2f dir);

        sf::Vector2f getDirection() const;

        void setTip(sf::Vector2f dir);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Vector2f direction;
        sf::ConvexShape head;
        sf::RectangleShape body;
};