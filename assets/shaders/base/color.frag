#version 430 core

layout(early_fragment_tests) in;
layout(location = 0) out vec4 fclr;

vec4 GetAlbedo();
vec4 GetMaterial_props();
vec3 GetNormal();
vec3 CalcLighting(in vec3 albedo,
                  in vec4 material_props,
                  in vec3 normal);

void main()
{
    vec4 albedo = GetAlbedo();

    fclr.rgb = CalcLighting(albedo.rgb,
               GetMaterialProps(),
               GetNormal());

    // transform back to 'gamma compressed' colors
     fclr.rgb = pow(fclr.rgb, vec3(1.0 / 2));
}
