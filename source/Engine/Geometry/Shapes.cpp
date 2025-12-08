#include "Shapes.hpp"

#include <numbers>
#include <stdexcept>
#include "Maths/LinAlg.hpp"

using namespace Trident;

ConvexPolygon::ConvexPolygon(std::vector<Trident::Vector2> ps) : points(ps){
    static Scalar tolerance = 0.01;
    auto centroid = calculateCentroid(*this);
    if (!approx_equal(centroid, {0,0}, tolerance)){
        throw std::invalid_argument("Not centred on the origin");
    }
    if (!testConvexity(*this)){
        throw std::invalid_argument("Not convex");
    }
};

const std::vector<Vector2>& ConvexPolygon::getPoints() const{
    return points;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

Trident::Vector2 support(Trident::Circle shape, Trident::Vector2 dir){
    return dir.normalized() * shape.radius;
}

Trident::Vector2 support(Trident::ConvexPolygon shape, Trident::Vector2 dir){
    size_t maxI = 0;
    double maxDot = 0;
    auto points = shape.getPoints();

    for (size_t i = 0; i < points.size(); ++i) {
        auto dot = points[i].dot(dir);
        if (dot > maxDot) {
            maxDot = dot;
            maxI = i;
        }
    }
    return points[maxI];
}

////////////////////////////////////////////////////////////////////////////////////////

Trident::Scalar calculateArea(Trident::Circle shape, Trident::Vector2 dir){
    return shape.radius * shape.radius * std::numbers::pi_v<Trident::Scalar>;
}
