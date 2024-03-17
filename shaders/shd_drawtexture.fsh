#version 330 core

in vec2 v_texCoord;

out vec4 FragColor;

uniform sampler2D u_baseTexture;

void main()
{
	FragColor = texture(u_baseTexture, v_texCoord);
}