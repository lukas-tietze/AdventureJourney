#version 430 core

in vec3 vNormalWs;

vec3 GetNormal()
{
    return normalize(vNormalWs);
}

