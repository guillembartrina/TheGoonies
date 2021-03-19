#version 330

in vec2 texCoordFrag;
out vec4 outColor;

uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, texCoordFrag);
	if(texColor.a < 0.5) discard;
	outColor = texColor;
}

