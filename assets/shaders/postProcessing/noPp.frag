#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;

out vec4 clr;

void main()
{
    clr = texture(color, vTex);
}