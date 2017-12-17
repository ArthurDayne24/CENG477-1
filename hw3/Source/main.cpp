#include <iostream>
#include "parser.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265358979323846
//////-------- Global Variables -------/////////

GLuint gpuVertexBuffer;
GLuint gpuNormalBuffer;
GLuint gpuIndexBuffer;

// Sample usage for reading an XML scene file
parser::Scene scene;
bool allLightOnFlag = false;
bool *lightStatus;

static GLFWwindow *win = NULL;

void cameraStarting();

void startLight();

static void errorCallback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void constructLightStatus() {
    lightStatus = new bool[scene.point_lights.size()]();
}

void oneLightOnOff(int pressButton) {

    if (lightStatus[pressButton - 1]) {
        glDisable(GL_LIGHT0 + pressButton -1);
        lightStatus[pressButton - 1] = false;
    } else {
        glEnable(GL_LIGHT0 + pressButton -1);
        lightStatus[pressButton - 1] = true;
    }
}

void turnOffLights() {
    if (!allLightOnFlag) {
        startLight();
    } else {
        //glDisable(GL_LIGHTING);

        for (int i = 0; i < scene.point_lights.size(); i++) {
            glDisable(GL_LIGHT0 + i);
            lightStatus[i] = false;
        }

        allLightOnFlag = false;
    }

}

float *matrixMultiplicationFourByFour(const float *firstMatrix, const float *secondMatrix) {
    float *k = new float[16]();

    for (int x = 0; x < 4; x++) { // row number of output
        for (int y = 0; y < 4; y++) { // column number of output
            k[4 * x + y] = 0;
            for (int z = 0; z < 4; z++) { // four elements are added for this output
                k[4 * x + y] += firstMatrix[4 * x + z] * secondMatrix[4 * z + y];
            }
        }
    }
/*
    std::cout << "multi\n";

    for (int i = 0; i <16 ; ++i) {

        std::cout << k[i] << "**";
    }
    std::cout << "end\n";*/

    return k;
}


parser::Vec3f doV_vector(const parser::Vec3f &u) {
    parser::Vec3f v;
    float smallestValue = u.x;
    int smallestValueLocation = 0;

    if (smallestValue > u.y) {
        smallestValue = u.y;
        smallestValueLocation = 1;
    }

    if (smallestValue > u.z) {
        smallestValue = u.z;
        smallestValueLocation = 2;

    }

    if (smallestValueLocation == 0) {
        v.x = 0;
        v.y = u.z;
        v.z = -1 * u.y;
    } else if (smallestValueLocation == 1) {
        v.y = 0;
        v.x = u.z;
        v.z = -1 * u.x;
    } else if (smallestValueLocation == 2) {
        v.z = 0;
        v.x = u.y;
        v.y = -1 * u.x;
    }

    return v;

}

float *matrixMultiplicationFourByOne(float *firstMatrix, float *secondMatrix) {
    float *result = new float[4]();

    result[0] = firstMatrix[0] * secondMatrix[0] + firstMatrix[1] * secondMatrix[1] + firstMatrix[2] * secondMatrix[2] +
                firstMatrix[3] * secondMatrix[3];
    result[1] = firstMatrix[4] * secondMatrix[0] + firstMatrix[5] * secondMatrix[1] + firstMatrix[6] * secondMatrix[2] +
                firstMatrix[7] * secondMatrix[3];
    result[2] =
            firstMatrix[8] * secondMatrix[0] + firstMatrix[9] * secondMatrix[1] + firstMatrix[10] * secondMatrix[2] +
            firstMatrix[11] * secondMatrix[3];
    result[3] =
            firstMatrix[12] * secondMatrix[0] + firstMatrix[13] * secondMatrix[1] + firstMatrix[14] * secondMatrix[2] +
            firstMatrix[15] * secondMatrix[3];

    return result;
}

void doRotation(bool isA, bool isU, bool UJOperation) {

    std::cout << isA << "-"
              << isU << "-"
              << UJOperation << "\n";
    parser::Vec3f u = scene.camera.up;
    std::cout << "u vector old:" << u.x << '*'
              << u.y << '*'
              << u.z << '\n';
    if (UJOperation && !isU) {
        std::cout << "pressing j" << std::endl;
        u = parser::calculateCrossProduct(scene.camera.gaze, scene.camera.up);
    } else if (UJOperation && isU) {
        std::cout << "pressing u" << std::endl;
        u = parser::calculateCrossProduct(scene.camera.up, scene.camera.gaze);
    }
    std::cout << "u vector new:" << u.x << '*'
              << u.y << '*'
              << u.z << '\n';
    parser::Vec3f v = doV_vector(u);
    parser::Vec3f w = parser::calculateCrossProduct(u, v);

/*    std::cout <<"u vector:" << u.x << '*'
              << u.y << '*'
              << u.z << '\n';
    std::cout <<"v vector:" << v.x << '*'
              << v.y << '*'
              << v.z << '\n';
    std::cout <<"w vector:" << w.x << '*'
              << w.y << '*'
              << w.z << '\n';*/
    float inverseOfM[16] = {
            u.x, v.x, w.x, 0,
            u.y, v.y, w.y, 0,
            u.z, v.z, w.z, 0,
            0, 0, 0, 1
    };

//    float inverseOfM[16] = {
//            1, 0, 0, 0,
//            0, 1, 0, 0,
//            0, 0, 1, 0,
//            0, 0, 0, 1
//    };

//    float m[16] = {
//            7, 0, 0, 0,
//            3, 0, 0, 0,
//            2, 0, 0, 0,
//            1, 0, 0, 0
//    };
//    float *deneme = matrixMultiplicationFourByFour(inverseOfM,m);

    float m[16] = {
            u.x, u.y, u.z, 0,
            v.x, v.y, v.z, 0,
            w.x, w.y, w.z, 0,
            0, 0, 0, 1
    };


    float r[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    if (isA && !UJOperation) {
        r[5] = cosf(1 * 0.5 * PI / 180.0);
        r[6] = -1 * sinf(1 * 0.5 * PI / 180.0);
        r[9] = sinf(1 * 0.5 * PI / 180.0);
        r[10] = cosf(1 * 0.5 * PI / 180.0);
    } else if (!isA && !UJOperation) {
        r[5] = cosf(-1 * 0.5 * PI / 180.0);
        r[6] = -1 * sinf(-1 * 0.5 * PI / 180.0);
        r[9] = sinf(-1 * 0.5 * PI / 180.0);
        r[10] = cosf(-1 * 0.5 * PI / 180.0);
    } else if (UJOperation && !isU) {
        r[5] = cosf(-1 * 0.5 * PI / 180.0);
        r[6] = -1 * sinf(-1 * 0.5 * PI / 180.0);
        r[9] = sinf(-1 * 0.5 * PI / 180.0);
        r[10] = cosf(-1 * 0.5 * PI / 180.0);
    } else if (UJOperation && isU) {
        r[5] = cosf(-1 * 0.5 * PI / 180.0);
        r[6] = -1 * sinf(-1 * 0.5 * PI / 180.0);
        r[9] = sinf(-1 * 0.5 * PI / 180.0);
        r[10] = cosf(-1 * 0.5 * PI / 180.0);
    }


    float *multi = matrixMultiplicationFourByFour(inverseOfM, r);
    multi = matrixMultiplicationFourByFour(multi, m);

    float cameraEye[] = {scene.camera.gaze.x, scene.camera.gaze.y, scene.camera.gaze.z, 1};
    float *rotX = matrixMultiplicationFourByOne(multi, cameraEye);

    /*   std::cout << scene.camera.gaze.x << '*'
                 << scene.camera.gaze.y << '*'
                 << scene.camera.gaze.z << '\n';*/
    scene.camera.gaze.x = rotX[0] / rotX[3];
    scene.camera.gaze.y = rotX[1] / rotX[3];
    scene.camera.gaze.z = rotX[2] / rotX[3];

    scene.camera.gaze = parser::doUnitVector(scene.camera.gaze);
/*    std::cout << scene.camera.gaze.x << '*'
              << scene.camera.gaze.y << '*'
              << scene.camera.gaze.z << '\n';*/

}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        scene.camera.position = scene.camera.position + (scene.camera.gaze * (float) 0.05);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        scene.camera.position = scene.camera.position - (scene.camera.gaze * (float) 0.05);
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        doRotation(true, false, false);
        cameraStarting();
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        doRotation(false, false, false);
        cameraStarting();
    } else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        doRotation(false, false, true);
        cameraStarting();
    } else if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        doRotation(false, true, true);
        cameraStarting();
    } else if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        turnOffLights();
    } else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        oneLightOnOff(1);
    } else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        oneLightOnOff(2);
    } else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        oneLightOnOff(3);
    } else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        oneLightOnOff(4);
    } else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
        oneLightOnOff(5);
    }else if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
        oneLightOnOff(6);
    }else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        oneLightOnOff(7);
    }else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        oneLightOnOff(8);
    }else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        oneLightOnOff(9);
    }
}


parser::Vec3f getVertexValue(int vertexId, const parser::Scene &scene) {
    return scene.vertex_data[vertexId - 1];
}

void cameraStarting() {
    parser::Camera camera = scene.camera;
    //loadIdentity
    //viewport
    glViewport(0, 0, camera.image_width, camera.image_height);
    //lookat
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
              (camera.gaze.x * camera.near_distance + camera.position.x),
              (camera.gaze.y * camera.near_distance + camera.position.y),
              (camera.gaze.z * camera.near_distance + camera.position.z), camera.up.x, camera.up.y, camera.up.z);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //frustom
    glFrustum(camera.near_plane.x, camera.near_plane.y, camera.near_plane.z, camera.near_plane.w, camera.near_distance,
              camera.far_distance);
}

void startLight() {
    glEnable(GL_LIGHTING);
    for (int i = 0; i < scene.point_lights.size(); i++) {
        glEnable(GL_LIGHT0 + i);
        lightStatus[i] = true;
    }
    allLightOnFlag = true;
}


void turnOnLights() {
    //glEnable(GL_LIGHTING);
    for (int i = 0; i < scene.point_lights.size(); i++) {
        parser::PointLight pointLight = scene.point_lights[i];
        //glEnable(GL_LIGHT0 + i);
        GLfloat col[] = {pointLight.intensity.x, pointLight.intensity.y, pointLight.intensity.z, 1.0f};
        GLfloat pos[] = {pointLight.position.x, pointLight.position.y, pointLight.position.z, 1.0f};
        GLfloat ambient[] = {scene.ambient_light.x, scene.ambient_light.y, scene.ambient_light.z, 1.0f};


        glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, col);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, col);
    }
}

void renderFunction(parser::Scene &scene) {
    //doRotation();
//    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    int i, j;
    for (i = 0; i < scene.meshes.size(); i++) {
        parser::Mesh mesh = scene.meshes[i];
        //material
        parser::Material material = scene.materials[mesh.material_id - 1];

        GLfloat ambColor[] = {material.ambient.x, material.ambient.y, material.ambient.z, 1.0f};
        GLfloat diffColor[] = {material.diffuse.x, material.diffuse.y, material.diffuse.z, 1.0f};
        GLfloat specColor[] = {material.specular.x, material.specular.y, material.specular.z, 1.0f};
        GLfloat specExp[] = {material.phong_exponent};


        glPushMatrix();
        for (j = mesh.transformations.size() - 1; j >= 0; j--) {
            parser::Transformation transformation = mesh.transformations[j];
            if (transformation.transformation_type == "Translation") {
                parser::Vec3f translation = scene.translations[transformation.id - 1];
                glTranslatef(translation.x, translation.y, translation.z);
            } else if (transformation.transformation_type == "Rotation") {
                parser::Vec4f rotation = scene.rotations[transformation.id - 1];
                glRotatef(rotation.x, rotation.y, rotation.z, rotation.w);
            } else if (transformation.transformation_type == "Scaling") {
                parser::Vec3f scalling = scene.scalings[transformation.id - 1];
                glScalef(scalling.x, scalling.y, scalling.z);
            }

        }

        //face

        for (j = 0; j < mesh.faces.size(); j++) {

            if (mesh.mesh_type == "Solid")
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            else if (mesh.mesh_type == "Wireframe")
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//material
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambColor);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffColor);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specColor);
            glMaterialfv(GL_FRONT, GL_SHININESS, specExp);


            glBegin(GL_TRIANGLES);

            //glColor3f(1.0, 0.0, 0.0); // color state is red
            parser::Vec3f normal;
            //std::cout<< "FACE SIZE -> " << mesh.faces.size() << std::endl;
            parser::Face face = mesh.faces[j];
            parser::Vec3f vertex;
            //normal = calculateCrossProduct(getVertexValue(face.v1_id, scene) - getVertexValue(face.v0_id, scene),getVertexValue(face.v2_id, scene)-getVertexValue(face.v0_id, scene));

            //std::cout << face.v0_id << std::endl;
            vertex = getVertexValue(face.v0_id, scene);
            //glNormal3f(normal.x,normal.y,normal.z);
            glNormal3f(scene.vertex_data[face.v0_id - 1].normalX, scene.vertex_data[face.v0_id - 1].normalY,
                       scene.vertex_data[face.v0_id - 1].normalZ);
            glVertex3f(vertex.x, vertex.y, vertex.z); // first vertex
            //std::cout << vertex.x << "--" <<  vertex.y << "--" <<vertex.z << std::endl;

            //glColor3f(0.0, 1.0, 0.0);
            //std::cout << face.v1_id << std::endl;
            vertex = getVertexValue(face.v1_id, scene);
            glNormal3f(scene.vertex_data[face.v1_id - 1].normalX, scene.vertex_data[face.v1_id - 1].normalY,
                       scene.vertex_data[face.v1_id - 1].normalZ);

            glVertex3f(vertex.x, vertex.y, vertex.z); // second vertex
            //std::cout << vertex.x << "--" <<  vertex.y << "--" <<vertex.z << std::endl;
            //glColor3f(0.0, 0.0, 1.0);
            //std::cout << face.v2_id << std::endl;
            vertex = getVertexValue(face.v2_id, scene);
            glNormal3f(scene.vertex_data[face.v2_id - 1].normalX, scene.vertex_data[face.v2_id - 1].normalY,
                       scene.vertex_data[face.v2_id - 1].normalZ);
            glVertex3f(vertex.x, vertex.y, vertex.z); // third vertex
            //std::cout << vertex.x << "--" <<  vertex.y << "--" <<vertex.z << std::endl;

            glEnd();

        }
//        if(i==0)
//            break;
        glPopMatrix();
    }
}


int main(int argc, char *argv[]) {
    constructLightStatus();

    scene.loadFromXml(argv[1]);
    scene.camera.gaze = parser::doUnitVector(scene.camera.gaze);

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    win = glfwCreateWindow(scene.camera.image_width, scene.camera.image_height, "CENG477", NULL, NULL);
    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(win);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(win, keyCallback);
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    startLight();

    while (!glfwWindowShouldClose(win)) {
        glfwWaitEvents();


        cameraStarting();
        turnOnLights();

//        drawCubeBasic();
        renderFunction(scene);

        glfwSwapBuffers(win);


    }

    glfwDestroyWindow(win);
    glfwTerminate();

    exit(EXIT_SUCCESS);

    return 0;
}
