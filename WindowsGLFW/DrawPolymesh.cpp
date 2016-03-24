//
//  DrawPolymesh.cpp
//  Lab3-Polymesh
//
//  Created by David Reed on 12/21/15.
//  Copyright © 2015 David M Reed. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Utils.h"

using std::string;
using std::ifstream;
using std::getline;

#include "DrawPolymesh.hpp"

//----------------------------------------------------------------------

// must initlaize GLFWBase with window parameter
DrawPolymesh::DrawPolymesh(GLFWwindow* window) : GLFWTrackball(window)
{

}

//----------------------------------------------------------------------

void DrawPolymesh::render()
{
    // clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint color = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    glUniform4fv(color, 1, _polymeshColor);

    GLuint rquat = glGetUniformLocation(_shaderProgram.program(), "rquat");
    //std::cerr << rotationQuaternion() << std::endl;
    glUniform4fv(rquat, 1, rotationQuaternion());

    // draw the polymesh
    _polymesh.glDraw();

}

//----------------------------------------------------------------------

void DrawPolymesh::setup(std::string filename)
{
    ifstream ifs;

    string polymeshFilename;

    // black background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // read and compile shaders
    string vshaderPath = "vshader.txt";
    string fshaderPath = "fshader.txt";
    vshaderPath = pathUsingEnvironmentVariable(vshaderPath, "GL_SHADER_DIR");
    fshaderPath = pathUsingEnvironmentVariable(fshaderPath, "GL_SHADER_DIR");
    _shaderProgram.makeProgramFromShaderFiles(vshaderPath, fshaderPath);
    _shaderProgram.useProgram();

    ifs.open(filename.c_str());
    getline(ifs, polymeshFilename);
    ifs >> _polymeshColor[0] >> _polymeshColor[1] >> _polymeshColor[2];
    _polymeshColor[3] = 1.0;

    _polymesh.readFromObjectFile(polymeshFilename);


    // bind the buffers
    _polymesh.bindArrayAndElementBuffers(_shaderProgram, 0);
}

//----------------------------------------------------------------------

void DrawPolymesh::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

//----------------------------------------------------------------------
