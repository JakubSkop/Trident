#pragma once
#include "TypeConfiguration.hpp"


#include <vector>

class Body_SoA{
    std::vector<Trident::Scalar> invMasses;
    std::vector<Trident::Scalar> invInertias;

    std::vector<Trident::Scalar> globalRotations;
    std::vector<Trident::Vector2> globalTranslations;

};