#version 430 core

layout(location = 0) in vec2 pos;

out vec2 vTex;

void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
    vTex = (pos + vec2(1.0, 1.0)) / 2.0;
}