//
// Created by sbk on 28.10.2017.
//
#include <iostream>
#include <limits>
#include "parser.h"
#include "ppm.h"
#include "raytracer.h"
#include "math.h"

RayInfo::RayInfo(){
    this->rayParameter = std::numeric_limits<float>::max();
    this->hitInfo = false;

};

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
    result = (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]))
           - (matrix[1][0] * (matrix[2][2] * matrix[0][1] - matrix[0][2] * matrix[2][1]))
           + (matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]));
    return result;
}

float calculateDotProduct(const parser::Vec3f& v1, const parser::Vec3f& v2){
    float result = 0;
    result += (v1.x * v2.x);
    result += (v1.y * v2.y);
    result += (v1.z * v2.z);

    return  result;

}

parser::Vec3f getVertexFromIndeces(int vertex,const parser::Scene& scene){
    return scene.vertex_data[vertex-1];
}

parser::Vec3f calculateCrossProduct(const parser::Vec3f &v1, const parser::Vec3f &v2){
    parser::Vec3f result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

bool triangleIntersection(const parser::Triangle& triangle , const parser::Scene& scene, const Ray& ray, RayInfo& rayHitInfo, const parser::Material& material){




    parser::Vec3f v0 = getVertexFromIndeces(triangle.indices.v0_id,scene);
    parser::Vec3f v1 = getVertexFromIndeces(triangle.indices.v1_id,scene);
    parser::Vec3f v2 = getVertexFromIndeces(triangle.indices.v2_id,scene);

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

    float gamaMatrix[3][3] = {
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
    if(detA == 0.0)
        return false;
    float detGama = calculateDeterminant(gamaMatrix);
    float detBeta = calculateDeterminant(betaMatrix);
    float detT = calculateDeterminant(tMatrix);

    float beta = detBeta/detA;
    float gama = detGama/detA;
    float t = detT/detA;


    if (t > 0 && beta + gama <= 1 && 0 <= beta && 0 <= gama){

        if (t < rayHitInfo.rayParameter) {
            rayHitInfo.rayParameter = t;
            rayHitInfo.rayPosition = origin + direction * rayHitInfo.rayParameter;
            rayHitInfo.rayNormal = calculateCrossProduct(v2-v1,v0-v1);
            rayHitInfo.hitInfo = true;
            rayHitInfo.material = material;
            return  true;
        }


    }

    return  false;

}


bool faceIntersection(const parser::Face& face , const parser::Scene& scene, const Ray& ray, RayInfo& rayHitInfo, const parser::Material& material){
    int indice_v0,indice_v1,indice_v2;

    indice_v0=face.v0_id;
    indice_v1=face.v1_id;
    indice_v2=face.v2_id;



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

    float gamaMatrix[3][3] = {
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
    if(detA == 0.0)
        return false;
    float detGama = calculateDeterminant(gamaMatrix);
    float detBeta = calculateDeterminant(betaMatrix);
    float detT = calculateDeterminant(tMatrix);

    float beta = detBeta/detA;
    float gama = detGama/detA;
    float t = detT/detA;


    if (t > 0 && beta + gama <= 1 && 0 <= beta && 0 <= gama){

        if (t < rayHitInfo.rayParameter) {
            rayHitInfo.rayParameter = t;
            rayHitInfo.rayPosition = origin + direction * rayHitInfo.rayParameter;
            rayHitInfo.rayNormal = calculateCrossProduct(v2-v1,v0-v1);
            rayHitInfo.hitInfo = true;
            rayHitInfo.material = material;
            return  true;
        }


    }

    return  false;

}


bool sphereIntersection(const parser::Sphere& sphere, const parser::Scene& scene, const Ray& ray, RayInfo& rayHitInfo, parser::Material& material){
    parser::Vec3f c = getVertexFromIndeces(sphere.center_vertex_id,scene);

    parser::Vec3f direction = ray.Direction();
    parser::Vec3f origin = ray.Origin();

    float A = calculateDotProduct(direction,direction);
    parser::Vec3f originMinusCenter = origin-c;
    float B = 2*(calculateDotProduct(direction,originMinusCenter));
    float C = (calculateDotProduct(originMinusCenter,originMinusCenter)) - (sphere.radius*sphere.radius);

    //Calculate delta
    float delta = sqrt(B*B - 4*A*C);
    if(delta>=0.0){
        float t1 = (-1*B + delta) / 2*A;
        float t2 = (-1*B - delta) / 2*A;
        float t = 0;
        if(t1>=t2)
            t = t2;
        else
            t = t1;

        if (t2 < rayHitInfo.rayParameter) {
            rayHitInfo.rayParameter = t;
            rayHitInfo.rayPosition = origin + direction * rayHitInfo.rayParameter;

            parser::Vec3f rayMinusCenter = rayHitInfo.rayPosition-c;
            rayHitInfo.rayNormal = rayMinusCenter*(1.0/sphere.radius);

            rayHitInfo.hitInfo = true;
            rayHitInfo.material = material;
            return  true;
        }
    }
    return  false;



}


int main(int argc, char* argv[]) {
    parser::Scene scene;

    //scene.loadFromXml("/home/sbk/CLionProjects/ceng477/cmake-build-debug/bunny.xml");
//    scene.loadFromXml("hw1_sample_scenes/simple.xml");

    scene.loadFromXml(argv[1]);
    unsigned char* image;
    int cameraSize = scene.cameras.size();
    int j,k,l,f1;
    // each camera
    for (int i = 0;  i< cameraSize; i++) {
        //calculateRay
        parser::Vec3f m,q,u;

        parser::Camera camera = scene.cameras[i];
        m = camera.position + (camera.gaze*camera.near_distance);
        u = calculateCrossProduct(camera.gaze,camera.up);
        q = m + (u*camera.near_plane.x) +(camera.up*camera.near_plane.w);
        int imageWidth = camera.image_width;
        int imageHeight = camera.image_height;
        image = new unsigned char [imageWidth * imageHeight * 3];

        // each pixel
        for(j=0; j<imageHeight;j++){
            for(k = 0; k<imageWidth; k++){
                float su,sv;

                su = (camera.near_plane.y-camera.near_plane.x)*(k+0.5)/imageWidth;
                sv = (camera.near_plane.w-camera.near_plane.z)*(j+0.5)/imageHeight;
                //std::cout<<"su->" << su << "sv->" << sv <<std::endl;

                parser::Vec3f s;
                s = q + (u*su) - (camera.up *sv);

                parser::Vec3f origin = camera.position;
                parser::Vec3f direction = s - camera.position;
                Ray ray(origin, direction);

                // Ray Hit
                RayInfo rayHitInfo;
                rayHitInfo.rayParameter = std::numeric_limits<float>::max();
                rayHitInfo.hitInfo = false;

                //Mesh
                int meshSize = scene.meshes.size();
                for(l = 0; l<meshSize;l++){

                    parser::Mesh *mesh = &(scene.meshes[l]);

                    int faceSize= mesh->faces.size();
                    //Each face
                    for(f1=0;f1<faceSize;f1++){

                        parser::Face *face = &mesh->faces[f1];
                        faceIntersection(*face,scene,ray,rayHitInfo,scene.materials[mesh->material_id-1]);

                    }

                }

                //Triangle
                int triangleSize = scene.triangles.size();
                for(l=0; l<triangleSize;l++){
                    parser::Triangle *triangle = &scene.triangles[l];
                    triangleIntersection(*triangle,scene,ray,rayHitInfo,scene.materials[triangle->material_id-1]);
                }

                //Sphere
                int sphereSize = scene.spheres.size();
                for(l=0; l<triangleSize;l++){
                    parser::Sphere *sphere = &scene.spheres[l];
                    sphereIntersection(*sphere,scene,ray,rayHitInfo,scene.materials[sphere->material_id-1]);
                }


                if (!rayHitInfo.hitInfo) {
                    image[3*(j*imageHeight+k)] = (unsigned char)scene.background_color.x;
                    image[3*(j*imageHeight+k)+1] = (unsigned char)scene.background_color.y;
                    image[3*(j*imageHeight+k)+2] = (unsigned char)scene.background_color.z;

                }else{
                    image[3*(j*imageHeight+k)] = 255;
                    image[3*(j*imageHeight+k)+1] = 255;
                    image[3*(j*imageHeight+k)+2] = 255;


                }
            }
            //if(j>399)
                //write_ppm("/home/sbk/CLionProjects/ceng477/cmake-build-debug/simple.ppm", image, imageWidth, imageHeight);


        }

        write_ppm(argv[2], image, imageWidth, imageHeight);
//        write_ppm("hello.ppm", image, imageWidth, imageHeight);
        //write_ppm("/home/sbk/CLionProjects/ceng477/cmake-build-debug/bunny.ppm", image, imageWidth, imageHeight);


    }


    return  0;

}