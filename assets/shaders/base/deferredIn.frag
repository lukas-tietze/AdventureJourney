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

const float ONE_HALF_V1 = 0.5;
const vec2 ONE_HALF_V2 = vec2(0.5);
const vec3 ONE_HALF_V3 = vec3(0.5);
const vec4 ONE_HALF_V4 = vec4(0.5);

void main()
{
    gColor = GetAlbedo().rgb;
    gNormal = GetNormal() * ONE_HALF_V3 + ONE_HALF_V3;
    gMaterial = GetMaterialProps();
}