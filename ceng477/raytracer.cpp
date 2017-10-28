//
// Created by sbk on 28.10.2017.
//
#include <iostream>
#include <limits>
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
    result = (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]))
           - (matrix[1][0] * (matrix[2][2] * matrix[0][1] - matrix[0][2] * matrix[2][1]))
           + (matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]));
    return result;
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

/*
bool triangleIntersection(const parser::Triangle& triangle =NULL , const parser::Scene& scene, const Ray& ray, RayInfo& rayHitInfo, bool isTriangle, const parser::Face& face=NULL){
    int indice_v0,indice_v1,indice_v2;
    if(isTriangle){
        indice_v0=triangle.indices.v0_id;
        indice_v1=triangle.indices.v1_id;
        indice_v2=triangle.indices.v2_id;
    }else{
        indice_v0=face.v0_id;
        indice_v1=face.v1_id;
        indice_v2=face.v2_id;

    }

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
    float detGama = calculateDeterminant(gamaMatrix);
    float detBeta = calculateDeterminant(betaMatrix);
    float detT = calculateDeterminant(tMatrix);

    float beta = detBeta/detA;
    float gama = detGama/detA;
    float t = detT/detA;


    if (t > 0 && beta + gama <= 1 && 0 <= beta && 0 <= gama){

        if (t < rayHitInfo.rayParameter) {
            rayHitInfo.materialId = triangle.material_id;
            rayHitInfo.rayParameter = t;
            rayHitInfo.rayPosition = origin + direction * rayHitInfo.rayParameter;
            rayHitInfo.rayNormal = calculateCrossProduct(v2-v1,v0-v1);
            rayHitInfo.hitInfo = true;
        }

        return  true;
    }

    return  false;

}
*/

bool faceIntersection(const parser::Face& face , const parser::Scene& scene, const Ray& ray, RayInfo& rayHitInfo){
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
    if(detA > 0)
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
        }

        return  true;
    }

    return  false;

}


int main(int argc, char* argv[]) {
    parser::Scene scene;

    scene.loadFromXml("/home/sbk/CLionProjects/ceng477/cmake-build-debug/simple.xml");
//    scene.loadFromXml("hw1_sample_scenes/simple.xml");

    //scene.loadFromXml(argv[1]);
    unsigned char* image;
    unsigned long cameraSize = scene.cameras.size();
    unsigned long j,k,l,f1;
    // each camera
    for (int i = 0;  i< cameraSize; i++) {
        //calculateRay
        parser::Vec3f m,q,u;

        parser::Camera camera = scene.cameras[i];
        m = camera.position + (camera.gaze*camera.near_distance);
        u = calculateCrossProduct(camera.up,camera.gaze);
        q = m + (u*camera.near_plane.x) +(camera.up*camera.near_plane.w);
        int imageWidth = camera.image_width;
        int imageHeight = camera.image_height;
        image = new unsigned char [imageWidth * imageHeight * 3];
        // each pixel
        unsigned long counter = 0;
        for(j=0; j<imageWidth;j++){
            for(k = 0; k<imageHeight; k++){
                float su,sv;

                su = (camera.near_plane.y-camera.near_plane.x)*(j+0.5)/imageWidth;
                sv = (camera.near_plane.w-camera.near_plane.z)*(k+0.5)/imageHeight;
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
                unsigned long meshSize = scene.meshes.size();
                for(l = 0; l<meshSize;l++){

                    parser::Mesh *mesh = &(scene.meshes[l]);

                    unsigned long faceSize= mesh->faces.size();
                    //Each face
                    for(f1=0;f1<faceSize;f1++){

                        parser::Face *face = &mesh->faces[f1];
                        faceIntersection(*face,scene,ray,rayHitInfo);

//                        std::cout<< "height: " << k << "--width:" << j << std::endl;


                        if (!rayHitInfo.hitInfo) {
                            image[counter++] = (unsigned char)scene.background_color.x;
                            image[counter++] = (unsigned char)scene.background_color.y;
                            image[counter++] = (unsigned char)scene.background_color.z;

                        }else{
                            image[counter++] = 255;
                            image[counter++] = 255;
                            image[counter++] = 255;

                        }

                    }

                }
            }
            if(j>399)
                write_ppm("/home/sbk/CLionProjects/ceng477/cmake-build-debug/simple.ppm", image, imageWidth, imageHeight);


        }

        //write_ppm(argv[2], image, imageWidth, imageHeight);
//        write_ppm("hello.ppm", image, imageWidth, imageHeight);



    }


    return  0;
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
    //write_ppm(argv[2], image, width, height);
}