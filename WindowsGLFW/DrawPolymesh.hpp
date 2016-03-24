//
//  DrawPolymesh.hpp
//  Lab3-Polymesh
//
//  Created by David Reed on 12/21/15.
//  Copyright © 2015 David M Reed. All rights reserved.
//

#ifndef DrawPolymesh_hpp
#define DrawPolymesh_hpp

#include <stdio.h>

#include "ShaderProgram.h"
#include "Polymesh.hpp"
#include "GLFWTrackball.hpp"

class DrawPolymesh : public GLFWTrackball {

public:
    DrawPolymesh(GLFWwindow *window);
    ~DrawPolymesh();
    
    // override the render method
    virtual void render();

    // override the keyboard callback
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // new method to initalize the data
    void setup(std::string filename);
    
private:

    ShaderProgram _shaderProgram;
    Polymesh _polymesh;
    float _polymeshColor[4];
};

#endif /* DrawPolymesh_hpp */
