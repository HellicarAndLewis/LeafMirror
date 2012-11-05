#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect src_tex_unit0;
uniform float brightness;
uniform int direction;

float coeffs[3]; //= float[](0.2270270270, 0.3162162162, 0.0702702703);

void main()
{
	coeffs[0]=0.2270270270;
	coeffs[1]= 0.3162162162;
	coeffs[2]=0.0702702703;

	vec2 st = gl_TexCoord[0].st;
	if(direction == 0){
		//horizontal blur 
		//from http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
		
		vec4 color = vec4(0.0,0.0,0.0,0.0);
		
		color += coeffs[2] * texture2DRect(src_tex_unit0, st - vec2(2.0, 0.0)).rgba;
		color += coeffs[1] * texture2DRect(src_tex_unit0, st - vec2(1.0, 0.0)).rgba;
		color += coeffs[0] * texture2DRect(src_tex_unit0, st).rgba;
		color += coeffs[2] * texture2DRect(src_tex_unit0, st + vec2(2.0, 0.0)).rgba;
		color += coeffs[1] * texture2DRect(src_tex_unit0, st + vec2(1.0, 0.0)).rgba;
		
		gl_FragColor = vec4(color.r*brightness,color.g*brightness,color.b*brightness, color.a);
	}else{
		vec4 color = vec4(0.0,0.0,0.0,0.0);
		
		color += coeffs[2] * texture2DRect(src_tex_unit0, st - vec2(0.0, 2.0)).rgba;
		color += coeffs[1] * texture2DRect(src_tex_unit0, st - vec2(0.0, 1.0)).rgba;
		color += coeffs[0] * texture2DRect(src_tex_unit0, st).rgba;
		color += coeffs[2] * texture2DRect(src_tex_unit0, st + vec2(0.0, 2.0)).rgba;
		color += coeffs[1] * texture2DRect(src_tex_unit0, st + vec2(0.0, 1.0)).rgba;
		
		gl_FragColor = vec4(color.r*brightness,color.g*brightness,color.b*brightness, color.a);
	}
	gl_FragDepth = gl_FragCoord.z;
}
