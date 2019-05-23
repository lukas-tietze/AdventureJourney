#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;

out vec4 fClr;

layout(std140, binding = 0) uniform screenDataBlock
{
    int width;
    int height;
} screenData;

vec2 offsets[9] = vec2[](
    vec2(-1.0, 1.0), // top-left
    vec2( 0.0, 1.0), // top-center
    vec2( 1.0, 1.0), // top-right
    vec2(-1.0, 0.0), // center-left
    vec2( 0.0, 0.0), // center-center
    vec2( 1.0, 0.0f),// center-right
    vec2(-1.0, -1.0),// bottom-left
    vec2( 0.0, -1.0),// bottom-center
    vec2( 1.0, -1.0) // bottom-right    
);

const float kernel[9] = float[]
(
    1.5, 1.5,  1.5, 
    1.5, -9, 1.5,
    1.5, 1.5,  1.5
);

void main()
{
    vec4 res = vec4(0.0);

    vec2 correction = vec2(1.0 / screenData.width, 1.0 / screenData.height);

    for(int i = 0; i < 9; i++)
        res += kernel[i] * texture(color, vTex + correction * offsets[i]);

    fClr = res;
}