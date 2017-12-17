#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <string>
#include <vector>
#include <math.h>

namespace parser {
    //Notice that all the structures are as simple as possible
    //so that you are not enforced to adopt any style or design.
    struct Vec3f {
        float x, y, z;
        int count;
        float normalX, normalY, normalZ;

        Vec3f operator-(const Vec3f &v2) {
            Vec3f result;
            result.x = x - v2.x;
            result.y = y - v2.y;
            result.z = z - v2.z;

            return result;
        }

        Vec3f operator+=(const Vec3f &v2) {
            Vec3f result;

            result.x = x + v2.x;
            result.y = y + v2.y;
            result.z = z + v2.z;

            return result;
        }

        Vec3f operator+(const Vec3f &v2) {
            Vec3f result;

            result.x = x + v2.x;
            result.y = y + v2.y;
            result.z = z + v2.z;

            return result;
        }



        Vec3f operator/(int val) {
            Vec3f result;
            result.x = x / val;
            result.y = y / val;
            result.z = z / val;

            return result;
        }



        Vec3f operator*(float val) {
            Vec3f result;
            result.x = x * val;
            result.y = y * val;
            result.z = z * val;

            return result;
        }
    };

    struct Vec3i {
        int x, y, z;
    };

    struct Vec4f {
        float x, y, z, w;
    };

    struct Camera {
        Vec3f position;
        Vec3f gaze;
        Vec3f up;
        Vec4f near_plane;
        float near_distance;
        float far_distance;
        int image_width, image_height;
    };

    struct PointLight {
        Vec3f position;
        Vec3f intensity;
        bool status;
    };

    struct Material {
        Vec3f ambient;
        Vec3f diffuse;
        Vec3f specular;
        float phong_exponent;
    };

    struct Transformation {
        std::string transformation_type;
        int id;
    };

    struct Face {
        int v0_id;
        int v1_id;
        int v2_id;
        Vec3f normal;
    };

    struct Mesh {
        int material_id;
        std::vector<Face> faces;
        std::vector<Transformation> transformations;
        std::string mesh_type;
    };

    struct Scene {
        //Data
        Vec3i background_color;
        Camera camera;
        Vec3f ambient_light;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<Vec3f> vertex_data;
        std::vector<Vec3f> translations;
        std::vector<Vec3f> scalings;
        std::vector<Vec4f> rotations;
        std::vector<Mesh> meshes;

        //Functions
        void loadFromXml(const std::string &filepath);
    };

    void doAverageNormal(Vec3f &vertexData);
    Vec3f calculateCrossProduct(const Vec3f &v1, const Vec3f &v2);
    Vec3f doUnitVector(const Vec3f &v);


}

#endif