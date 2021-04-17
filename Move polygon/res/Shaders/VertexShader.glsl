#version 330 core 

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec3 inputColor;

uniform mat4 transform;

out vec3 color; 

void main() 
{ 
	color = inputColor;
	gl_Position = transform*vec4(inputPosition.xyz, 1.0); 
	// Synthikes gia rgb
	if(gl_Position.x == -1.0f){
		color.r = 0.0f;
	}
	if(gl_Position.x == 1.0f){
		color.r = 1.0f;
	}

	if(gl_Position.y == -1.0f){
		color.g = 0.0f;
	}
	if(gl_Position.y == 1.0f){
		color.g = 1.0f;
	}

	else
		color.r = gl_Position.x;
		color.g = gl_Position.y;
} ;