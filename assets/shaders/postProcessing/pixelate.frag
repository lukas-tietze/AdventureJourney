#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;

out vec4 fClr;

layout(std140, binding = 0) uniform screenDataBlock
{
    int width;
    int height;
} screenData;

const int PIXELATION = 5;

void main()
{
    vec2 size = vec2(screenData.width, screenData.height);
    vec2 tex = vTex * size;
    tex = tex - mod(tex, PIXELATION);

    fClr = texture(color, tex / size);
}