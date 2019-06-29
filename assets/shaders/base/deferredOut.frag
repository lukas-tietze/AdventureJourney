#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D gClr;
layout(location = 1) uniform sampler2D gNrm;
layout(location = 2) uniform sampler2D gMat;
layout(location = 3) uniform sampler2D gDepth;

out vec4 fClr;

vec4 CalcLighting(in vec3 pos, in vec3 normal, in vec3 albedo, in vec4 materialProperties);

void main()
{
    // fClr = CalcLighting(vPos.xyz, vNrm.xyz, vClr.rgb, vMat);
    fClr.rgb = texture(gDepth, vTex).rgb / 2.0;
    fClr.a = 1.0;
}