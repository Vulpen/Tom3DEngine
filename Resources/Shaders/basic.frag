#version 330 core

in vec3 NormalVec;
in vec2 TexCoord;

out vec4 frag_color;

uniform vec3 lightColor;
//uniform vec4 vertColor;
uniform sampler2D myTexture;

void main()
{
	frag_color = vec4(lightColor, 1.0f);
	//frag_color = frag_color * dot(NormalVec, vec3(0.0,1.0,0.0)) * 10;
	//frag_color = vec4(NormalVec,1.0f);
	frag_color = texture(myTexture, TexCoord);
};