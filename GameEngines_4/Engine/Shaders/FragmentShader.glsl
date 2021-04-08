#version 450 core
in vec3 Normal;
in vec2 TexCoords;
in  vec3 FragPosition;

uniform sampler2D inputTexture;
uniform vec3 cameraPosition;


out vec4 fColour;

struct Light
{
	vec3 lightPos;
	vec3 lightColour;
	float ambient;
	float diffuse;
	float specular;
};

uniform Light lights;

void main(){
	vec3 ambient = lights.ambient * texture(inputTexture, TexCoords).rgb * lights.lightColour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lights.lightPos - FragPosition);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = (diff * lights.diffuse) * texture(inputTexture, TexCoords).rgb * lights.lightColour;
	
	vec3 viewDir  = normalize(cameraPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = (spec * lights.specular) * lights.lightColour;

	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result,1.0f);
}