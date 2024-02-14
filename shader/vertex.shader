#version 460 core

layout(location=0) in vec4 in_position;
layout(location=1) in vec4 in_normal;

out vec4 normal;

uniform mat4 cam_space;

void main()
{
	gl_Position = cam_space * in_position;
	normal = in_normal;
};
