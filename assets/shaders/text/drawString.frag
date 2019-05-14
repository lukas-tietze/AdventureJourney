#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D sprite; 

out vec4 fClr;

void main()
{
    fClr = texture(sprite, vTex);
}