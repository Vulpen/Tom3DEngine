#version 330 core

in vec3 NormalVec;
in vec2 TexCoord;
in vec3 FragPos;

out vec4 frag_color;

uniform vec3 surfaceColor;
uniform vec3 cameraPos;
uniform vec3 lightPos;

void main()
{
	vec3 colorCool = vec3( 0, 0, 0.55f) + 0.25f * surfaceColor;
	vec3 colorWarm = vec3(0.3f, 0.3f, 0.0f) + 0.25f * surfaceColor;
	vec3 colorHighlight = vec3(1.0f,1.0f,1.0f);

	vec3 n = normalize(NormalVec);
	vec3 l = normalize(lightPos - FragPos);
	vec3 v = normalize(cameraPos - FragPos);

	//variable 't'
	float warmCool =  (dot(n,l) + 1) / 2.0f;
	//variable 'r' reflection of light across normal
	vec3 r = (2 * dot(n,l) * n) - l;
	//variable 's' or shininess
	float s = 100 * dot(r,v) - 97;
	s = clamp(s, 0.0f, 1.0f);

	frag_color = vec4(FragPos, 1.0f);
	vec3 mixColor = warmCool * colorWarm + (1-warmCool)*colorCool;
	frag_color = vec4(   (  s * colorHighlight + (1 - s) * mixColor  )   , 1.0f);
};