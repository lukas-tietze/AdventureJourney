#version 430 core

layout (location = 0) out vec3 gClr;
layout (location = 1) out vec3 gNrm;
layout (location = 2) out vec4 gMat;

in vec3 vNrm;
in vec2 vTex;
in vec4 vClr;

// vec3 GetNormal();
// vec4 GetColor();
// vec3 GetMaterialProperties();

void main()
{
    // gNrm = GetNormal();
    // gClr = GetColor();
    // gMat = GetMaterialProperties();

    gClr = vClr;
    gNrm = vNrm;
    gMat = vec4(0.0);
}