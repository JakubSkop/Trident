#include "Collider.hpp"
#include "Centroid.hpp"


Collider::Collider(Shape s) : shape(s){
    auto [centroid, _] = CentroidAndArea(s);
    centroid 
};