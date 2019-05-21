#version 430 core

invariant gl_Position;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nrm;
layout(location = 2) in vec4 clr;
layout(location = 3) in vec4 tex;

out vec3 vPosWs;
out vec3 vNrmWs;

void TransformUniforms();
vec4 TransformToClipSpace();

void main()
{
    TransformUniforms();

    gl_Position = TransformToClipSpace();
}