#pragma once

#include "Maths/LinAlg.hpp"
#include <SFML/Graphics.hpp>

template <typename T>
sf::Vector2<T> convert(linalg::Vector2D<T> vec){
    return sf::Vector2<T>(vec[0], vec[1]);
};

template <typename T>
linalg::Vector2D<T> convert(sf::Vector2<T> vec){
    return linalg::Vector2D<T>{vec.x, vec.y};
};

template <typename T, typename U>
linalg::Vector2D<T> convert(sf::Vector2<U> vec){
    return linalg::Vector2D<T>{static_cast<T>(vec.x), static_cast<T>(vec.y)};
};

