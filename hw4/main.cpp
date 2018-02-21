#include "helper.h"
//#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>

static GLFWwindow *win = NULL;

// Shaders
GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture;
GLuint idMVPMatrix;

int widthTexture, heightTexture;

glm::vec3 *vertex_data;

glm::vec3 cameraUp = glm::vec3(0, 1, 0);
glm::vec3 cameraGaze = glm::vec3(0, 0, 1);
glm::vec3 cameraLeft = glm::cross(cameraUp, cameraGaze);
glm::vec3 cameraPosition;

GLfloat cameraSpeed = 0.0f;
//full screen
GLFWvidmode *mode;
const GLFWmonitor *monitor;

bool isFullScreen = false;
int displayWidth = 1000;
int displayHeight = 1000;
bool updateViewPort = false;

int nowDisplayWidth = 0;
int nowDisplayHeight = 0;

GLdouble angle = 45;
GLdouble aspectRatio = 1;
GLdouble nearDistance = 0.1;
GLdouble farDistance = 1000;

GLfloat heightFactor = 10.0f;


void createMesh() {
    int i, j, k;
    k = 0;
    glm::vec3 v1, v2, v3, v4;
    for (i = 0; i < widthTexture; i++) {
        for (j = 0; j < heightTexture; j++) {
            v1 = glm::vec3(i, 0, j);
            v2 = glm::vec3(i + 1, 0, j + 1);
            v3 = glm::vec3(i + 1, 0, j);
            v4 = glm::vec3(i, 0, j + 1);

            vertex_data[k] = v1;   // First triangle 1,2,3     v3 O----0 v2
            vertex_data[k + 1] = v2; //                             |   /|
            vertex_data[k + 2] = v3; //                             |  / |
            vertex_data[k + 3] = v1; // Second triangle 1,4,2       | /  |
            vertex_data[k + 4] = v4; //                             |/   |
            vertex_data[k + 5] = v2; //                          v1 0----0 v4

            k += 6;
        }
    }
}



void initialViewPortSetting(){
    glViewport(0,0, displayWidth, displayHeight);

}

void cameraSpec() {


    glm::mat4 projectionMatrix = glm::perspective(angle, aspectRatio, nearDistance, farDistance);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, glm::vec3(cameraPosition + cameraGaze * nearDistance), cameraUp);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    glm::mat4 normal_matrix = glm::inverseTranspose(viewMatrix);

    GLint mvpLocation = glGetUniformLocation(idProgramShader, "MVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

    GLint mvLocation = glGetUniformLocation(idProgramShader, "MV");
    glUniformMatrix4fv(mvLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    GLint normalMatrixLocation = glGetUniformLocation(idProgramShader, "normalMatrix");
    glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &normal_matrix[0][0]);

    GLint cameraPositionLocation = glGetUniformLocation(idProgramShader, "cameraPosition");
    glUniform3fv(cameraPositionLocation, 1, &cameraPosition[0]);


}

void renderFunction() {
    // Send data via vertex arrays
    int vertexCount = 6 * widthTexture * heightTexture;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableClientState(GL_VERTEX_ARRAY);

}

static void errorCallback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        cameraSpeed += 0.25;
    }

    if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        cameraSpeed -= 0.25;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (isFullScreen) {
            nowDisplayWidth = displayWidth;
            nowDisplayHeight = displayHeight;
            glfwSetWindowMonitor(window, nullptr, 0, 0, displayWidth, displayHeight, 0);
//            cout << "in f: getting old screen\n"<<nowDisplayWidth<<endl;


            isFullScreen = false;
        } else {

            glfwSetWindowMonitor(window, const_cast<GLFWmonitor*>(monitor),0,0,mode->width, mode->height,mode->refreshRate);
            nowDisplayWidth = mode->width;
            nowDisplayHeight = mode->height;
//            cout << "in f: getting full screen\n"<<nowDisplayWidth<<endl;

            isFullScreen = true;
        }
        updateViewPort = true;
    }

    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        cameraGaze = glm::rotate(cameraGaze, 0.01f, cameraLeft);
        cameraUp = glm::rotate(cameraUp, 0.01f, cameraLeft);
    }

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        cameraGaze = glm::rotate(cameraGaze, -0.01f, cameraLeft);
        cameraUp = glm::rotate(cameraUp, -0.01f, cameraLeft);
    }

    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        cameraGaze = glm::rotate(cameraGaze, 0.01f, cameraUp);
        cameraLeft = glm::rotate(cameraLeft, 0.01f, cameraUp);
    }

    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        cameraGaze = glm::rotate(cameraGaze, -0.01f, cameraUp);
        cameraLeft = glm::rotate(cameraLeft, -0.01f, cameraUp);
    }

    if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        heightFactor += 0.5;
        GLint heightFactorLocation = glGetUniformLocation(idProgramShader, "heightFactor");
        glUniform1f(heightFactorLocation, heightFactor);
    }

    if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        heightFactor -= 0.5;
        GLint heightFactorLocation = glGetUniformLocation(idProgramShader, "heightFactor");
        glUniform1f(heightFactorLocation, heightFactor);
    }

}




int main(int argc, char *argv[]) {



    if (argc != 2) {
        printf("Please provide only a texture image\n");
        exit(-1);
    }

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    win = glfwCreateWindow(1000, 1000, "CENG477 - HW4", NULL, NULL);

    if (!win) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(win);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

        glfwTerminate();
        exit(-1);
    }

    glfwSetKeyCallback(win, keyCallback);

    initShaders();
    glUseProgram(idProgramShader);
    initTexture(argv[1], &widthTexture, &heightTexture);
    int vertexCount = 6 * widthTexture * heightTexture;
    vertex_data = new glm::vec3[vertexCount]; // 2*w*d triangles and 3*2*w*d vertices

    cameraPosition = glm::vec3(widthTexture / 2, widthTexture / 10, (-1) * (widthTexture / 4));

    cameraSpec();

    initialViewPortSetting();

    createMesh();



    glEnable(GL_DEPTH_TEST);

    GLint samplerLocation = glGetUniformLocation(idProgramShader, "rgbTexture");
    glUniform1i(samplerLocation, 0);

    GLint widthTextureLocation = glGetUniformLocation(idProgramShader, "widthTexture");
    glUniform1i(widthTextureLocation, widthTexture);

    GLint heightTextureLocation = glGetUniformLocation(idProgramShader, "heightTexture");
    glUniform1i(heightTextureLocation, heightTexture);

    GLint heightFactorLocation = glGetUniformLocation(idProgramShader, "heightFactor");
    glUniform1f(heightFactorLocation, heightFactor);


    monitor = glfwGetPrimaryMonitor();
    mode = const_cast<GLFWvidmode *>(glfwGetVideoMode(const_cast<GLFWmonitor *>(monitor)));
    glfwGetWindowSize( win, &nowDisplayWidth, &nowDisplayHeight );


    while (!glfwWindowShouldClose(win)) {
        if ( updateViewPort )
        {


            glViewport( 0, 0, nowDisplayWidth, nowDisplayHeight);
//            cout<<"in while loop: vpsizeWidth\n"<<vpSizeWidth<<endl;
            updateViewPort = false;
        }



        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0f);
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        cameraPosition += cameraSpeed * cameraGaze;
        cameraSpec();
        renderFunction();
        glfwSwapBuffers(win);
        glfwPollEvents();

    }


    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
