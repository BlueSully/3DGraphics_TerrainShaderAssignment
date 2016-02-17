uniform sampler2D grassTex;
uniform sampler2D waterTex;
uniform sampler2D rockTex;
uniform sampler2D snowTex;

varying vec4 specular;
varying float height;

void main(void)
{
    vec4 texel;//Hold the textures colours

	if(height < 0.05f && height < 0.2f)
	{
		texel = texture2D(waterTex,gl_TexCoord[0].st);//water
	}
	else if(height < 0.2f)
	{
		//water, grass
		float localheight = height - 0.05f;
		float percent = localheight / 0.05f;
		vec4 c1 = texture2D(waterTex,gl_TexCoord[0].st);
		vec4 c2 = texture2D(grassTex,gl_TexCoord[0].st);
		
		texel = mix(c1, c2, percent);
	}
	else if(height > 0.2f && height < 2.0f)
	{		
		texel = texture2D(grassTex,gl_TexCoord[0].st);//grass
	}

	else if(height < 2.0f){
		//grass, rock
		float localheight = height - 0.6f;
		float percent = localheight / 0.15f;
		vec4 c1 = texture2D(grassTex, gl_TexCoord[0].st);
		vec4 c2 = texture2D(rockTex, gl_TexCoord[0].st);
		
		texel = mix(c1, c2, percent);
	}

	else if(height > 2.0f && height < 6.0f)
	{
		texel = texture2D(rockTex,gl_TexCoord[0].st);
	}
	else if(height > 0.6f && height < 0.7f)
	{
		//rock, snow
		float localheight = height - 0.05f;
		float percent = localheight / 0.05f;
		vec4 c1 = texture2D(rockTex,gl_TexCoord[0].st);
		vec4 c2 = texture2D(snowTex,gl_TexCoord[0].st);
		
		texel = mix(c1, c2, percent);
	}
	else
	{
		texel = texture2D(snowTex,gl_TexCoord[0].st);//snow
	}


    gl_FragColor = gl_Color* texel;
}