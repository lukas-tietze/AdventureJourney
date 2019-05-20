#version 430 core

invariant gl_Position;

in vec3 pos;
in vec2 tex;

out vec2 vTex;

void main()
{
    gl_Position = pos;
    vTex = tex;
}