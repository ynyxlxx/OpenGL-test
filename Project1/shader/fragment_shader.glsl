#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

//Functions
vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos)
{
	vec3 posToLightDirVec = normalize(lightPos - vs_position);
	float diffuseConstant = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = diffuseConstant * material.diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos, vec3 cameraPos) 
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, vs_normal));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = material.specular * specularConstant;

	return specularFinal;
}


//Main
void main()
{	
	//Ambient light
	vec3 ambientFinal = calculateAmbient(material);

	//Diffuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);

	//Specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);

	//Attenuation


	fs_color = texture(material.diffuseTex, vs_texcoord)
	* vec4(vs_color, 1.f)
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

}