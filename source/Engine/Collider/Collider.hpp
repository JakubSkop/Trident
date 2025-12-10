#pragma once

#include "Engine/Geometry/Shapes.hpp"


class Collider{
    Trident::Shape shape;
    Trident::Matrix2 localtransform;
    Trident::Vector2 localtranslation;

    Trident::Scalar frictionCoefficient;
    Trident::Scalar RestitutionCoefficient;
    Trident::Scalar density;

    Collider(Trident::Shape s);

};
