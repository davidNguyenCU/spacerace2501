#version 130

in vec4 color_interp;
in vec2 uv_interp;
in float acttime;

out vec4 FragColor;

uniform float time;
uniform sampler2D onetex;
void main()
{
	vec4 color = texture2D(onetex, uv_interp);
	float r = 0;
	float g = 0;
	float b = 0;

	if(acttime < 0.15)
	{
		g = 255;
	}

	else if(acttime > 0.15 && acttime <= 0.30)
	{
		g = 255;
		b = 255;
	}

	else if(acttime > 0.3 && acttime <= 0.45)
	{
		b = 255;
	}

	else if(acttime > 0.45 && acttime <= 0.60)
	{
		b = 255;
		r = 255;
	}

	else if(acttime > 0.60 && acttime <= 0.90)
	{
		r = 255;
	}

	else if(acttime > 0.90)
	{
		r = 255;
		g = 255;
	}

	vec4 newColor = vec4(r, g, b, color.a-(time/7));

    
	FragColor = newColor;
}