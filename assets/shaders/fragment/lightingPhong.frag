#version 430 core

in vec3 vPositionWs;
const float CG2PI = 3.14159265359;

layout(std140, binding = 1) uniform cameraDataBlock
{
        mat4 view;
        mat4 invViewMat;
        mat4 projectionMat;
        mat4 invProjectionMat;

} camera;

struct Light
{
    vec3 position;
    int type;
    vec3 color;
    float ambientFactor;
    int active;
};

layout(std140, binding = 4) uniform globalLightDataBlock
{
    Light lights[8];
#define Lpos(i) global.lights[i].position.xyz
#define Lis_dir(i) (global.lights[i].position.w == 0)
#define Lcolor(i) global.lights[i].color_AND_ambi.xyz
#define Lspot_dir(i) global.lights[i].spot_dir_AND_cut_off.xyz

#define Lambient(i) global.lights[i].color_AND_ambi.w
#define Lspot_cutoff(i) global.lights[i].spot_dir_AND_cut_off.w
#define Lspot_exponent(i) global.lights[i].spot_exponent_AND_size_AND_enabled.x
#define Lsize(i) global.lights[i].spot_exponent_AND_size_AND_enabled.y
#define Lenabled(i) (global.lights[i].spot_exponent_AND_size_AND_enabled.w > 0.5)
} global;

vec3 CalcOneLight(in int id, in vec3 normal, in vec3 fpos, in vec3 albedo, in vec2 mp)
{
    vec3 V = normalize(Lis_dir(i) ? camera.view[3].xyz - fpos : Lpos(i));
    vec3 L = Lpos(i);
    vec3 H = normalize(V + L);
    float atten = Lis_dir(i) ? 1.0 : 1.0 / (1 + d * d);
    float NdotL = clamp(dot(N, L), 0.0, 1.0);
    vec3 diff = Lcolor(i) * NdotL;
    vec3 spec = vec3(0);

    if(NdotL > 0.0)
        spec = Lcolor(i) * clamp(pow(dot(N, H), 8.0), 0, 1) * 0.2;

    vec3 ambi = Lcolor(i) * Lambient(i);
    lightColor += atten * diff + ambi;
    lightColorSpec += atten * spec;
    
    fclr.rgb = albedo.rgb * lightColor + lightColorSpec;
    fclr.rgb = pow(fclr.rgb,vec3(1.0/2));
	fclr.a = 1.0;
}

vec3 calcLighting(in vec3 albedo, in vec4 materialProps, in vec3 normal)
{
    vec3 res = vec3(0);

    for(int i = 0; i < 8; i++) 
    {
        if(Lenabled(i))
            res += CalcOneLight(i, normal, vPositionWs, albedo, materialProps.xy);
    }

    return res;
}
