#include "lib.hpp"
#include <SFML/Graphics.hpp>
#include "Engine/Geometry/Shapes.hpp"
#include "Graphics/Arrow.hpp"
#include "Engine/Collision/NarrowPhase.hpp"
#include "Conversions.hpp"

#include <iostream>
#include <map>

using namespace Trident;


library::library()
    : name {"Trident"}
{
    constexpr auto windowWidth = 1920u;
    constexpr auto windowHeight = 1080u;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project");
    window.setFramerateLimit(30);
    sf::View view;
    view.setCenter({0.0f, 0.0f});
    view.setSize({static_cast<float>(windowWidth), -static_cast<float>(windowHeight)});
    window.setView(view);

    ArrowShape arrow1({0,0});
    auto c = Circle(1);
    std::cout << calculateCentroid(c);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        auto s = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        arrow1.setTip(s);
        
        //std::cout << circle2.shape.translation;

        window.clear();

        window.draw(arrow1);

        window.display();
    }

}


