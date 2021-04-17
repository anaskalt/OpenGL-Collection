#version 330 core 

//uniform float greenChannel;
uniform float intensity;

in vec3 color;

void main() 
{ 
	gl_FragColor = vec4(color*intensity, 1.0); 
	//gl_FragColor = vec4(1.0f, greenChannel, 0.0f, 1.0); 
} 