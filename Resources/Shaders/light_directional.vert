#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 NormalVec;
out vec3 FragPos; //Fragment in world space?
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);


	TexCoord = texCoord;
	NormalVec = mat3(transpose(inverse(model))) * normal;
	NormalVec = normalize(NormalVec);
	//NormalVec = normal;
	FragPos = vec3(model * vec4(pos, 1.0));
};