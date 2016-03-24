//
//  main.cpp
//  
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>

#ifndef __APPLE__
#include <GL/freeglut.h>
#endif

#include <GLFW/glfw3.h>

#include "PolymeshScene.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

//----------------------------------------------------------------------

static void errorCallback(int error, const char* description)
{
    cerr << description << endl;
    //fputs(description, stderr);
}

//----------------------------------------------------------------------

int main(int argc, const char * argv[]) {

    GLFWwindow* window;
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // try to get a fairly recent version of OpenGL
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //  create the GLFW window
    window = glfwCreateWindow(600, 600, "OpenGL Demo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set it to be the current OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    // global variable declared in GLEW files
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        cerr << "failed to initialize GLEW\n";
        exit(EXIT_FAILURE);
    }

    // specify refresh rate (normally 1)
    glfwSwapInterval(1);

    // output some information about OpenGL version
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    fprintf(stderr, "OpenGL version received: %d.%d.%d\n", major, minor, rev);
    fprintf(stderr, "%s", glfwGetVersionString());
    cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    cerr << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cerr << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cerr << "Renderer: " << glGetString(GL_RENDERER) << endl;
    GLint textureUnits;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &textureUnits);
    cerr << "Num texture units: " << textureUnits << endl;

    // create the class
    PolymeshScene *glBase = new PolymeshScene(window);

    // do any setup
    string filename;

    if (argc > 1) {
        filename = argv[1];
    }
    else {
        //filename = "in1.txt";
        cout << "enter filename: ";
        cin >> filename;
    }
    glBase->setup(filename);
    // and enter the run loop
    glBase->runLoop(false);
}
