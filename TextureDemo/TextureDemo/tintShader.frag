// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec3 tint_interp;
in vec2 uv_interp;

out vec4 FragColor;

uniform sampler2D onetex;

void main()
{
	vec4 color = texture2D(onetex, uv_interp);

	float newR = tint_interp.x;
	float newG = tint_interp.y;
	float newB = tint_interp.z;

	float grey = (color.r + color.g + color.g) / 3;
	float tintGrey = (newR + newG + newB) / 3;

	float dr =  grey - tintGrey;    
	float dg =  grey - tintGrey;    
	float db =  grey - tintGrey;  

	float tintR = newR + dr;    
	float tintG = newG + dg;   
	float tintB = newB + db;

	FragColor = vec4(newR, newG, newB, color.a);
	
	//FragColor = vec4(color.r, color.g, color.b, color.a);
    if(FragColor.a < 0.9)
	{
		discard;
		//gl_FragDepth = 10000;
//		FragColor = vec4(color.r,color.g,color.b,0.5);
	}
//	 FragColor = color_interp;
}