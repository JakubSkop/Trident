#pragma once

#include "Engine/Geometry/Shapes.hpp"

class Collider_SoA{
    std::vector<size_t> shapeIndices;
    std::vector<size_t> bodyIndices;
    std::vector<Trident::Entity> entities;

    std::vector<Trident::Matrix2> localTransforms;
    std::vector<Trident::Vector2> localTranslations;

    std::vector<Trident::Scalar> frictionCoefficients;
    std::vector<Trident::Scalar> restitutionCoefficients;
    std::vector<Trident::Scalar> densities;

    std::vector<uint64_t> categoryMasks;
    std::vector<uint64_t> collisionMasks;

    public:

        const auto& getShapeIndices() const;
        const auto& getbodyIndices() const;
        const auto& getEntities() const;
        const auto& getLocalTransforms() const;
        const auto& getLocalTranslations() const;
        const auto& getFrictionCoefficients() const;
        const auto& getRestitutionCoefficients() const;
        const auto& getDensities() const;
        const auto& getCategoryMasks() const;
        const auto& getCollisionMasks() const;

};
