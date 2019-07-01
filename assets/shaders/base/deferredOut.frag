#version 430 core

in vec2 vTexcoord;

layout(binding = 0) uniform sampler2D gColor;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gMaterial;
layout(binding = 3) uniform sampler2D gDepth;

out vec4 fClr;

vec4 CalcLighting(in vec3 pos, in vec3 normal, in vec3 albedo, in vec3 materialProperties);

void main()
{
    fClr = CalcLighting(vec3(gl_FragCoord.xy, texture(gDepth, vTexcoord).r),
     texture(gNormal, vTexcoord).xyz, 
     texture(gColor, vTexcoord).rgb,
     texture(gMaterial, vTexcoord).rgb);
}