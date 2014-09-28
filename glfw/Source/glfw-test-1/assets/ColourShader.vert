#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 1) in vec3 aVertexPosition;
layout(location = 2) in vec4 aVertexColor;
layout(location = 3) in vec3 aVertexNormals;

uniform mat4 MVP;

out vec4 colorForFrag;

void main(){
	colorForFrag = aVertexColor - vec4(aVertexNormals, 0)*0.0001;
	gl_Position = MVP * vec4(aVertexPosition, 1.0);
}