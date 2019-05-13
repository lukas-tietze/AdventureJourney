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
    vec3 position;
    uint type;
    vec3 color;
    float ambientFactor;
    uint enabled;
};

layout(std140, binding = 4) uniform globalLightDataBlock
{
    Light lights[4];
} global;

// #define LPos(i) (global.lights[i].position.xyz)
// #define LIsDir(i) (global.lights[i].type == 0)
// #define LColor(i) (global.lights[i].color.xyz)
// #define LAmbient(i) (global.lights[i].ambientFactor)
// #define LEnabled(i) (global.lights[i].enabled != 0)

#define LPos(i) (vec3(0.0, 0.0, 0.0))
#define LIsDir(i) (false)
#define LColor(i) (vec3(0.3f, 0.7f, 0.9f))
#define LAmbient(i) (0.3)
#define LEnabled(i) (true)

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

        // vec3 viewDir = normalize(camera.viewMat[3].xyz - fpos);
        // vec3 reflectDir = reflect(-L, N);

        // res += LColor(i) * a * pow(max(dot(viewDir, reflectDir), 0.0), 32);
    }

    return res;
}

vec3 CalcLighting(in vec3 albedo, in vec4 materialProps, in vec3 normal)
{
    vec3 res = vec3(0.0, 0.0, 0.0);

    for(int i = 0; i < 4; i++) 
        if(LEnabled(i))
            res += CalcOneLight(i, normal, vPositionWs, albedo, materialProps.xy);

    return res;
}
