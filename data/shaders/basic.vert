#version 330 core

// Input data
layout(location = 0) in vec3 vertexPosition_modelspace;

// Uniforms
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform mat4 V;

// Output data
out vec3 position_worldspace;

void main(){
	// Just to "use" them to not get warnings
	MV;
	V;

	position_worldspace = vec3(M * vec4(vertexPosition_modelspace,1));

	// Output position of the vertex
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
}

