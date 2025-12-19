#include "Collider.hpp"

using namespace Trident;

const auto& Collider_SoA::getShapeIndices() const{
    return shapeIndices;
}
const auto& Collider_SoA::getbodyIndices() const{
    return bodyIndices;
}
const auto& Collider_SoA::getEntities() const{
    return entities;
}
const auto& Collider_SoA::getLocalTransforms() const{
    return localTransforms;
}
const auto& Collider_SoA::getLocalTranslations() const{
    return localTranslations;
}
const auto& Collider_SoA::getFrictionCoefficients() const{
    return frictionCoefficients;
}
const auto& Collider_SoA::getRestitutionCoefficients() const{
    return restitutionCoefficients;
}
const auto& Collider_SoA::getDensities() const{
    return densities;
}
const auto& Collider_SoA::getCategoryMasks() const{
    return categoryMasks;
};
const auto& Collider_SoA::getCollisionMasks() const{
    return collisionMasks;
};