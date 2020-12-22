#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "objImporter/objImporter.hpp"

using namespace std;

int main(void){
    cout << "MAIN::main()" << endl;
    ObjImporter objImporter;
    objImporter.extract("./resources/object\\Cube.obj");

    //***Window variables
    GLFWwindow* window;
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

    //***Main loop
     while(glfwWindowShouldClose(window)){
        //***Process timing
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        //**Sleeping for capping refresh rate
        deltaTime = (double)1/fpsCap - deltaTime;
        if(deltaTime > 0)
            //Sleep(deltaTime*1000);

        //***Polling and swapping of buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}