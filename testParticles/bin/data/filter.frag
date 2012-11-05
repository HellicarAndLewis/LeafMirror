#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect fboCurrent;
uniform sampler2DRect fboPrev;


void main()
{

	vec2 st = gl_TexCoord[0].st;
	
	gl_FragColor = texture2DRect(fboPrev, st).rgba*.95 + texture2DRect(fboCurrent, st).rgba*.05;
	
	gl_FragDepth = gl_FragCoord.z;
}
