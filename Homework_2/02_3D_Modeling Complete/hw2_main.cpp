//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

/*!
ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
*/
unsigned int createTriangleStripModel(void)
{
	// use the vertex array object vaoID[0] for this model representation
	float* vertices = new float[135];  // Vertices for our square
	float *colors = new float[135]; // Colors for our vertices

	vertices[0] = 0.0 - 3.0; vertices[1] = 0.0; vertices[2] = -3.0; // 0
	colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // 0

	vertices[3] = 0.0 - 3.0; vertices[4] = -1.0; vertices[5] = -3.0; // 1
	colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // 1

	vertices[6] = 0.0 - 3.0; vertices[7] = 0.0; vertices[8] = -2.0; // 2
	colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // 2

	vertices[9] = 0.0 - 3.0; vertices[10] = -1.0; vertices[11] = -2.0; // 3
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // 3

	vertices[12] = 2.0 - 3.0; vertices[13] = 0.0; vertices[14] = -2.0; // 4
	colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0; // 4

	vertices[15] = 2.0 - 3.0; vertices[16] = -1.0; vertices[17] = -2.0; // 5
	colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // 5

	vertices[18] = 2.0 - 3.0; vertices[19] = 0.0; vertices[20] = -3.0; // 6
	colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0; // 6

	vertices[21] = 2.0 - 3.0; vertices[22] = -1.0; vertices[23] = -3.0; // 7
	colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0; // 7

	vertices[24] = 0.0 - 3.0; vertices[25] = 0.0; vertices[26] = -3.0; // 8
	colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0; // 8

	vertices[27] = 0.0 - 3.0; vertices[28] = -1.0; vertices[29] = -3.0; // 9
	colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0; // 9

	vertices[30] = 2.0 - 3.0; vertices[31] = -1.0; vertices[32] = -2.0; // 10
	colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0; // 10

	vertices[33] = 0.0 - 3.0; vertices[34] = -1.0; vertices[35] = -2.0; // 11
	colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0; // 11

	vertices[36] = 2.0 - 3.0; vertices[37] = -1.0; vertices[38] = -3.0; // 12
	colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0; // 12

	vertices[39] = 0.0 - 3.0; vertices[40] = -1.0; vertices[41] = -3.0; // 13
	colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0; // 13

	vertices[42] = 0.0 - 3.0; vertices[43] = 0.0; vertices[44] = -3.0; // 14
	colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0; // 14

	vertices[45] = 2.0 - 3.0; vertices[46] = 0.0; vertices[47] = -2.0; // 15
	colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0; // 15

	vertices[48] = 2.0 - 3.0; vertices[49] = 0.0; vertices[50] = -3.0; // 16
	colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0; // 16

	vertices[51] = 0.0 - 3.0; vertices[52] = 0.0; vertices[53] = -3.0; // 17
	colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0; // 17

	vertices[54] = 0.0 - 3.0; vertices[55] = 0.0; vertices[56] = -2.0; // 18
	colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0; // 18

	vertices[57] = 2.0 - 3.0; vertices[58] = 0.0; vertices[59] = -2.0; // 19
	colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0; // 19

	vertices[60] = 2.0 - 3.0; vertices[61] = 0.0; vertices[62] = -3.0; // 20
	colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0; // 20

	vertices[63] = 2.0 - 3.0; vertices[64] = 1.0; vertices[65] = -2.0; // 21
	colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0; // 21

	vertices[66] = 2.0 - 3.0; vertices[67] = 1.0; vertices[68] = -3.0; // 22
	colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0; // 22

	vertices[69] = 3.0 - 3.0; vertices[70] = 1.0; vertices[71] = -2.0; // 23
	colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0; // 23    

	vertices[72] = 3.0 - 3.0; vertices[73] = 1.0; vertices[74] = -3.0; // 24
	colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0; // 24

	vertices[75] = 2.0 - 3.0; vertices[76] = 1.0; vertices[77] = -3.0; // 25
	colors[75] = 0.0; colors[76] = 0.0; colors[77] = 1.0; // 25

	vertices[78] = 3.0 - 3.0; vertices[79] = -1.0; vertices[80] = -3.0; // 26
	colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0; // 26

	vertices[81] = 2.0 - 3.0; vertices[82] = -1.0; vertices[83] = -3.0; // 27
	colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0; // 27

	vertices[84] = 3.0 - 3.0; vertices[85] = -1.0; vertices[86] = -0.0; // 28
	colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0; // 28

	vertices[87] = 2.0 - 3.0; vertices[88] = -1.0; vertices[89] = -0.0; // 29
	colors[87] = 0.0; colors[88] = 0.0; colors[89] = 1.0; // 29

	vertices[90] = 3.0 - 3.0; vertices[91] = 0.0; vertices[92] = -0.0; // 30
	colors[90] = 0.0; colors[91] = 0.0; colors[92] = 1.0; // 30

	vertices[93] = 2.0 - 3.0; vertices[94] = 0.0; vertices[95] = -0.0; // 31
	colors[93] = 0.0; colors[94] = 0.0; colors[95] = 1.0; // 31

	vertices[96] = 3.0 - 3.0; vertices[97] = 1.0; vertices[98] = -2.0; // 32
	colors[96] = 0.0; colors[97] = 0.0; colors[98] = 1.0; // 32

	vertices[99] = 2.0 - 3.0; vertices[100] = 1.0; vertices[101] = -2.0; // 33
	colors[99] = 0.0; colors[100] = 0.0; colors[101] = 1.0; // 33

	vertices[102] = 2.0 - 3.0; vertices[103] = -1.0; vertices[104] = -2.0; // 34
	colors[102] = 0.0; colors[103] = 0.0; colors[104] = 1.0; // 34

	vertices[105] = 2.0 - 3.0; vertices[106] = 0.0; vertices[107] = -0.0; // 35
	colors[105] = 0.0; colors[106] = 0.0; colors[107] = 1.0; // 35

	vertices[108] = 2.0 - 3.0; vertices[109] = -1.0; vertices[110] = -0.0; // 36
	colors[108] = 0.0; colors[109] = 0.0; colors[110] = 1.0; // 36

	vertices[111] = 3.0 - 3.0; vertices[112] = 1.0; vertices[113] = -2.0; // 37
	colors[111] = 0.0; colors[112] = 0.0; colors[113] = 1.0; // 37

	vertices[114] = 3.0 - 3.0; vertices[115] = -1.0; vertices[116] = -2.0; // 38
	colors[114] = 0.0; colors[115] = 0.0; colors[116] = 1.0; // 38

	vertices[117] = 3.0 - 3.0; vertices[118] = 0.0; vertices[119] = -0.0; // 39
	colors[117] = 0.0; colors[118] = 0.0; colors[119] = 1.0; // 39

	vertices[120] = 3.0 - 3.0; vertices[121] = -1.0; vertices[122] = -0.0; // 40
	colors[120] = 0.0; colors[121] = 0.0; colors[122] = 1.0; // 40

	vertices[123] = 3.0 - 3.0; vertices[124] = -1.0; vertices[125] = -3.0; // 41
	colors[123] = 0.0; colors[124] = 0.0; colors[125] = 1.0; // 41

	vertices[126] = 3.0 - 3.0; vertices[127] = 1.0; vertices[128] = -3.0; // 42
	colors[126] = 0.0; colors[127] = 0.0; colors[128] = 1.0; // 42

	vertices[129] = 3.0 - 3.0; vertices[130] = -1.0; vertices[131] = -2.0; // 43
	colors[129] = 0.0; colors[130] = 0.0; colors[131] = 1.0; // 43

	vertices[132] = 3.0 - 3.0; vertices[133] = 1.0; vertices[134] = -2.0; // 44
	colors[132] = 0.0; colors[133] = 0.0; colors[134] = 1.0; // 44

	glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it


	glGenBuffers(2, vboID); // Generate our Vertex Buffer Object

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 135 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


	//Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 135 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory




	//TODO:
	vaoID[0];

	return 1;
}

/*!
ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
*/
unsigned int createPolygonModel(void)
{
	// use the vertex array object vaoID[1] for this model representation
	float* vertices = new float[423];  // Vertices for our square
	float *colors = new float[423]; // Colors for our vertices

	vertices[0] = 0.0; vertices[1] = 0.0; vertices[2] = -3.0; // 0
	colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // 0

	vertices[3] = 0.0; vertices[4] = -1.0; vertices[5] = -3.0; // 1
	colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // 1

	vertices[6] = 0.0; vertices[7] = 0.0; vertices[8] = -2.0; // 2
	colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // 2

	vertices[9] = 0.0; vertices[10] = -1.0; vertices[11] = -3.0; // 1
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // 1

	vertices[12] = 0.0; vertices[13] = 0.0; vertices[14] = -2.0; // 2
	colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0; // 2

	vertices[15] = 0.0; vertices[16] = -1.0; vertices[17] = -2.0; // 3
	colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // 3

	vertices[18] = 0.0; vertices[19] = 0.0; vertices[20] = -2.0; // 2
	colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0; // 2

	vertices[21] = 0.0; vertices[22] = -1.0; vertices[23] = -2.0; // 3
	colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0; // 3

	vertices[24] = 2.0; vertices[25] = 0.0; vertices[26] = -2.0; // 4
	colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0; // 4

	//vertices[27] = 0.0; vertices[28] = -1.0; vertices[29] = -2.0; // 3
	//colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0; // 3

	//vertices[30] = 2.0; vertices[31] = 0.0; vertices[32] = -2.0; // 4
	//colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0; // 4

	//vertices[33] = 2.0; vertices[34] = 0.0; vertices[35] = -2.0; // 5
	//colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0; // 5

	vertices[36] = 2.0; vertices[37] = 0.0; vertices[38] = -2.0; // 4
	colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0; // 4

	vertices[39] = 2.0; vertices[40] = -1.0; vertices[41] = -2.0; // 5
	colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0; // 5

	vertices[42] = 2.0; vertices[43] = 0.0; vertices[44] = -3.0; // 6
	colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0; // 6

	vertices[45] = 2.0; vertices[46] = -1.0; vertices[47] = -2.0; // 5
	colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0; // 5

	vertices[48] = 2.0; vertices[49] = 0.0; vertices[50] = -3.0; // 6
	colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0; // 6

	vertices[51] = 2.0; vertices[52] = -1.0; vertices[53] = -3.0; // 7
	colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0; // 7

	vertices[54] = 2.0; vertices[55] = 0.0; vertices[56] = -3.0; // 6
	colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0; // 6

	vertices[57] = 2.0; vertices[58] = -1.0; vertices[59] = -3.0; // 7
	colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0; // 7

	vertices[60] = 0.0; vertices[61] = 0.0; vertices[62] = -3.0; // 8
	colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0; // 8

	vertices[63] = 2.0; vertices[64] = -1.0; vertices[65] = -3.0; // 7
	colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0; // 7

	vertices[66] = 0.0; vertices[67] = 0.0; vertices[68] = -3.0; // 8
	colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0; // 8

	vertices[69] = 0.0; vertices[70] = -1.0; vertices[71] = -3.0; // 9
	colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0; // 9

	vertices[72] = 0.0; vertices[73] = 0.0; vertices[74] = -3.0; // 8
	colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0; // 8

	vertices[75] = 0.0; vertices[76] = -1.0; vertices[77] = -3.0; // 9
	colors[75] = 0.0; colors[76] = 0.0; colors[77] = 1.0; // 9

	vertices[78] = 2.0; vertices[79] = -1.0; vertices[80] = -2.0; // 10
	colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0; // 10

	vertices[81] = 0.0; vertices[82] = -1.0; vertices[83] = -3.0; // 9
	colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0; // 9

	vertices[84] = 2.0; vertices[85] = -1.0; vertices[86] = -2.0; // 10
	colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0; // 10

	vertices[87] = 0.0; vertices[88] = -1.0; vertices[89] = -2.0; // 11
	colors[87] = 0.0; colors[88] = 0.0; colors[89] = 1.0; // 11

	vertices[90] = 2.0; vertices[91] = -1.0; vertices[92] = -2.0; // 10
	colors[90] = 0.0; colors[91] = 0.0; colors[92] = 1.0; // 10

	vertices[93] = 0.0; vertices[94] = -1.0; vertices[95] = -2.0; // 11
	colors[93] = 0.0; colors[94] = 0.0; colors[95] = 1.0; // 11

	vertices[96] = 2.0; vertices[97] = -1.0; vertices[98] = -3.0; // 12
	colors[96] = 0.0; colors[97] = 0.0; colors[98] = 1.0; // 12

	vertices[99] = 0.0; vertices[100] = -1.0; vertices[101] = -2.0; // 11
	colors[99] = 0.0; colors[100] = 0.0; colors[101] = 1.0; // 11

	vertices[102] = 2.0; vertices[103] = -1.0; vertices[104] = -3.0; // 12
	colors[102] = 0.0; colors[103] = 0.0; colors[104] = 1.0; // 12

	vertices[105] = 0.0; vertices[106] = -1.0; vertices[107] = -3.0; // 13
	colors[105] = 0.0; colors[106] = 0.0; colors[107] = 1.0; // 13

	vertices[108] = 2.0; vertices[109] = -1.0; vertices[110] = -3.0; // 12
	colors[108] = 0.0; colors[109] = 0.0; colors[110] = 1.0; // 12

	vertices[111] = 0.0; vertices[112] = -1.0; vertices[113] = -3.0; // 13
	colors[111] = 0.0; colors[112] = 0.0; colors[113] = 1.0; // 13

	vertices[114] = 0.0; vertices[115] = 0.0; vertices[116] = -3.0; // 14
	colors[114] = 0.0; colors[115] = 0.0; colors[116] = 1.0; // 14

	vertices[117] = 0.0; vertices[118] = -1.0; vertices[119] = -3.0; // 13
	colors[117] = 0.0; colors[118] = 0.0; colors[119] = 1.0; // 13

	vertices[120] = 0.0; vertices[121] = 0.0; vertices[122] = -3.0; // 14
	colors[120] = 0.0; colors[121] = 0.0; colors[122] = 1.0; // 14

	vertices[123] = 2.0; vertices[124] = 0.0; vertices[125] = -2.0; // 15
	colors[123] = 0.0; colors[124] = 0.0; colors[125] = 1.0; // 15

	vertices[126] = 0.0; vertices[127] = 0.0; vertices[128] = -3.0; // 14
	colors[126] = 0.0; colors[127] = 0.0; colors[128] = 1.0; // 14

	vertices[129] = 2.0; vertices[130] = 0.0; vertices[131] = -2.0; // 15
	colors[129] = 0.0; colors[130] = 0.0; colors[131] = 1.0; // 15

	vertices[132] = 2.0; vertices[133] = 0.0; vertices[134] = -3.0; // 16
	colors[132] = 0.0; colors[133] = 0.0; colors[134] = 1.0; // 16

	vertices[135] = 2.0; vertices[136] = 0.0; vertices[137] = -2.0; // 15
	colors[135] = 0.0; colors[136] = 0.0; colors[137] = 1.0; // 15

	vertices[138] = 2.0; vertices[139] = 0.0; vertices[140] = -3.0; // 16
	colors[138] = 0.0; colors[139] = 0.0; colors[140] = 1.0; // 16

	vertices[141] = 0.0; vertices[142] = 0.0; vertices[143] = -3.0; // 17
	colors[141] = 0.0; colors[142] = 0.0; colors[143] = 1.0; // 17

	vertices[144] = 2.0; vertices[145] = 0.0; vertices[146] = -3.0; // 16
	colors[144] = 0.0; colors[145] = 0.0; colors[146] = 1.0; // 16

	vertices[147] = 0.0; vertices[148] = 0.0; vertices[149] = -3.0; // 17
	colors[147] = 0.0; colors[148] = 0.0; colors[149] = 1.0; // 17

	vertices[150] = 0.0; vertices[151] = 0.0; vertices[152] = -2.0; // 18
	colors[150] = 0.0; colors[151] = 0.0; colors[152] = 1.0; // 18

	vertices[153] = 0.0; vertices[154] = 0.0; vertices[155] = -3.0; // 17
	colors[153] = 0.0; colors[154] = 0.0; colors[155] = 1.0; // 17

	vertices[156] = 0.0; vertices[157] = 0.0; vertices[158] = -2.0; // 18
	colors[156] = 0.0; colors[157] = 0.0; colors[158] = 1.0; // 18

	vertices[159] = 2.0; vertices[160] = 0.0; vertices[161] = -2.0; // 19
	colors[159] = 0.0; colors[160] = 0.0; colors[161] = 1.0; // 19

	vertices[162] = 0.0; vertices[163] = 0.0; vertices[164] = -2.0; // 18
	colors[162] = 0.0; colors[163] = 0.0; colors[164] = 1.0; // 18

	vertices[165] = 2.0; vertices[166] = 0.0; vertices[167] = -2.0; // 19
	colors[165] = 0.0; colors[166] = 0.0; colors[167] = 1.0; // 19

	vertices[168] = 2.0; vertices[169] = 0.0; vertices[170] = -3.0; // 20
	colors[168] = 0.0; colors[169] = 0.0; colors[170] = 1.0; // 20

	vertices[171] = 2.0; vertices[172] = 0.0; vertices[173] = -2.0; // 19
	colors[171] = 0.0; colors[172] = 0.0; colors[173] = 1.0; // 19

	vertices[174] = 2.0; vertices[175] = 0.0; vertices[176] = -3.0; // 20
	colors[174] = 0.0; colors[175] = 0.0; colors[176] = 1.0; // 20

	vertices[177] = 2.0; vertices[178] = 1.0; vertices[179] = -2.0; // 21
	colors[177] = 0.0; colors[178] = 0.0; colors[179] = 1.0; // 21

	vertices[180] = 2.0; vertices[181] = 0.0; vertices[182] = -3.0; // 20
	colors[180] = 0.0; colors[181] = 0.0; colors[182] = 1.0; // 20

	vertices[183] = 2.0; vertices[184] = 1.0; vertices[185] = -2.0; // 21
	colors[183] = 0.0; colors[184] = 0.0; colors[185] = 1.0; // 21

	vertices[186] = 2.0; vertices[187] = 1.0; vertices[188] = -3.0; // 22
	colors[186] = 0.0; colors[187] = 0.0; colors[188] = 1.0; // 22

	vertices[189] = 2.0; vertices[190] = 1.0; vertices[191] = -2.0; // 21
	colors[189] = 0.0; colors[190] = 0.0; colors[191] = 1.0; // 21

	vertices[192] = 2.0; vertices[193] = 1.0; vertices[194] = -3.0; // 22
	colors[192] = 0.0; colors[193] = 0.0; colors[194] = 1.0; // 22

	vertices[195] = 3.0; vertices[196] = 1.0; vertices[197] = -2.0; // 23
	colors[195] = 0.0; colors[196] = 0.0; colors[197] = 1.0; // 23    

	vertices[198] = 2.0; vertices[199] = 1.0; vertices[200] = -3.0; // 22
	colors[198] = 0.0; colors[199] = 0.0; colors[200] = 1.0; // 22

	vertices[201] = 3.0; vertices[202] = 1.0; vertices[203] = -2.0; // 23
	colors[201] = 0.0; colors[202] = 0.0; colors[203] = 1.0; // 23    

	vertices[204] = 3.0; vertices[205] = 1.0; vertices[206] = -3.0; // 24
	colors[204] = 0.0; colors[205] = 0.0; colors[206] = 1.0; // 24

	vertices[207] = 3.0; vertices[208] = 1.0; vertices[209] = -2.0; // 23
	colors[207] = 0.0; colors[208] = 0.0; colors[209] = 1.0; // 23    

	vertices[210] = 3.0; vertices[211] = 1.0; vertices[212] = -3.0; // 24
	colors[210] = 0.0; colors[211] = 0.0; colors[212] = 1.0; // 24

	vertices[213] = 2.0; vertices[214] = 1.0; vertices[215] = -3.0; // 25
	colors[213] = 0.0; colors[214] = 0.0; colors[215] = 1.0; // 25

	vertices[216] = 3.0; vertices[217] = 1.0; vertices[218] = -3.0; // 24
	colors[216] = 0.0; colors[217] = 0.0; colors[218] = 1.0; // 24

	vertices[219] = 2.0; vertices[220] = 1.0; vertices[221] = -3.0; // 25
	colors[219] = 0.0; colors[220] = 0.0; colors[221] = 1.0; // 25

	vertices[222] = 3.0; vertices[223] = -1.0; vertices[224] = -3.0; // 26
	colors[222] = 0.0; colors[223] = 0.0; colors[224] = 1.0; // 26

	vertices[225] = 2.0; vertices[226] = 1.0; vertices[227] = -3.0; // 25
	colors[225] = 0.0; colors[226] = 0.0; colors[227] = 1.0; // 25

	vertices[228] = 3.0; vertices[229] = -1.0; vertices[230] = -3.0; // 26
	colors[228] = 0.0; colors[229] = 0.0; colors[230] = 1.0; // 26

	vertices[231] = 2.0; vertices[232] = -1.0; vertices[233] = -3.0; // 27
	colors[231] = 0.0; colors[232] = 0.0; colors[233] = 1.0; // 27

	vertices[234] = 3.0; vertices[235] = -1.0; vertices[236] = -3.0; // 26
	colors[234] = 0.0; colors[235] = 0.0; colors[236] = 1.0; // 26

	vertices[237] = 2.0; vertices[238] = -1.0; vertices[239] = -3.0; // 27
	colors[237] = 0.0; colors[238] = 0.0; colors[239] = 1.0; // 27

	vertices[240] = 3.0; vertices[241] = -1.0; vertices[242] = -0.0; // 28
	colors[240] = 0.0; colors[241] = 0.0; colors[242] = 1.0; // 28

	vertices[243] = 2.0; vertices[244] = -1.0; vertices[245] = -3.0; // 27
	colors[243] = 0.0; colors[244] = 0.0; colors[245] = 1.0; // 27

	vertices[246] = 3.0; vertices[247] = -1.0; vertices[248] = -0.0; // 28
	colors[246] = 0.0; colors[247] = 0.0; colors[248] = 1.0; // 28

	vertices[249] = 2.0; vertices[250] = -1.0; vertices[251] = -0.0; // 29
	colors[249] = 0.0; colors[250] = 0.0; colors[251] = 1.0; // 29

	vertices[252] = 3.0; vertices[253] = -1.0; vertices[254] = -0.0; // 28
	colors[252] = 0.0; colors[253] = 0.0; colors[254] = 1.0; // 28

	vertices[255] = 2.0; vertices[256] = -1.0; vertices[257] = -0.0; // 29
	colors[255] = 0.0; colors[256] = 0.0; colors[257] = 1.0; // 29

	vertices[258] = 3.0; vertices[259] = 0.0; vertices[260] = -0.0; // 30
	colors[258] = 0.0; colors[259] = 0.0; colors[260] = 1.0; // 30

	vertices[261] = 2.0; vertices[262] = -1.0; vertices[263] = -0.0; // 29
	colors[261] = 0.0; colors[262] = 0.0; colors[263] = 1.0; // 29

	vertices[264] = 3.0; vertices[265] = 0.0; vertices[266] = -0.0; // 30
	colors[264] = 0.0; colors[265] = 0.0; colors[266] = 1.0; // 30

	vertices[267] = 2.0; vertices[268] = 0.0; vertices[269] = -0.0; // 31
	colors[267] = 0.0; colors[268] = 0.0; colors[269] = 1.0; // 31

	vertices[270] = 3.0; vertices[271] = 0.0; vertices[272] = -0.0; // 30
	colors[270] = 0.0; colors[271] = 0.0; colors[272] = 1.0; // 30

	vertices[273] = 2.0; vertices[274] = 0.0; vertices[275] = -0.0; // 31
	colors[273] = 0.0; colors[274] = 0.0; colors[275] = 1.0; // 31

	vertices[276] = 3.0; vertices[277] = 1.0; vertices[278] = -2.0; // 32
	colors[276] = 0.0; colors[277] = 0.0; colors[278] = 1.0; // 32

	vertices[279] = 2.0; vertices[280] = 0.0; vertices[281] = -0.0; // 31
	colors[279] = 0.0; colors[280] = 0.0; colors[281] = 1.0; // 31

	vertices[282] = 3.0; vertices[283] = 1.0; vertices[284] = -2.0; // 32
	colors[282] = 0.0; colors[283] = 0.0; colors[284] = 1.0; // 32

	vertices[285] = 2.0; vertices[286] = 1.0; vertices[287] = -2.0; // 33
	colors[285] = 0.0; colors[286] = 0.0; colors[287] = 1.0; // 33

	vertices[288] = 3.0; vertices[289] = 1.0; vertices[290] = -2.0; // 32
	colors[288] = 0.0; colors[289] = 0.0; colors[290] = 1.0; // 32

	vertices[291] = 2.0; vertices[292] = 1.0; vertices[293] = -2.0; // 33
	colors[291] = 0.0; colors[292] = 0.0; colors[293] = 1.0; // 33

	vertices[294] = 2.0; vertices[295] = -1.0; vertices[296] = -2.0; // 34
	colors[294] = 0.0; colors[295] = 0.0; colors[296] = 1.0; // 34

	vertices[297] = 2.0; vertices[298] = 1.0; vertices[299] = -2.0; // 33
	colors[297] = 0.0; colors[298] = 0.0; colors[299] = 1.0; // 33

	vertices[300] = 2.0; vertices[301] = -1.0; vertices[302] = -2.0; // 34
	colors[300] = 0.0; colors[301] = 0.0; colors[302] = 1.0; // 34

	vertices[303] = 2.0; vertices[304] = 0.0; vertices[305] = -0.0; // 35
	colors[303] = 0.0; colors[304] = 0.0; colors[305] = 1.0; // 35

	vertices[306] = 2.0; vertices[307] = -1.0; vertices[308] = -2.0; // 34
	colors[306] = 0.0; colors[307] = 0.0; colors[108] = 1.0; // 34

	vertices[309] = 2.0; vertices[310] = 0.0; vertices[311] = -0.0; // 35
	colors[309] = 0.0; colors[310] = 0.0; colors[311] = 1.0; // 35

	vertices[312] = 2.0; vertices[313] = -1.0; vertices[314] = -0.0; // 36
	colors[312] = 0.0; colors[313] = 0.0; colors[314] = 1.0; // 36

	vertices[315] = 2.0; vertices[316] = 0.0; vertices[317] = -0.0; // 35
	colors[315] = 0.0; colors[316] = 0.0; colors[317] = 1.0; // 35

	vertices[318] = 2.0; vertices[319] = -1.0; vertices[320] = -0.0; // 36
	colors[318] = 0.0; colors[319] = 0.0; colors[320] = 1.0; // 36

	vertices[321] = 3.0; vertices[322] = 1.0; vertices[323] = -2.0; // 37
	colors[321] = 0.0; colors[322] = 0.0; colors[323] = 1.0; // 37

	vertices[324] = 2.0; vertices[325] = -1.0; vertices[326] = -0.0; // 36
	colors[324] = 0.0; colors[325] = 0.0; colors[326] = 1.0; // 36

	vertices[327] = 3.0; vertices[328] = 1.0; vertices[329] = -2.0; // 37
	colors[327] = 0.0; colors[328] = 0.0; colors[329] = 1.0; // 37

	vertices[330] = 3.0; vertices[331] = -1.0; vertices[332] = -2.0; // 38
	colors[330] = 0.0; colors[331] = 0.0; colors[332] = 1.0; // 38

	vertices[333] = 3.0; vertices[334] = 1.0; vertices[335] = -2.0; // 37
	colors[333] = 0.0; colors[334] = 0.0; colors[335] = 1.0; // 37

	vertices[336] = 3.0; vertices[337] = -1.0; vertices[338] = -2.0; // 38
	colors[336] = 0.0; colors[337] = 0.0; colors[338] = 1.0; // 38

	vertices[339] = 3.0; vertices[340] = 0.0; vertices[341] = -0.0; // 39
	colors[339] = 0.0; colors[340] = 0.0; colors[341] = 1.0; // 39

	vertices[342] = 3.0; vertices[343] = -1.0; vertices[344] = -2.0; // 38
	colors[342] = 0.0; colors[343] = 0.0; colors[344] = 1.0; // 38

	vertices[345] = 3.0; vertices[346] = 0.0; vertices[347] = -0.0; // 39
	colors[345] = 0.0; colors[346] = 0.0; colors[347] = 1.0; // 39

	vertices[348] = 3.0; vertices[349] = -1.0; vertices[350] = -0.0; // 40
	colors[348] = 0.0; colors[349] = 0.0; colors[350] = 1.0; // 40

	vertices[351] = 3.0; vertices[352] = 0.0; vertices[353] = -0.0; // 39
	colors[351] = 0.0; colors[352] = 0.0; colors[353] = 1.0; // 39

	vertices[354] = 3.0; vertices[355] = -1.0; vertices[356] = -0.0; // 40
	colors[354] = 0.0; colors[355] = 0.0; colors[356] = 1.0; // 40

	vertices[357] = 3.0; vertices[358] = -1.0; vertices[359] = -3.0; // 41
	colors[357] = 0.0; colors[358] = 0.0; colors[359] = 1.0; // 41

	vertices[360] = 3.0; vertices[361] = -1.0; vertices[362] = -0.0; // 40
	colors[360] = 0.0; colors[361] = 0.0; colors[362] = 1.0; // 40

	vertices[363] = 3.0; vertices[364] = -1.0; vertices[365] = -3.0; // 41
	colors[363] = 0.0; colors[364] = 0.0; colors[365] = 1.0; // 41

	vertices[366] = 3.0; vertices[367] = 1.0; vertices[368] = -3.0; // 42
	colors[366] = 0.0; colors[367] = 0.0; colors[368] = 1.0; // 42

	vertices[369] = 3.0; vertices[370] = -1.0; vertices[371] = -3.0; // 41
	colors[369] = 0.0; colors[370] = 0.0; colors[371] = 1.0; // 41

	vertices[372] = 3.0; vertices[373] = 1.0; vertices[374] = -3.0; // 42
	colors[372] = 0.0; colors[373] = 0.0; colors[374] = 1.0; // 42

	vertices[375] = 3.0; vertices[376] = -1.0; vertices[377] = -2.0; // 43
	colors[375] = 0.0; colors[376] = 0.0; colors[377] = 1.0; // 43

	vertices[378] = 3.0; vertices[379] = 1.0; vertices[380] = -3.0; // 42
	colors[378] = 0.0; colors[379] = 0.0; colors[380] = 1.0; // 42

	vertices[381] = 3.0; vertices[382] = -1.0; vertices[383] = -2.0; // 43
	colors[381] = 0.0; colors[382] = 0.0; colors[383] = 1.0; // 43

	vertices[384] = 3.0; vertices[385] = 1.0; vertices[386] = -2.0; // 44
	colors[384] = 0.0; colors[385] = 0.0; colors[386] = 1.0; // 44

	vertices[387] = 0.0; vertices[388] = -1.0; vertices[389] = -2.0; // 44
	colors[387] = 0.0; colors[388] = 0.0; colors[389] = 1.0; // 44

	vertices[390] = 2.0; vertices[391] = 0.0; vertices[392] = -2.0; // 44
	colors[390] = 0.0; colors[391] = 0.0; colors[392] = 1.0; // 44

	vertices[393] = 2.0; vertices[394] = -1.0; vertices[395] = -2.0; // 44
	colors[393] = 0.0; colors[394] = 0.0; colors[395] = 1.0; // 44

	vertices[396] = 2.0; vertices[397] = -1.0; vertices[398] = -2.0; // 44
	colors[396] = 0.0; colors[397] = 0.0; colors[398] = 1.0; // 44

	vertices[399] = 2.0; vertices[400] = 0.0; vertices[401] = 0.0; // 44
	colors[399] = 0.0; colors[400] = 0.0; colors[401] = 1.0; // 44

	vertices[402] = 2.0; vertices[403] = -1.0; vertices[404] = 0.0; // 44
	colors[402] = 0.0; colors[403] = 0.0; colors[404] = 1.0; // 44

	vertices[405] = 0.0; vertices[406] = -1.0; vertices[407] = -2.0; // 3
	colors[405] = 0.0; colors[406] = 0.0; colors[407] = 1.0; // 3

	vertices[408] = 2.0; vertices[409] = -1.0; vertices[410] = -2.0; // 5
	colors[408] = 0.0; colors[409] = 0.0; colors[410] = 1.0; // 5

	vertices[411] = 0.0; vertices[412] = -1.0; vertices[413] = -3.0; // 1
	colors[411] = 0.0; colors[412] = 0.0; colors[413] = 1.0; // 1

	vertices[414] = 2.0; vertices[415] = -1.0; vertices[416] = -2.0; // 5
	colors[414] = 0.0; colors[415] = 0.0; colors[416] = 1.0; // 5

	vertices[417] = 0.0; vertices[418] = -1.0; vertices[419] = -3.0; // 1
	colors[417] = 0.0; colors[418] = 0.0; colors[419] = 1.0; // 1

	vertices[420] = 2.0; vertices[421] = -1.0; vertices[422] = -3.0; // 7
	colors[420] = 0.0; colors[421] = 0.0; colors[422] = 1.0; // 7

	glGenVertexArrays(2, &vaoID[1]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it


	glGenBuffers(2, vboID); // Generate our Vertex Buffer Object

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 423 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


	//Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 423 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory

	//TODO:
	vaoID[1];

	return 1;
}



/*!
ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
*/
void renderTriangleStripModel(void)
{

	// Bind the buffer and switch it to an active buffer
	glBindVertexArray(vaoID[0]);

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
	// Draw the triangles
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 134 );


	// Unbind our Vertex Array Object
	glBindVertexArray(0);
}



/*!
ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
*/
void renderPolygonModel(void)
{

	// Bind the buffer and switch it to an active buffer
	glBindVertexArray(vaoID[1]);


	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0 , 26 );
	glDrawArrays(GL_TRIANGLES, 36 , 423 );

	// Unbind our Vertex Array Object
	glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
This function creates the two models
*/
void setupScene(void) {

	  createTriangleStripModel();
	  // renderTriangleStripModel();
	  createPolygonModel();
	  // renderPolygonModel();

}




int main(int argc, const char * argv[])
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Init glfw, create a window, and init glew

	// Init the GLFW Window
	window = initWindow();


	// Init the glew api
	initGlew();

	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// The Shader Program starts here

	// Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
	// Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
	static const string vertex_code = vs_string;
	static const char * vs_source = vertex_code.c_str();

	// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
	static const string fragment_code = fs_string;
	static const char * fs_source = fragment_code.c_str();

	// This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
	program = glCreateProgram();

	// We create a shader with our fragment shader source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);

	// We create a shader with our vertex shader source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);

	// We'll attach our two compiled shaders to the OpenGL program.
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	// We'll specify that we want to use this program that we've attached the shaders to.
	glUseProgram(program);

	//// The Shader Program ends here
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/// IGNORE THE NEXT PART OF THIS CODE
	/// IGNORE THE NEXT PART OF THIS CODE
	/// IGNORE THE NEXT PART OF THIS CODE
	// It controls the virtual camera

	// Set up our green background color
	static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
	viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader


	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader


	//// The Shader Program ends here
	//// START TO READ AGAIN
	//// START TO READ AGAIN
	//// START TO READ AGAIN
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	glBindAttribLocation(program, 0, "in_Position");
	glBindAttribLocation(program, 1, "in_Color");



	// this creates the scene
	setupScene();

	int i = 0;

	// Enable depth test
	// ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
	glEnable(GL_DEPTH_TEST);

	// This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
	while (!glfwWindowShouldClose(window))
	{

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		// this draws the coordinate system
		coordinate_system_renderer->draw();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// This generate the object
		// Enable the shader program
		glUseProgram(program);

		// this changes the camera location
		glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader


		// This moves the model to the right
		modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader


		// This line renders your triangle strip model
		renderTriangleStripModel();


		// This moves the model to the left
		modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

		// This line renders your Ppolygon model
		renderPolygonModel();


		// disable the shader program
		glUseProgram(0);


		//// This generate the object
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// delete the coordinate system object
	delete coordinate_system_renderer;

	// Program clean up when the window gets closed.
	glDeleteVertexArrays(2, vaoID);
	glDeleteProgram(program);
}

