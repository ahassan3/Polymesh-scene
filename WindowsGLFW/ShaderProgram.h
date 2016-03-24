//
//  ShaderProgram.h
//  
//
//  Created by David Reed on 2/15/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __MacGLFW__ShaderProgram__
#define __MacGLFW__ShaderProgram__

#include <string>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <GLFW/glfw3.h>


class ShaderProgram {

public:
    ShaderProgram() { _program = 0; }

    // read vertex and fragment shaders files to create the shader program
    void makeProgramFromShaderFiles(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

    // create shader program from strings containng the vertex and shader files
    void makeProgramFromShaderStrings(std::string vertexShader, std::string fragmentShader);

    // compile a shader; called by makeProgramFromShaderStrings
    void compileShader(std::string shaderCode, GLenum shaderType) const;

    // access the program identifier
    GLuint program() const { return _program; }

    // use this shader program
    void useProgram() const { glUseProgram(_program); }

protected:
    GLuint _program;
};

#endif /* defined(__MacGLFW__ShaderProgram__) */
