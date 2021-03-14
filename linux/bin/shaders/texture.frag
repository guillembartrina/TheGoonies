#version 330

in vec2 texCoordFrag;
out vec4 outColor;

uniform sampler2D tex;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	vec4 texColor = texture(tex, texCoordFrag);
	if(texColor.a < 0.5) discard;
	outColor = texColor;
}

