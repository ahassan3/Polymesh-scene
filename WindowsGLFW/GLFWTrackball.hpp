//
//  GLFWTrackball.hpp
//  Lab3-Polymesh
//
//  Created by David Reed on 12/21/15.
//  Copyright © 2015 David M Reed. All rights reserved.
//

#ifndef GLFWTrackball_hpp
#define GLFWTrackball_hpp

#include <stdio.h>

#include "ShaderProgram.h"
#include "GLFWBase.h"
#include "Polymesh.hpp"

class GLFWTrackball: public GLFWBase {
public:
    GLFWTrackball(GLFWwindow *window);



    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos);

    virtual void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

    virtual void windowSizeCallback(GLFWwindow *window, int width, int height);
    
    void reset();

    void rotateStart(int x, int y);
    void rotateTrack(int x, int y);

    void setTrackBallSize(double v) { _trackballSize = v; }
    double trackballSize() { return _trackballSize; }

    /*! returns the rotation quaternion so it can be sent to the shader
     * \returns vec4 rotation quaternion
     */
    vec4 rotationQuaternion() { return _curQuat; }


private:

    // private functions
    void computeQuat(vec4 &q, double p1x, double p1y, double p2x, double p2y);
    void axisToQuat(vec3 &axis, double angle, vec4 &q);
    double projectToSphere(double r, double x, double y);
    void addQuat();



    int _windowWidth, _windowHeight;

    int _button;
    bool _pressed;
    vec4 _lastQuat, _curQuat;
    int _xStart, _yStart;
    double _invWindowHeight;
    int _normalizeCount;
    double _trackballSize;

};

#endif /* GLFWTrackball_hpp */
