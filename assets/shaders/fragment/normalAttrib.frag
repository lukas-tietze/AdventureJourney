#version 430 core

in vec3 vPositionWs;
in vec3 vTangentWs;
in vec3 vBitangentWs;
in vec3 vNormalWs;
in vec2 vTexcoord;
in vec4 vColor;

vec3 GetNormal()
{
    return vNormalWs;
}

