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

float lengthOfVector(const parser::Vec3f& v1){
    float result = 0;
    result = sqrtf(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
    return result;
}

float distanceOfVectors(const parser::Vec3f& v1, const parser::Vec3f& v2){
    float result = 0;
    result += (v2.x-v1.x)*(v2.x-v1.x);
    result += (v2.y-v1.y)*(v2.y-v1.y);
    result += (v2.z-v1.z)*(v2.z-v1.z);

    result = sqrtf(result);
    return result;
}

parser::Vec3f coloring(Ray& ray, int counterForDepth, RayInfo& rayHitInfo, parser::Scene& scene, parser::Camera& camera){

    parser::Vec3f color;
    if (counterForDepth < 0) {
        color.x = 0;
        color.y = 0;
        color.z = 0;
        return color;
    }



    color.x = rayHitInfo.material.ambient.x * scene.ambient_light.x;
    color.y = rayHitInfo.material.ambient.y * scene.ambient_light.y;
    color.z = rayHitInfo.material.ambient.z * scene.ambient_light.z;

    int lightSize = scene.point_lights.size();
    int l;

    for(l=0;l<lightSize;l++){
        parser::PointLight *pointLight = &(scene.point_lights[l]);
        parser::Vec3f pointToRayHit = pointLight->position - rayHitInfo.rayPosition;

        parser::Vec3f Wi= (pointToRayHit) * (1/(lengthOfVector(pointToRayHit)));

        bool sphereShadowFlag = false;
        bool dummyFlag = false;
        bool meshShadowFlag = false;

        Ray shadowRay(rayHitInfo.rayPosition + Wi * scene.shadow_ray_epsilon, Wi);
        RayInfo shadowHitInfo;

        float tLight = (pointLight->position - shadowRay.Origin()).x
                       / shadowRay.Direction().x;


        //Sphere Shadow

        int sphereSize = scene.spheres.size();
        for(l=0; l<sphereSize;l++){
            parser::Sphere *sphere = &scene.spheres[l];
            sphereIntersection(*sphere,scene,shadowRay,shadowHitInfo,scene.materials[sphere->material_id-1]);
            // if shadow hit object
            if(shadowHitInfo.hitInfo){
                if(tLight > shadowHitInfo.rayParameter){
                    sphereShadowFlag = true;
                    dummyFlag = true;
                }

            }
        }

        // Mesh Shadow
        if(!sphereShadowFlag){
            //Mesh
            int meshSize = scene.meshes.size(),f1;
            for(l = 0; l<meshSize;l++){

                parser::Mesh *mesh = &(scene.meshes[l]);

                int faceSize= mesh->faces.size();
                //Each face
                for(f1=0;f1<faceSize;f1++){

                    parser::Face *face = &mesh->faces[f1];
                    faceIntersection(*face,scene,shadowRay,shadowHitInfo,scene.materials[mesh->material_id-1]);
                    // if shadow hit object
                    if(shadowHitInfo.hitInfo){
                        if(tLight > shadowHitInfo.rayParameter){
                            meshShadowFlag = true;
                            dummyFlag = true;
                        }

                    }

                }

            }
        }


        //TriangleShadow
        if(!meshShadowFlag || !sphereShadowFlag){
            //Triangle
            int triangleSize = scene.triangles.size();
            for(l=0; l<triangleSize;l++){
                parser::Triangle *triangle = &scene.triangles[l];
                triangleIntersection(*triangle,scene,shadowRay,shadowHitInfo,scene.materials[triangle->material_id-1]);

                if(shadowHitInfo.hitInfo){
                    if(tLight > shadowHitInfo.rayParameter){
                        dummyFlag = true;
                    }

                }

            }
        }

        if(!dummyFlag){
            parser::Vec3f cameraToRayHit = camera.position - rayHitInfo.rayPosition;
            parser::Vec3f Wo = cameraToRayHit * (1/lengthOfVector(cameraToRayHit));

            parser::Vec3f normal = rayHitInfo.rayNormal;

            float cosTheta = std::max(0.0f, calculateDotProduct(Wi, normal));
            parser::Vec3f h = (Wi + Wo) *(1/ lengthOfVector(Wi + Wo));
            float cosAlpha = std::max(0.0f,calculateDotProduct(normal,h));

            parser::Vec3f radiance = pointLight->intensity * (1/((powf(distanceOfVectors(pointLight->position,rayHitInfo.rayPosition),2))));



            parser::Vec3f Wr = (Wo * -1) + (normal * (calculateDotProduct(normal, Wo)) * 2);

            // Diffusing
            color.x += rayHitInfo.material.diffuse.x * cosTheta * radiance.x;
            color.y += rayHitInfo.material.diffuse.y * cosTheta * radiance.y;
            color.z += rayHitInfo.material.diffuse.z * cosTheta * radiance.z;

            //Specular
            float phongOp = powf(cosAlpha,rayHitInfo.material.phong_exponent);
            color.x += rayHitInfo.material.specular.x *phongOp * radiance.x;
            color.y += rayHitInfo.material.specular.y *phongOp * radiance.y;
            color.z += rayHitInfo.material.specular.z *phongOp * radiance.z;




            //Reflection
            Ray reflectionRay(rayHitInfo.rayPosition + Wr * scene.shadow_ray_epsilon, Wr);

            parser::Vec3f reflectionColor;
            reflectionColor =reflectionColor + coloring(reflectionRay,counterForDepth-1,rayHitInfo,scene,camera);
            color.x += reflectionColor.x * rayHitInfo.material.mirror.x;
            color.y += reflectionColor.y * rayHitInfo.material.mirror.y;
            color.z += reflectionColor.z * rayHitInfo.material.mirror.z;

        }



    }

    // Control case and adapt it for RGB->0-255
    if (color.x > 255.0) {
        color.x = 255.0;
    }

    if (color.y > 255.0) {
        color.y = 255.0;
    }

    if (color.z > 255.0) {
        color.z = 255.0;
    }


    return color;

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
                for(l=0; l<sphereSize;l++){
                    parser::Sphere *sphere = &scene.spheres[l];
                    sphereIntersection(*sphere,scene,ray,rayHitInfo,scene.materials[sphere->material_id-1]);
                }


                if (!rayHitInfo.hitInfo) {
                    image[3*(j*imageHeight+k)] = (unsigned char)scene.background_color.x;
                    image[3*(j*imageHeight+k)+1] = (unsigned char)scene.background_color.y;
                    image[3*(j*imageHeight+k)+2] = (unsigned char)scene.background_color.z;

                }else{

                    parser::Vec3f color;
                    color = coloring(ray,scene.max_recursion_depth,rayHitInfo,scene,camera);

                    image[3*(j*imageHeight+k)] = color.x;
                    image[3*(j*imageHeight+k)+1] = color.y;
                    image[3*(j*imageHeight+k)+2] = color.z;


                }
            }
            //if(j>399)
                //write_ppm("/home/sbk/CLionProjects/ceng477/cmake-build-debug/simple.ppm", image, imageWidth, imageHeight);


        }

        write_ppm(camera.image_name.c_str(), image, imageWidth, imageHeight);
//        write_ppm("hello.ppm", image, imageWidth, imageHeight);
        //write_ppm("/home/sbk/CLionProjects/ceng477/cmake-build-debug/bunny.ppm", image, imageWidth, imageHeight);


    }


    return  0;

}