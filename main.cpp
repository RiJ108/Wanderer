#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "objImporter/objImporter.hpp"
#include "shader/shader.hpp"

using namespace std;
void processInputs(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

double lastXPos = -1.0f;
float angle_ = -1.0f;
float FOV = 90.0f;


int main(void){
    cout << "MAIN::main()" << endl;
    ObjImporter objImporter;
    objImporter.extract("./resources/object/CubeTopBevel.obj");

    //**Window variables
    GLFWwindow* window;
    Shader shader3D;
    string title = "Wanderer", build = "build_0.1 dev";
    int SCR_WIDTH = 1280, SCR_HEIGHT = 720, fpsCap = 60;
    float deltaTime = 0.0f, lastFrame = 0.0f, currentFrame = 0.0f;

    //**Initiate glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, (title+"_"+build).c_str(), NULL, NULL);
    if (window == NULL){
        cout << "WINDOW::Failed to create GLFW window" << endl;
        glfwTerminate();
        return 0;
    }else   cout << "WINDOW::GLFW window created." << endl;
    glfwMakeContextCurrent(window);

    //**Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "WINDOW::Failed to initialize GLAD" << endl;
        return 0;
    }else   cout << "WINDOW::GLAD initialized." << endl;

    //**OpenGL state
    glEnable(GL_DEPTH_TEST);

    //**Setting the callBacks
    //glfwSetKeyCallback(window, key_callback);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //**Initiate 3D shader
    shader3D = Shader("./resources/shader/vShaderSource.vs", "resources/shader/fShaderSource.fs");
    vec3 position = vec3(-3.0f, 2.0f, -3.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 front = vec3(1.0f, -0.5f, -1.0f);
    shader3D.use();
    shader3D.setVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
    shader3D.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
    shader3D.setVec3("lightPos", vec3(-25.0f, 50.0f, -25.0f));
    //shader3D.setMat4("projection", perspective(radians(FOV), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 10000.0f));
    //shader3D.setMat4("model", mat4(1.0f));

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*objImporter.getDataSize(), &objImporter.getData()[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    //**Main loop
     while(!glfwWindowShouldClose(window)){
        //**Process timing
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        //**Process key press
        processInputs(window);

        //**Clearing buffers
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //**Setting shader's uniform
        shader3D.use();
        shader3D.setVec3("frontView", vec3(0.0f) - position);
        shader3D.setMat4("view", lookAt(position, vec3(0.0f) - position, up));
        shader3D.setVec3("viewPos", position);
        shader3D.setMat4("projection", perspective(radians(FOV), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 10000.0f));
        shader3D.setMat4("model", 
            glm::scale(glm::rotate(glm::mat4(1.0f), glm::radians(angle_), glm::vec3(0.0, 1.0, 0.0)), glm::vec3(0.5, 0.5, 0.5))
        );
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        //**Sleeping for capping refresh rate
        deltaTime = (double)1/fpsCap - deltaTime;
        if(deltaTime > 0)
            _sleep(deltaTime*1000);

        //**Polling and swapping of buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processInputs(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if(lastXPos >= 0){
            angle_ += (lastXPos - xpos);
            lastXPos = xpos;
        }else{
            lastXPos = xpos;
        }
    }else{
        lastXPos = -1.0f;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    FOV -= (float)yoffset*1.5f;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 120.0f)
        FOV = 120.0f; 
}