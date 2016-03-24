//
//  GLFWTrackball.cpp
//  Lab3-Polymesh
//
//  Created by David Reed on 12/21/15.
//  Copyright © 2015 David M Reed. All rights reserved.
//

#include "GLFWTrackball.hpp"

GLFWTrackball::GLFWTrackball(GLFWwindow *window) : GLFWBase(window)
{
    _pressed = false;
    reset();
    _trackballSize = 1.0;
    glfwGetWindowSize(window, &_windowWidth, &_windowHeight);
    _invWindowHeight = 1.0 / _windowHeight;
}

//----------------------------------------------------------------------

void GLFWTrackball::reset()
{
    _curQuat = vec4(1, 0, 0, 0);
    _normalizeCount = 0;
}

//----------------------------------------------------------------------

void GLFWTrackball::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        _pressed = true;
        _xStart = xPos;
        _yStart = yPos;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        _pressed = false;
    }

    // save which button pressed
    _button = button;
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (_pressed)
                rotateStart(xPos, yPos);
            break;

            /*
        case GLFW_MOUSE_BUTTON_MIDDLE:
             _eyeCoiDistStart = _eyeCoiDist;
             break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            if (pressed_) {
                xViewStart_ = xView_;
                yViewStart_ = yView_;
                break;
            }
             */
    };
}

//----------------------------------------------------------------------

void GLFWTrackball::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (_pressed) {
        switch(_button) {
            case 0:
                rotateTrack(xPos, yPos);
                break;
                /*
                 case 1:
                 _eyeCoiDist = _eyeCoiDistStart -
                 0.1 * ((y - _yPressPos) + (_xPressPos - x));
                 if (_eyeCoiDist < 1.0)
                 _eyeCoiDist = 1.0;
                 _eye.set(coi_[0], coi_[1], coi_[2] + eyeCoiDist_);
                 break;

                 case 2:
                 xView_ = xViewStart_ + 0.05 * (x - xPressPos_);
                 yView_ = yViewStart_ + 0.05 * (yPressPos_ - y);
                 break;
                 */
        }
        //glutPostRedisplay();
    }
}

//----------------------------------------------------------------------

void GLFWTrackball::windowSizeCallback(GLFWwindow *window, int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
    _invWindowHeight = 1.0 / height;
    glViewport(0, 0, width, height);
}

//----------------------------------------------------------------------

void GLFWTrackball::rotateStart(int x, int y)
{
    _xStart = x;
    _yStart = y;
}

//----------------------------------------------------------------------

void GLFWTrackball::rotateTrack(int x, int y)
{
    computeQuat(_lastQuat, (2 * _xStart - _windowWidth) * _invWindowHeight,
                (_windowHeight - 2 * _yStart) * _invWindowHeight,
                (2 * x - _windowWidth) * _invWindowHeight,
                (_windowHeight - 2 * y) * _invWindowHeight);
    _xStart = x;
    _yStart = y;

    addQuat();
}

//----------------------------------------------------------------------

void GLFWTrackball::computeQuat(vec4 &q, double p1x, double p1y, double p2x, double p2y)
{
    vec3 a;           // Axis of rotation.
    double phi;            // How much to rotate about axis.
    vec3 p1, p2, d;
    double t;

    if ((p1x == p2x) && (p1y == p2y)) {
        // Zero rotation
        q = vec4(0, 0, 0, 1);
        return;
    }
    // First, figure out z-coordinates for projection of P1 and
    // P2 to deformed sphere.
    p1 = vec3(p1x, p1y, projectToSphere(_trackballSize, p1x, p1y));
    p2 = vec3(p2x, p2y, projectToSphere(_trackballSize, p2x, p2y));

    // Now, we want the cross product of P1 and P2.
    a = cross(p2, p1);

    // Figure out how much to rotate around that axis.
    d = p1 - p2;
    t = length(d) / (2.0 * _trackballSize);

    // Avoid problems with out-of-control values.
    if (t > 1.0)
        t = 1.0;
    if (t < -1.0)
        t = -1.0;
    phi = 2.0 * asin(t);

    axisToQuat(a, phi, q);
}


//----------------------------------------------------------------------

void GLFWTrackball::axisToQuat(vec3 &axis, double angle, vec4 &q)
{
    double m;

    axis = normalize(axis);
    m = sin(0.5 * angle);
    q = vec4(axis[0] * m, axis[1] * m, axis[2] * m, cos(0.5 * angle));
}

//----------------------------------------------------------------------

double GLFWTrackball::projectToSphere(double r, double x, double y)
{
    double d, t, z;

    d = sqrt(x * x + y * y);
    if (d < r * 0.70710678118654752440) {
        // Inside sphere.
        z = sqrt(r * r - d * d);
    }
    else {
        // On hyperbola.
        t = r / 1.41421356237309504880;
        z = t * t / d;
    }
    return z;
}

//----------------------------------------------------------------------

void GLFWTrackball::addQuat()
{
    vec3 t1, t2, t3, tf;
    vec3 q1, q2;

    q1 = vec3(_lastQuat[0], _lastQuat[1], _lastQuat[2]);
    q2 = vec3(_curQuat[0], _curQuat[1], _curQuat[2]);

    t1 = vec3(_lastQuat[0] * _curQuat[3],
              _lastQuat[1] * _curQuat[3],
              _lastQuat[2] * _curQuat[3]);
    t2 = vec3(_curQuat[0] * _lastQuat[3],
              _curQuat[1] * _lastQuat[3],
              _curQuat[2] * _lastQuat[3]);
    t3 = cross(q2, q1);
    tf = t1 + t2 + t3;

    _curQuat = vec4(tf[0], tf[1], tf[2],
                    _lastQuat[3] * _curQuat[3] - dot(q1, q2));
    _normalizeCount++;
    if (_normalizeCount > 100) {
        _normalizeCount = 0;
        // _curQuat = normalize(_curQuat);
    }
}

//----------------------------------------------------------------------
