#version 430 core

invariant gl_Position;

layout(location = 0) in vec3 pos;
layout(location = 1) in int index;
layout(location = 2) in vec2 corner;

layout(std140, binding = 0) uniform fontDataBlock
{
    vec2 offset;
    vec2 charSize;
    vec2 stride;
    ivec2 colsAndLines;
} font;

out vec2 vTex;

int main()
{
    gl_Position = pos;

    vec2 charGridPos = vec2(font.colsAndLines.x % index,
                            font.colsAndLines.x / index);

    vTex = font.offset + charGridPos * font.stride + font.charSize * corner;
}