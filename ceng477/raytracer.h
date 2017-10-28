//
// Created by sbk on 28.10.2017.
//

#ifndef CENG477_RAYTRACER_H
#define CENG477_RAYTRACER_H
#include "parser.h"

class Ray {
    private:
        parser::Vec3f origin;
        parser::Vec3f direction;

    public:
        Ray(const parser::Vec3f& origin, const parser::Vec3f& direction);

        const parser::Vec3f &Origin() const;

        const parser::Vec3f &Direction() const;
};

class RayInfo{
public:
    parser::Material *material;
    parser::Vec3f rayPosition;
    parser::Vec3f rayNormal;
    float rayParameter;
    bool hitInfo;


};





#endif //CENG477_RAYTRACER_H
