#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

uniform float time;

void main ()
{
	vec3 Position = aPos;
	Position.y = sin(time + aPos.y);

	gl_Position =  Projection * View * Model * vec4(Position, 1.0f);
}