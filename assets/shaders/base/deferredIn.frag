#version 430 core

layout (location = 0) out vec3 fPosWs;
layout (location = 1) out vec3 fNrmWs;
layout (location = 2) out vec4 fClr;

in vec3 vPos;
in vec3 vNrm;

vec4 CalcColor();

void main()
{
    fPos = vPos;
    fNrm = vNrm;
    cFlr = CalcColor();
}