#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D pos;
layout(location = 1) uniform sampler2D nrm;
layout(location = 2) uniform sampler2D clr;
layout(location = 3) uniform sampler2D mat;

out vec4 fClr;

vec4 CalcLighting(in vec3 pos, in vec3 normal, in vec3 albedo, in vec4 materialProperties);

void main()
{
    vec4 vPos = texture(pos, vTex);
    vec4 vNrm = texture(nrm, vTex);
    vec4 vClr = texture(clr, vTex);
    vec4 vMat = texture(mat, vTex);

    fClr = CalcLighting(vPos.xyz, vNrm.xyz, vClr.rgb, vMat);
}