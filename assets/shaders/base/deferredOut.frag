#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D pos;
layout(location = 0) uniform sampler2D nrm;
layout(location = 0) uniform sampler2D clr;

out vec4 fClr;

vec4 CalcLighting(in vec3 pos, in vec3 normal, in vec3 albedo, in float shininess);

void main()
{
    vec4 vPos = texture(pos, vTex);
    vec4 vNrm = texture(nrm, vTex);
    vec4 vClr = texture(clr, vTex);

    fClr = CalcLighting(vPos.xyz, vNrm.xyz, vClr.rgb, vClr.a);
}