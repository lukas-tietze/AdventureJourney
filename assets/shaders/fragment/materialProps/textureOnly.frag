#version 430 core

in vec2 v_texcoord;
layout(binding = 2) uniform sampler2D mp_map;

vec3 GetMaterialProps()
{
    return texture(mp_map, v_texcoord).rgb;
}

