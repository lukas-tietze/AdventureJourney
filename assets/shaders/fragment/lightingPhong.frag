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

vec3 CalcOneLight(in int i, in vec3 N, in vec3 fpos, in vec3 albedo, in vec2 mp)
{
    vec3 res = LColor(i) * LAmbient(i);
    vec3 L;
    float a;

    if(LIsDir(i))
    {
        L = LPos(i);
        a = 1.0;
    }
    else
    {
        L = normalize(LPos(i) - fpos);
        a = 1.0 / (1 + pow(length(LPos(i) - fpos), 2));
    }

    float NdotL = dot(N, L);
    
    if(NdotL > 0)
    {
        res += a * NdotL * LColor(i);

        vec3 viewDir = normalize(camera.invViewMat[3].xyz - fpos);
        vec3 reflectDir = reflect(-L, N);

        res += LColor(i) * a * pow(max(dot(viewDir, reflectDir), 0.0), 32);
    }

    return res * albedo;
}

vec3 CalcLighting(in vec3 albedo, in vec4 materialProps, in vec3 normal)
{
    vec3 res = vec3(0.0, 0.0, 0.0);

    for(int i = 0; i < 1; i++) 
        if(LEnabled(i))
            res += CalcOneLight(i, normal, vPositionWs, albedo, materialProps.xy);

    return res;
}
