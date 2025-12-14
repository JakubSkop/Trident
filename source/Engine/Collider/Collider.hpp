#pragma once

#include "Engine/Geometry/Shapes.hpp"


struct Collider{
    size_t shapeIndex;
    size_t bodyIndex;
    Trident::Matrix2 localTransform;
    Trident::Vector2 localTranslation;

    Trident::Scalar frictionCoefficient;
    Trident::Scalar restitutionCoefficient;
    Trident::Scalar density;
};

class Collider_SoA{
    std::vector<size_t> shapeIndices;
    std::vector<size_t> bodyIndices;
    std::vector<Trident::Matrix2> localTransforms;
    std::vector<Trident::Vector2> localTranslations;

    std::vector<Trident::Scalar> frictionCoefficients;
    std::vector<Trident::Scalar> restitutionCoefficients;
    std::vector<Trident::Scalar> densities;

    public:

        const auto& getShapeIndices() const;
        const auto& getbodyIndices() const;
        const auto& getLocalTransforms() const;
        const auto& getLocalTranslations() const;
        const auto& getFrictionCoefficients() const;
        const auto& getRestitutionCoefficients() const;
        const auto& getDensities() const;
};
