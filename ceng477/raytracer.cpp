//
// Created by sbk on 28.10.2017.
//
#include <iostream>
#include "parser.h"
#include "ppm.h"
#include "raytracer.h"


Ray::Ray(const parser::Vec3f &origin, const parser::Vec3f &direction):origin(origin), direction(direction) {
}

const parser::Vec3f & Ray::Origin() const {
    return origin;
}

const parser::Vec3f& Ray::Direction() const {
    return direction;
}

float calculateDeterminant(float matrix[3][3]){
    float result;
    result = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]))
           - (matrix[1][0] * (matrix[2][2] * matrix[0][1] - matrix[0][2] * matrix[2][1]))
           + (matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
    return result;
}

parser::Vec3f getVertexFromIndeces(int vertex,const parser::Scene& scene){
    return scene.vertex_data[vertex-1];
}

void triangleIntersection(const parser::Triangle& triangle, const parser::Scene& scene, const Ray& ray, RayInfo& rayInfo){
    int indice_v0=triangle.indices.v0_id;
    int indice_v1=triangle.indices.v1_id;
    int indice_v2=triangle.indices.v2_id;

    parser::Vec3f v0 = getVertexFromIndeces(indice_v0,scene);
    parser::Vec3f v1 = getVertexFromIndeces(indice_v1,scene);
    parser::Vec3f v2 = getVertexFromIndeces(indice_v2,scene);

    parser::Vec3f direction = ray.Direction();
    parser::Vec3f origin = ray.Origin();

    //Cramer's rule
    float matrixA[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, direction.x},
            {v0.y-v1.y, v0.y-v2.y, direction.y},
            {v0.z-v1.z, v0.z-v2.z, direction.z}
    };

    float betaMatrix[3][3] = {
            {v0.x-origin.x, v0.x-v2.x, direction.x},
            {v0.y-origin.y, v0.y-v2.y, direction.y},
            {v0.z-origin.z, v0.z-v2.z, direction.z}

    };

    float alphaMatrix[3][3] = {
            {v0.x-v1.x, v0.x-origin.x, direction.x},
            {v0.y-v1.y, v0.y-origin.y, direction.y},
            {v0.z-v1.z, v0.z-origin.z, direction.z}

    };

    float tMatrix[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, v0.x-origin.x},
            {v0.y-v1.y, v0.y-v2.y, v0.y-origin.y},
            {v0.z-v1.z, v0.z-v2.z, v0.z-origin.z}

    };

    float detA = calculateDeterminant(matrixA);
    float detAlpha = calculateDeterminant(alphaMatrix);
    float detBeta = calculateDeterminant(betaMatrix);
    float detT = calculateDeterminant(tMatrix);

    float beta = detBeta/detA;
    float alpha = detAlpha/detA;
    float t = detT/detA;
}




int main(int argc, char* argv[]) {
    parser::Scene scene;

    scene.loadFromXml(argv[1]);

    scene.triangles[0].
            scene.vertex_data[5].
/*
    int i = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int colIdx = x / columnWidth;
            image[i++] = BAR_COLOR[colIdx][0];
            image[i++] = BAR_COLOR[colIdx][1];
            image[i++] = BAR_COLOR[colIdx][2];
        }
    }

    */
    write_ppm(argv[2], image, width, height);
}