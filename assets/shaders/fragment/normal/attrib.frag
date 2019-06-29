#version 430 core

in vec3 vNrm;

vec3 GetNormal()
{
    return normalize(vNormalWs);
}

