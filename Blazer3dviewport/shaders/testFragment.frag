#version 450 core

in vec3 fragcolor;
out vec4 outcolor;

void main()
{
	outcolor = vec4(fragcolor, 1.0f);
}