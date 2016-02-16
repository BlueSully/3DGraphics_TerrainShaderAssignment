uniform sampler2D grassTex;
uniform sampler2D waterTex;
uniform sampler2D rockTex;
uniform sampler2D snowTex;
varying float height;

void main()
{
	vec4 color;

	if(height < 0.05f)
	{
		//water
		color = texture2D(waterTex,gl_TexCoord[0].st);
	}

	else if(height < 0.2f)
	{
		//water, grass
		float localheight = height - 0.05f;
		float percent = localheight / 0.05f;
		vec4 c1 = texture2D(waterTex,gl_TexCoord[0].st);
		vec4 c2 = texture2D(grassTex,gl_TexCoord[0].st);
		
		color = mix(c1, c2, percent);
	}

	else if(height > 0.2f && height < 0.6f)
	{
		//grass
		color = texture2D(grassTex,gl_TexCoord[0].st);
	}

	else if(height < 0.6f){
		//grass, rock
		float localheight = height - 0.6f;
		float percent = localheight / 0.15f;
		vec4 c1 = texture2D(grassTex, gl_TexCoord[0].st);
		vec4 c2 = texture2D(rockTex, gl_TexCoord[0].st);
		
		color = mix(c1, c2, percent);
	}
	else if(height > 0.6f && height < 2.0f)
	{
		color = texture2D(rockTex,gl_TexCoord[0].st);
	}
	else if(height > 1.0f && height < 2.0f){
		//grass, rock
		float localheight = height - 0.6f;
		float percent = localheight / 0.15f;
		vec4 c1 = texture2D(grassTex, gl_TexCoord[0].st);
		vec4 c2 = texture2D(rockTex, gl_TexCoord[0].st);
		
		color = mix(c1, c2, percent);
	}

	else
	{
		//snow
		color = texture2D(snowTex,gl_TexCoord[0].st);
	}
		 
    gl_FragColor = color;
}