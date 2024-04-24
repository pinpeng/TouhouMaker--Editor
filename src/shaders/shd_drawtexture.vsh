#version 330 core

in vec2 in_position;

out vec2 v_texCoord;

uniform mat4 u_MVPMatrix;

void main()
{
	gl_Position = u_MVPMatrix * vec4(in_position, 0.0, 1.0);
	v_texCoord = in_position;
}
