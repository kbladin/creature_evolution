#version 330 core

// Input data
in vec3 position_worldspace;

// Ouput data
out vec3 color;

void main()
{
	// Output color 
	color = (position_worldspace * 0.5 +  vec3(0.5, 0.5, 0.5)) *
		position_worldspace.y + position_worldspace * 0.1;
}
