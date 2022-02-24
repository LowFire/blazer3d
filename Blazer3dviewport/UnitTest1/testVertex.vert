#version 450 core

in layout (location = 0) vec3 vpos;
in layout (location = 1) vec3 vcolor;
out vec3 fragcolor;

void main()
{
	gl_Position = vec4(vpos, 1.0f);
	fragcolor = vcolor;
}
