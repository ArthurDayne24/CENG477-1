//
// Created by sbk on 28.10.2017.
//

#ifndef CENG477_RAYTRACER_H
#define CENG477_RAYTRACER_H
#include "parser.h"

parser::Vec3f operator+(const parser::Vec3f& v1, const parser::Vec3f& v2){
    parser::Vec3f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}

parser::Vec3f operator-(const parser::Vec3f& v1, const parser::Vec3f& v2){
    parser::Vec3f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

parser::Vec3f operator*(const parser::Vec3f& v1, float alpha){
    parser::Vec3f result;
    result.x = v1.x * alpha;
    result.y = v1.y * alpha;
    result.z = v1.z * alpha;

    return result;
}

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
    parser::Vec3f rayPosition;
    parser::Vec3f rayNormal;
    float rayParameter;
    bool hitInfo;


};





#endif //CENG477_RAYTRACER_H
