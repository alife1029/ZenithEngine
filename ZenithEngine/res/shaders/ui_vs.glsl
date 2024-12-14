#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in float a_TexIndex;

uniform vec2 u_WindowSize;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoords;
	v_TexIndex = a_TexIndex;
	gl_Position = vec4(
		2.0 * a_Position.x / u_WindowSize.x - 1.0, 
		2.0 * a_Position.y / u_WindowSize.y - 1.0,
		0.0,
		1.0
	);
}
