#version 330

in vec2 texCoordFrag;
out vec4 outColor;

uniform sampler2D tex;
uniform int customTexCoord;
uniform vec4 frame;
uniform vec4 color;

void main()
{
	vec4 texColor;
	
	if(customTexCoord == 0)
	{
		texColor = texture(tex, texCoordFrag);
	}
	else
	{
		vec2 newTexCoordFrag = frame.zw * texCoordFrag + frame.xy;
		texColor = texture(tex, newTexCoordFrag);
	}
	
	if(texColor.a < 0.5) discard;
	outColor = texColor * color;
}

