#version 430 core

in vec2 vTexcoord;
layout(binding = 0) uniform sampler2D albedoMap;

vec4 GetAlbedo()
{
    return texture(albedoMap, vTexcoord);
}

