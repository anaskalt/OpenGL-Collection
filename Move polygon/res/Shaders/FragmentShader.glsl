#version 330 core 

in vec3 color;

void main() 
{ 
	//gl_FragColor = vec4(color, 1.0); 
	gl_FragColor = vec4(color.r, color.g, 0.0, 1.0); 
} 