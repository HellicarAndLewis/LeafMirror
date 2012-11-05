#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect src_tex_unit0;
uniform vec2 tcOffset[9]; // Texture coordinate offsets

void main()
{
	vec4 sample[9];
	vec4 maxValue = vec4(0.0);
 	vec2 st = gl_TexCoord[0].st;
 	
	for (int i = 0; i < 9; i++)
	{
		// Sample a grid around and including our texel
		sample[i] = texture2DRect(src_tex_unit0, st + tcOffset[i]);
 		// Keep the maximum value		
		maxValue = max(sample[i], maxValue);
	}
 
	gl_FragColor = maxValue;
}
