#pragma once

#include <vector>
#include <tuple>
#include <memory>
#include <variant>
#include <iostream>

#include "Engine/TypeConfiguration.hpp"


namespace Trident{

    struct Circle{
        Trident::Scalar radius;
    };

    class ConvexPolygon{
        std::vector<Trident::Vector2> points;

        public:
            ConvexPolygon(std::vector<Trident::Vector2> ps);
            const std::vector<Trident::Vector2>& getPoints() const;
    };

    class SupportFunctor{
        const Trident::Vector2(supportFunctionPtr)(Trident::Vector2);

        public:
            inline Trident::Vector2 operator()(Trident::Vector2 dir){
                return supportFunctionPtr(dir);
            };
    };

    using Shape = std::variant<Circle, ConvexPolygon, SupportFunctor>;

    struct ShapeContainer{
        std::tuple<std::vector<Circle>, std::vector<ConvexPolygon>, std::vector<SupportFunctor>> shapeLists;
    };

}

///////////////////////////////////////////////////////////

Trident::Vector2 support(Trident::Circle shape, Trident::Vector2 dir);
Trident::Vector2 support(Trident::ConvexPolygon shape, Trident::Vector2 dir);

inline Trident::Vector2 support(Trident::SupportFunctor f, Trident::Vector2 dir){
    return f(dir);
}

////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<Trident::Vector2> GenerateVertices(T shape){
    static const int numSamples = 30;
    std::vector<Trident::Vector2> vertices{};
    for (auto i = 0; i < numSamples; i += 1 ){

        auto theta = i*2*std::numbers::pi/numSamples;
        Trident::Vector2 dir{std::cos(theta), std::sin(theta)};
        auto point = support(shape, dir);

        if (vertices.empty() || (point != vertices.back() && point != vertices.front())){
            vertices.push_back(point);
        }
    }
    return vertices;
};

////////////////////////////////////////////////////////////////////////////

Trident::Scalar calculateArea(Trident::Circle shape, Trident::Vector2 dir);

template <class T>
Trident::Scalar calculateArea(T& S){
    auto vertices = GenerateVertices(S);
    Trident::Scalar area{0};

    for (auto index = 0; index < vertices.size(); index++){
        auto next_index =  (index+1)%vertices.size();
        area += vertices[index].cross(vertices[next_index]);
    }
    area /= 2;
    return area;
};

////////////////////////////////////////////////////////////////////////////

template <class T>
Trident::Vector2 calculateCentroid(T& S){
    auto vertices = GenerateVertices(S);
    Trident::Vector2 centroid{0,0};
    Trident::Scalar doubleArea{0};

    for (auto index = 0; index < vertices.size(); index++){
        auto next_index =  (index+1)%vertices.size();
        auto v = vertices[index];
        auto next_v = vertices[next_index];

        auto termA = v.cross(next_v);
        centroid += termA * (v + next_v);
        doubleArea += termA;
    }

    centroid /= 3*doubleArea;
    return centroid;
};

/////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool testConvexity(T& S){
    auto vertices = GenerateVertices(S);

    for (auto index = 1; index <= vertices.size(); index++){
        auto v = vertices[index%vertices.size()];
        auto next_v = vertices[(index+1)%vertices.size()];
        auto prev_v = vertices[index-1];

        if ((next_v - v).cross(prev_v - v) <= 0){
            return false;
        }
    }

    return true;
};

