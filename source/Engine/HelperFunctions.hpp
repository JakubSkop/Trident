#pragma once

#include "TypeConfiguration.hpp"

inline Trident::Vector2 RotateClockwise90(Trident::Vector2 vec){
    return {vec[1], -vec[0]};
}

inline Trident::Vector2 RotateAntiClockwise90(Trident::Vector2 vec){
    return {-vec[1], vec[0]};
}

inline Trident::Vector2 Rotate(Trident::Vector2 vec, Trident::Scalar angle){
    return {std::cos(angle)*vec[0] - std::sin(angle)*vec[1], std::sin(angle)*vec[0] + std::cos(angle)*vec[1]};
}

inline auto CrossProd2D(Trident::Vector2 vec1, Trident::Vector2 vec2){
    return vec1[0]*vec2[1] - vec1[1]*vec2[0];
}