//
//  Polymesh.h
//  Polymesh
//
//  Created by David M Reed on 12/21/15.
//  Copyright (c) 2015 David M Reed. All rights reserved.
//

#ifndef __Polymesh__Polymesh__
#define __Polymesh__Polymesh__

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <GLFW/glfw3.h>
#include "Angel.h"

class Polymesh {

public:
    Polymesh() { init(); }
    virtual ~Polymesh() { dealloc(); }

    /*! initializes instance variables to indicate zero points/triangles and NULL values for dynamicac arrays
     */
    virtual void init();


    /*! deallocates dynamic arrays and deallocates OpenGL buffers
     */
    virtual void dealloc();
    
    /*! read polymesh from specified filename and store as triangles in CCW order
     \param filename full path to file containing polymesh data
     \param frontFaceIsClockwise True if faces are defined in clockwise order when viewed from outside the object
     \post sets _numPoints, _numTriangles and allocates _points and _indices arrays and fills in the arrays appropriately
     */
    virtual void readFromObjectFile(std::string filename, bool frontFaceIsClockwise=true);
    
    GLsizei numTriangles() const { return _numTriangles; }
    GLsizei numPoints() const { return _numPoints; }

    /*! creates OpenGL buffers based on the points and indices
     \param shaderProgram ShaderProgram the current vertex shader
     \param shaderVertexPositionName int layout positon for the vertex position in the shader
     \post allocates OpenGL buffers and copies data for points and indices to the buffers
     */
    virtual void bindArrayAndElementBuffers(ShaderProgram &shaderProgram, int vertexPosition);

    /*! executes OpenGL commands to draw the Polymesh
     \pre OpenGL commands to clear color and depth buffer have been executed
     */
    virtual void glDraw();
        
protected:
    // number of points in the polymesh
    GLsizei _numPoints;

    // number of triangles in the polymesh
    GLsizei _numTriangles;

    // dynamically allocated array of points (3 * _numPoints for x, y, z coordinates)
    GLfloat *_points;

    // dynamically allocated array of indices (3 * _numTriangles since 3 point indices per triangle)
    GLuint *_indices;

    // values for the GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER for the point and index data
    GLuint _arrayAndElementBuffers[2];

    
private:
    // prevent copy constructor and operator= from being called
    Polymesh(const Polymesh &);
    Polymesh& operator=(const Polymesh &);
};

#endif /* defined(__Polymesh__Polymesh__) */
