#version 430 core

in vec2 vTexcoord;

layout(std140, binding = 1) uniform cameraDataBlock
{
    mat4 viewMat;
    mat4 invViewMat;
    mat4 projectionMat;
    mat4 invProjectionMat;

} camera;

layout(binding = 0) uniform sampler2D gColor;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gMaterial;
layout(binding = 3) uniform sampler2D gDepth;

out vec4 fClr;

vec3 CalcLighting(in vec3 pos, in vec3 normal, in vec3 albedo, in vec3 materialProperties);

void main()
{
    vec3 color = texture(gColor, vTexcoord).rgb;
    vec3 normal = texture(gNormal, vTexcoord).xyz * vec3(2.0) + vec3(-1.0);
    vec3 materialProperties = texture(gMaterial, vTexcoord).rgb;
    vec4 pos = camera.invViewMat * 
               camera.invProjectionMat * 
               vec4(gl_FragCoord.xy / vec2(textureSize(gDepth, 0)) * vec2(2.0) + vec2(1.0), texture(gDepth, vTexcoord).r, 1.0);
    vec3 fPos = pos.xyz / pos.w;

    fClr.rgb = CalcLighting(fPos,
                        normal,
                        color,
                        materialProperties);
    fClr.a = 1.0;
}