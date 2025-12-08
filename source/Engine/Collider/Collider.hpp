#pragma once

#include "Engine/Geometry/Shapes.hpp"


class Collider{
    Shape shape;
    Trident::Matrix2 localtransform;
    Trident::Vector2 localtranslation;

    Collider(Shape s);

};
