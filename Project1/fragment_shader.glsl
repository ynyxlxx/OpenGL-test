#version 440

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform sampler2D texture0;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

void main()
{	
	//fs_color = vec4(vs_color, 1.f);

	//Ambient light
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);

	//Diffuse light
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	float diffuseConstant = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = diffuseConstant * diffuseColor;

	//Specular light
	vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = reflect(lightToPosDirVec, vs_normal);
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
	vec3 specularFinal = vec3(1.f, 1.f, 1.f) * specularConstant;

	//Attenuation

	fs_color = texture(texture0, vs_texcoord)
	* vec4(vs_color, 1.f)
	* (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}