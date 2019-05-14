#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;
layout(location = 1) uniform sampler2D depth;

out vec4 clr;

void main()
{
    clr = vec4(0.3, 1.0, 0.3, 1.0);
}