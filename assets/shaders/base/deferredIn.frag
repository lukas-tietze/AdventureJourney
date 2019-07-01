#version 430 core

layout(binding = 0) uniform sampler2D albedoMap;

layout (location = 0) out vec3 gColor;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gMaterial;

in vec3 vNormalWs;
in vec2 vTexcoord;
in vec4 vColor;

vec3 GetNormal();
vec4 GetAlbedo();
vec3 GetMaterialProps();

void main()
{
    gColor = GetAlbedo().rgb;
    gNormal = GetNormal();
    gMaterial = GetMaterialProps();
}