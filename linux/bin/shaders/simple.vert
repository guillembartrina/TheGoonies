#version 330

uniform mat4 projection, modelview;

in vec2 position;
in vec2 texCoord;

void main()
{
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}
