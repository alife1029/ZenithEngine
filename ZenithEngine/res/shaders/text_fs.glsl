#version 450 core

#define MAX_TEXTURES

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

out vec4 FragColor;

uniform sampler2D u_Samplers[MAX_TEXTURES];

void main()
{
	int texIndex = int(v_TexIndex);
	FragColor = vec4(1.0, 1.0, 1.0, texture(u_Samplers[texIndex], v_TexCoord)) * v_Color;
}
