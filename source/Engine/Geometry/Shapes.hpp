#pragma once

#include <vector>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <variant>
#include <iostream>

#include "Engine/TypeConfiguration.hpp"
#include "Engine/Typelist.hpp"


namespace Trident{

    struct Line{
        Trident::Vector2 radialDir;
    };

    struct Circle{
        Trident::Scalar radius;
    };

    class Ellipse{
        Trident::Matrix2 transformation;

        public:
            Ellipse();
            Ellipse(Trident::Matrix2 m);
            Ellipse(Trident::Scalar width, Trident::Scalar height);
            Ellipse(Trident::Vector2 majorAxis, Trident::Scalar minorAxisScaleFactor);

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

    using shapes_t = Caravan::Typelist<Line, Circle, ConvexPolygon, SupportFunctor>;
    using Shape = Caravan::bundle<shapes_t, std::variant>;

    class Shape_SoA{
        std::vector<Shape> shapes;
        std::unordered_map<std::string, size_t> shapeNameMap;
    };

}

///////////////////////////////////////////////////////////

Trident::Vector2 support(Trident::Line shape, Trident::Vector2 dir);
Trident::Vector2 support(Trident::Circle shape, Trident::Vector2 dir);
Trident::Vector2 support(Trident::ConvexPolygon shape, Trident::Vector2 dir);
inline Trident::Vector2 support(Trident::SupportFunctor f, Trident::Vector2 dir){
    return f(dir);
}

////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<Trident::Vector2> GenerateVertices(T shape){
    static const int numSamples = 30;
    std::vector<Trident::Vector2> vertices;
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

Trident::Scalar CalculateArea(Trident::Circle shape, Trident::Vector2 dir);

template <class T>
Trident::Scalar CalculateArea(T& S){
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
Trident::Vector2 CalculateCentroid(T& S){
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
bool TestConvexity(T& S){
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

