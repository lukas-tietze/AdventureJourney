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
    vec3 color = texture(gColor, vTexcoord).rgb;
    vec3 normal = texture(gNormal, vTexcoord).xyz * vec3(2.0) + vec3(-1.0);
    vec3 materialProperties = texture(gMaterial, vTexcoord).rgb;
    vec3 fPos = vec3(gl_FragCoord.xy / vec2(textureSize(gDepth, 0)), texture(gDepth, vTexcoord).r);

    fClr = CalcLighting(fPos,
                        normal,
                        color,
                        materialProperties);

    // fClr.rgb = color * normal * depth;
    fClr.a = 1.0;
}