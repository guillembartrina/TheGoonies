#version 330

in vec2 position;
in vec2 texCoord;
out vec2 texCoordFrag;

uniform mat4 projection, modelview;

void main()
{
	texCoordFrag = texCoord;
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}

