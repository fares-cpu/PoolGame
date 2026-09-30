#version 330 core

struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular2;
	float shininess;
};

struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct FlashLight{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Material material;
uniform vec3 viewPos;

uniform DirLight dirLight;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3 diffuseMap = texture(material.texture_diffuse1, TexCoord).rgb;
vec3 specularMap = texture(material.texture_specular1, TexCoord).rgb;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(){
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = calcDirLight(dirLight, norm, viewDir);
	if(result == vec3(0.0, 0.0, 0.0)){
		FragColor = vec4(1.0, 0.0, 1.0, 1.0);
		return;
	}

	FragColor = vec4(result, 1.0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 diffuse = light.diffuse * diff * diffuseMap;
	vec3 specular = light.specular * spec * specularMap;

	return (light.ambient * diffuseMap + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir= reflect(-lightDir, normal);

	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - fragPos);
	float annutation = 1 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	vec3 ambient = light.ambient * annutation * diffuseMap;
	vec3 diffuse = light.diffuse * diff * annutation * diffuseMap;
	vec3 specular = light.diffuse * spec * annutation * specularMap;

	//return (ambient + diffuse + specular);
	return vec3(0.0f, 0.0f, 0.0f);
}

vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float dist = length(light.position - fragPos);
	float annutation = 1 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	float theta = dot(lightDir,	normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * diffuseMap;
	vec3 diffuse = light.diffuse * diff * annutation * diffuseMap;
	vec3 specular = light.specular * spec * annutation * specularMap;

	diffuse*= intensity;
	specular *= intensity;

	//return (ambient + diffuse + specular);
	return vec3(0.0f, 0.0f, 0.0f);
}