#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 vertexColor;

out vec4 theColor;

uniform float time;

void main() {
	vec3 Position = aPos;
	
	// Some equations used for testing other effects, not the fire 
	//Position.y = sin(time + aPos.y);
	//Position.x = cos(aPos.x);
	//Position.y = -1 * Position.y;
	
	gl_Position = vec4(Position, 1.0f);
	theColor = vertexColor;
}