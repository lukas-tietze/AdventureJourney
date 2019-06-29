#version 430 core

layout(binding = 0) uniform sampler2D albedoMap;

layout (location = 0) out vec3 gClr;
layout (location = 1) out vec3 gNrm;
layout (location = 2) out vec3 gMat;

in vec3 vNormal;
in vec2 vTexcoord;
in vec4 vColor;

vec3 GetNormal();
vec4 GetAlbedo()
vec3 GetMaterialProperties();

void main()
{
    gClr = GetAlbedo().rgb;
    gNrm = vNormal;
    gMat = vNormal * texture(albedoMap, vTexcoord).rgb;
}