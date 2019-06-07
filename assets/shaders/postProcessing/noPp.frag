#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;

out vec4 fclr;

void main()
{
    fclr = texture(color, vTex);
    // fclr = vec4(vTex, 0.0, 1.0);
}