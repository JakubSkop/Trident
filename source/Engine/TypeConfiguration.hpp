#pragma once

#include <numbers> 
#include "Maths/LinAlg.hpp"

namespace Trident {

    using Scalar = double;
    using Vector2 = linalg::Vector2D<Scalar>;
    using Matrix2 = linalg::Matrix2D<Scalar>;

    struct Entity{
        uint32_t id;
        uint32_t generation;
    };
    
}


