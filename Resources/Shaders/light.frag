#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuseMap;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 NormalVec;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 frag_color;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 normal = normalize(NormalVec);
	vec3 lightDir = normalize(light.position - FragPos);
	float NDotL = max(dot(normal, lightDir),0.0f);
	vec3 diffuse = vec3(texture(material.diffuseMap, TexCoord)) * light.diffuse * NDotL;

	//phongspecular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, NormalVec);
	float RDotV = max(dot(viewDir, reflectDir),0.0f);
	vec3 specular = light.specular * material.specular * pow(RDotV, material.shininess);

	//blinn-phong specular, Saves a call on reflect()
	viewDir = normalize(viewPos - FragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float NDotH = max(dot(NormalVec, halfDir),0.0f);
	specular = light.specular * material.specular * pow(NDotH, material.shininess);


	vec4 texel = texture(material.diffuseMap, TexCoord);
	frag_color = vec4(ambient + diffuse + specular, 1.0f) * texel;
};