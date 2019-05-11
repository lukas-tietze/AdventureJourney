#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nrm;
layout(location = 2) in vec3 clr;
layout(location = 3) in vec2 tex;

layout(std140, binding = 2) uniform objectDataBlock
{
    mat4 model;
    mat3 normal;
} object;

layout(std140, binding = 1) uniform cameraDataBlock
{
    mat4 view;
    mat4 invView;
    mat4 projection;
    mat4 invProjection;
} camera;

out vec4 vclr;
out vec2 vtex;

void main()
{
	gl_Position = camera.projection * camera.view * object.model * vec4(pos, 1.0);

    vtex = tex;

    // vclr.rgb = vec3(tex, 0.0);
    vclr.rgb = clr;
    vclr.a = 1.0;
}
