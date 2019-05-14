#version 430 core

in vec2 vTex;

layout(location = 0) uniform sampler2D color;

out vec4 fClr;

const float offsetX = 1.0 / 300.0;  
const float offsetY = 1.0 / 300.0;  

vec2 offsets[9] = vec2[](
    vec2(-offsetX,  offsetY), // top-left
    vec2( 0.0f,     offsetY), // top-center
    vec2( offsetX,  offsetY), // top-right
    vec2(-offsetX,  0.0f),   // center-left
    vec2( 0.0f,     0.0f),   // center-center
    vec2( offsetX,  0.0f),   // center-right
    vec2(-offsetX, -offsetY), // bottom-left
    vec2( 0.0f,    -offsetY), // bottom-center
    vec2( offsetX, -offsetY)  // bottom-right    
);

const float kernel[9] = float[]
(
    -1, -1, -1, 
    -1,  9, -1,
    -1, -1, -1
);

void main()
{
    vec4 res = vec4(0.0);

    for(int i = 0; i < 9; i++)
        res += kernel[i] * texture(color, vTex + offsets[i]);

    fClr = res;
}