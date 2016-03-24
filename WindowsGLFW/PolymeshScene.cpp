//
//  PolymeshScene.cpp
//  Lab4-PolymeshScene
//
//  Created by Aimen Hassan on 1/10/16.
//  Instructor: David Reed
//

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using std::ifstream;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::string;
using std::cout;

#include "Utils.h"

#include "PolymeshScene.hpp"

//----------------------------------------------------------------------

PolymeshScene::PolymeshScene(GLFWwindow *window) : GLFWBase(window)
{
    glfwGetWindowSize(window, &_windowWidth, &_windowHeight);
    _arrayOfPolymesh = NULL;
}

//----------------------------------------------------------------------

PolymeshScene::~PolymeshScene()
{
    if (_arrayOfPolymesh) {
        delete [] _arrayOfPolymesh;
    }
}

//----------------------------------------------------------------------

void PolymeshScene::render()
{
	// clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// initiallize  a vector 4
	vec4 r;
	// set the x and z values of the vector based on the eye and coi
	r.x = _eye.x - _coi.x;
	r.z = _eye.z - _coi.z;


	// if the key is pressed to rotate counter-clockwise
	if (_rotateCCW == TRUE) {
		// update the angle
		_angle += .0128;
		// calculate the new eye x and z values based on the angle of cos
		_eye.x = length(r) * cos(_angle);
		_eye.z = length(r) * sin(_angle);
		// increment the eye by coi
		_eye.x += _coi.x;
		_eye.z += _coi.z;
	}


	// if the key is pressed to rotate clockwise
	if (_rotateCW == TRUE) {
		// update the angle
		_angle -= .0128;
		// calculate the new eye x and z values based on the angle of cos
		_eye.x = length(r) * cos(_angle);
		_eye.z = length(r) * sin(_angle);
		// increment the eye by coi
		_eye.x += _coi.x;
		_eye.z += _coi.z;
	}


	// update coi and eye by the eyeinc
	_eye += _eyeInc;
	_coi += _eyeInc;
	// create the perspective matrix by 
	mat4 perspective = Perspective(90, _windowWidth / _windowHeight, .101, 99.9);
	// create the lookat matrix 
	mat4 lookat = LookAt(_eye, _coi, vec4(0, 1, 0, 1));
	// create the projectioneyematrix by multiplying perspective by lookat
	mat4 projectionEyeMatrix = perspective * lookat;
	// get the location of the projectioneyematrix to send to the vshader
	GLuint proj = glGetUniformLocation(_shaderProgram.program(), "projectionEyeMatrix");
	// send the final formed matrix
	glUniformMatrix4fv(proj, 1, GL_TRUE, projectionEyeMatrix);

	// for loop to render every polymesh
	for (unsigned int i = 0; i < _polymeshInfoVec.size(); i++) {
		// creating the translate matrix based on the translate coordiantes in our file
		mat4 trans = Translate(_polymeshInfoVec[i].translate);
		// creating the rotatex matrix based on the x coordiante in our file
		mat4 rotx = RotateX(_polymeshInfoVec[i].rotate[0]);
		// creating the rotatey matrix based on the y coordiante in our file
		mat4 roty = RotateY(_polymeshInfoVec[i].rotate[1]);
		// creating the rotatez matrix based on the z coordiante in our file
		mat4 rotz = RotateZ(_polymeshInfoVec[i].rotate[2]);
		// creating the scale matrix based on the translate coordiantes in our file
		mat4 scal = Scale(_polymeshInfoVec[i].scale);
		// multiplies the matrices in the order described in the documentation: first scale then rotate then translate (which get flipped when dealing with matrices)
		mat4 objectmatrix = trans * (rotz * roty * rotx) * scal;

		// Get the location of the polycolor from the fshader
		GLuint color = glGetUniformLocation(_shaderProgram.program(), "polyColor");
		// send in the color of the polymesh from the file
		glUniform4fv(color, 1, _polymeshInfoVec[i].color);
		// get location of the objectmatrix from vshader
		GLuint obj = glGetUniformLocation(_shaderProgram.program(), "objectMatrix");
		// send that in from our final martrix that we found above
		glUniformMatrix4fv(obj, 1, GL_TRUE, objectmatrix);
		// draw the polymesh
		_arrayOfPolymesh[i].glDraw();

	}
}

//----------------------------------------------------------------------

void PolymeshScene::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// if the escape or Q key is pressed, exit the appication
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// if the K key is pressed, move forward
	 if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		 // calcualte the vector formed from the eye and coi
		vec4 frstvec = _eye - _coi;
		// normalize the vector
		frstvec = normalize(frstvec);
		// set the y value to 0, since we arent changing y
		frstvec[1] = 0;
		// multiply our eyeInc instance variable by -.1 to show the degree of moving backward
		_eyeInc = -.1 * frstvec;	
	}
	 // if the K key is released
	if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
		// set _eyeinc to 0
		_eyeInc = vec4 (0, 0, 0, 0);
	}
	// if the J key is released
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
		// set _eyeinc to 0
		_eyeInc = vec4 (0, 0, 0, 0);
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		// calcualte the vector formed from the eye and coi
		vec4 frstvec = _eye - _coi;
		// normalize the vector
		frstvec = normalize(frstvec);
		// set the y value to 0, since we arent changing y
		frstvec[1] = 0;
		// multiply our eyeInc instance variable by -.1 to show the degree of moving backward
		_eyeInc = .1 * frstvec;
	}
	// if the F key is pressed, rotate clockwise
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		// set clockwise rotate instance variable to true
		_rotateCW = TRUE;
	}
	// if the D key is pressed, rotate counter clockwise
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		// set counter clockwise instance variable to true
		_rotateCCW = TRUE;
	}
	// if the F key is released
	if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
		// set value to false
		_rotateCW = FALSE;
	}
	// if the D key is released
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		// set the variable to false
		_rotateCCW = FALSE;
	}
}

//----------------------------------------------------------------------

void PolymeshScene::setup(std::string filename)
{
	glClearColor(0.39, 0.56, 0.85, 1);
	glEnable(GL_DEPTH_TEST);

	// read and compile shaders
	string vshaderPath = "vshader.txt";
	string fshaderPath = "fshader.txt";
	vshaderPath = pathUsingEnvironmentVariable(vshaderPath, "GL_SHADER_DIR");
	fshaderPath = pathUsingEnvironmentVariable(fshaderPath, "GL_SHADER_DIR");
	_shaderProgram.makeProgramFromShaderFiles(vshaderPath, fshaderPath);
	_shaderProgram.useProgram();

	_eyeInc = vec4(0, 0, 0, 0);
	_rotateCW = _rotateCCW = false;

	readFile(filename);
}

//----------------------------------------------------------------------

void PolymeshScene::readFile(std::string filename)
{
	// create an ifstream to read in the file
	ifstream ifs;
	// open the file object
	ifs.open(filename.c_str());
	// assignt the first two lines of values to the eye and coi
	ifs >> _eye[0] >> _eye[1] >> _eye[2] >> _eye[3];
	ifs >> _coi[0] >> _coi[1] >> _coi[2] >> _coi[3];
	// create a polymeshinfo object to hold each polymesh's file info
	PolymeshInfo pmi;
	// while we have polymeshes, keep appending it into our _polymeshInfovec
	while (ifs >> pmi) {
		_polymeshInfoVec.push_back(pmi);
	}
	// allocate memory to the _arrayofpolymesh for how many polmeshes we have
	_arrayOfPolymesh = new Polymesh[_polymeshInfoVec.size()];
	// loop that runs for every polymesh we have
	
	
	for (unsigned int i = 0; i < _polymeshInfoVec.size(); i++) {
		// assaign the polymeshs to the array of polymesh
		_arrayOfPolymesh[i].readFromObjectFile(_polymeshInfoVec[i].filename);
		_arrayOfPolymesh[i].bindArrayAndElementBuffers(_shaderProgram, 0);
		/*cout << _polymeshInfoVec[i].filename << std::endl;
		cout << _polymeshInfoVec[i].color << std::endl;
		cout << _polymeshInfoVec[i].translate << std::endl;
		cout << _polymeshInfoVec[i].rotate << std::endl;
		cout << _polymeshInfoVec[i].scale << std::endl;*/
	}
	// close the file
	
	
	ifs.close();
	//intialize a vec2 to calculate the angle
	vec2 frstvec;
	// the vec2 holds the differences of the and y coordinates of the eye and coi
	frstvec[0] = _eye.x - _coi.x;
	frstvec[1] = _eye.z - _eye.z;
	// create a vec2 that is 1,0 to calculate the angle
	vec2 scnd = (1, 0);
	// calculate the angle by doing the inverse cosine of the dot product of the two vec2s and over the length of our first vec2 (the length of other vec2 equals 1)
	_angle = acos(dot(frstvec, scnd) / length(frstvec));



}
	

//----------------------------------------------------------------------

void PolymeshScene::windowSizeCallback(GLFWwindow *window, int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
    glViewport(0, 0, width, height);
}

//----------------------------------------------------------------------
