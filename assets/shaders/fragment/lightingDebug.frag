#version 430 core

in vec3 vPositionWs;
const float CG2PI = 3.14159265359;

layout(std140, binding = 1) uniform cameraDataBlock
{
        mat4 viewMat;
        mat4 invViewMat;
        mat4 projectionMat;
        mat4 invProjectionMat;

} camera;

struct Light
{
    vec4 position_type;
    vec4 color_ambientFactor;
    vec4 spotDir_cutOff;
    vec4 spotExponent_size_enabled; // z  unused!
    mat4 worldSpaceToShadowMap;
};

layout(std140, binding = 4) uniform globalLightDataBlock
{
    Light lights[4];
} global;

#define LPos(i) (global.lights[i].position_type.xyz)
#define LIsDir(i) (global.lights[i].position_type.w == 0)
#define LColor(i) (global.lights[i].color_ambientFactor.rgb)
#define LAmbient(i) (global.lights[i].color_ambientFactor.a)
#define LEnabled(i) (global.lights[i].spotExponent_size_enabled.w != 0)
#define LSpotDir(i) (global.lights[i].spotDir_cutOff.xyz)
#define LSpotCutoff(i) (global.lights[i].spotDir_cutOff.w)
#define LSpotExponent(i) (global.lights[i].spotExponent_size_enabled.x)
#define Lsize(i) (global.lights[i].spotExponent_size_enabled.y)

vec3 CalcLighting(in vec3 albedo, in vec4 materialProps, in vec3 normal)
{
    if(normal.x < 0 || normal.y < 0 || normal.z < 0)
        return normal * -1.0;
    
    return normal;
}
