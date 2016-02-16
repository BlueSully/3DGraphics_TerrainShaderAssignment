varying float height;

varying vec4 specular;
uniform float tallestPoint;

void main()
{
	vec3 normal, lightDir, viewVector, halfVector;
	vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
	float NdotL,NdotHV;

	height = gl_Vertex.y / tallestPoint;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	normal = normalize(gl_NormalMatrix * gl_Normal);

	vec4 pointEyeSpace = (gl_ModelViewMatrix * gl_Vertex);
	lightDir = normalize(vec3(gl_LightSource[0].position) - pointEyeSpace.xyz);
	
	NdotL = max(dot(normal, lightDir), 0.0);
	
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	vec4 cameraDir = -pointEyeSpace;
	halfVector = normalize((lightDir + cameraDir)).xyz;

	if (NdotL > 0.0) 
	{
		// normalize the half-vector, and then compute the
		// cosine (dot product) with the normal
		NdotHV = max(dot(normal, halfVector.xyz),0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
	}

	gl_FrontColor = globalAmbient + NdotL * diffuse + ambient + specular;
	
	gl_Position = ftransform();
}
