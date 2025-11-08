#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform vec2 lightPos;
uniform float radius;

void main()
{
	vec4 color = texture(texture0, fragTexCoord);

	vec2 pixelPos = fragTexCoord * resolution;

	float distance= length(pixelPos - lightPos);

	if(distance > radius)
	{
		color.rgb *= 0.2;
	}

	finalColor = color;
}
