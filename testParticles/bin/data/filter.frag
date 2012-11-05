#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect fboCurrent;
uniform sampler2DRect fboPrev;
uniform float filterFactor;

void main()
{

	vec2 st = gl_TexCoord[0].st;
	
	gl_FragColor = texture2DRect(fboPrev, st).rgba*filterFactor + texture2DRect(fboCurrent, st).rgba*(1-filterFactor);
	
	gl_FragDepth = gl_FragCoord.z;
}
