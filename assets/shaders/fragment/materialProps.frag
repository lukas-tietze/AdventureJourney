#version 430 core

in vec2 v_texcoord;
layout(binding = 2) uniform sampler2D mp_map;

layout(std140,binding = 3) uniform materialDataBlock
{
    vec4 albedo;
    vec4 properties;
} material;

vec4 GetMaterialProps()
{
    return material.properties;
}

