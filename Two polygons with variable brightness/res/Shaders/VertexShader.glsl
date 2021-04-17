#version 330 core 

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec3 inputColor;

//uniform float intensity;

out vec3 color; 

void main() 
{ 
	gl_Position = vec4(inputPosition.xyz, 1.0); 
	color = inputColor;
} ;