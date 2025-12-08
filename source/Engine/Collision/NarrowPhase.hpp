#pragma once

#include "Engine/TypeConfiguration.hpp"
#include "Engine/HelperFunctions.hpp"

#include <iostream>

template <class T>
auto CSLI_2D(T supportFunction, Trident::Vector2 initialNormal,  bool Clockwise = true){
    struct CLSI_Return_t{
        bool IsIntersecting;
        Trident::Vector2 normal;
    };

    Trident::Scalar mult = Clockwise ? 1: -1;

    Trident::Vector2 n_prev = initialNormal;
    Trident::Vector2 n = mult * RotateClockwise90(supportFunction(n_prev));

    for (auto i = 0; i < 5; i++){

        if (approx_equal(n, n_prev, 10.0)){
            return CLSI_Return_t{false, n};
        }

        n_prev = n;
        n = mult * RotateClockwise90(supportFunction(n_prev));
    }

    return CLSI_Return_t{true, n};
};

//n.dot(n_prev) > 0.95 * n.length()*n_prev.length()