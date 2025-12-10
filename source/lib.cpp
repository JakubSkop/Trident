#include "lib.hpp"
#include <SFML/Graphics.hpp>
#include "Engine/Geometry/Shapes.hpp"
#include "Graphics/Arrow.hpp"
#include "Engine/Collision/NarrowPhase.hpp"
#include "Conversions.hpp"
#include "Engine/Typelist.hpp"

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
    auto c = ConvexPolygon({{1,-1},{1,1},{-1,1},{-1,-1}});

    using empty = Caravan::Typelist<>;
    using floatingTypes = Caravan::Typelist<float, double>;
    using integralTypes = Caravan::Typelist<short, int, long>;
    using doubledIntegralTypes = Caravan::add<integralTypes, integralTypes>;
    using noInts = Caravan::remove<Caravan::Typelist<>, int>;
    using N = Caravan::removeDuplicates<doubledIntegralTypes>;
    using K = Caravan::select<N, 0,2>;
    using L = Caravan::slice<doubledIntegralTypes,2,4>;
    using P = Caravan::pop<doubledIntegralTypes,1,2,3>;
    using B = Caravan::bundle<integralTypes, std::tuple>;
    using U = Caravan::unbundle<B>;
    using C = Caravan::compose<integralTypes, std::vector, std::optional>;
    using D = Caravan::decompose<C, std::optional>;
    //Caravan::print<D>();
    std::cout << Caravan::compareEqual<integralTypes,integralTypes>();

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


