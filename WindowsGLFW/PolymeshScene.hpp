//
//  PolymeshScene.hpp
//  Lab4-PolymeshScene
//
//  Created by David Reed on 12/24/15.
//  Copyright © 2015 David M Reed. All rights reserved.
//

#ifndef PolymeshScene_hpp
#define PolymeshScene_hpp

#include <stdio.h>
#include <vector>

#include "ShaderProgram.h"
#include "Polymesh.hpp"
#include "PolymeshInfo.hpp"
#include "GLFWBase.h"

class PolymeshScene : public GLFWBase {

public:
    PolymeshScene(GLFWwindow *window);
    ~PolymeshScene();

    /*! renders the scene
     */
    virtual void render();

    /* ! update instance variables based on keys pressed to update scene view
     */
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void setup(std::string filename);

    /*! reads the file containing the scene description;
     *  allocates _arrayOfPolymesh and stores each polymesh in it;
     *  sets the initial value for _angle based on _eye and _coi location
     *  stores the transformation and color information in _polymeshInfoVec
     * \param filename name of file containing scene description
     */
    void readFile(std::string filename);

    virtual void windowSizeCallback(GLFWwindow *window, int width, int height);

private:
    ShaderProgram _shaderProgram;

    // width and height of window; set in windowSizeCallback
    // need them to create perspective matrix
    int _windowWidth, _windowHeight;

    Polymesh *_arrayOfPolymesh;
    // recommended for storing polymesh filename and transformations
    std::vector<PolymeshInfo> _polymeshInfoVec;

    // eye and coi in world coordinates for lookat matrix
    vec4 _eye, _coi;

    // increment for eye and coi to use to update position
    // set in keyboardCallback
    vec4 _eyeInc; 

    // angle to calculate new _eye for rotating
    double _angle;

    // indicate whether we are currently rotating
    // set in keyboardCallback
    bool _rotateCCW, _rotateCW;

    // declare copy constructor and operator= private but do not implement
    PolymeshScene(const PolymeshScene &src);
    PolymeshScene& operator=(const PolymeshScene & src);
};

#endif /* PolymeshScene_hpp */
