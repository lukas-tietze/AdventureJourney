#version 430 core

layout(std140,binding = 1) uniform cameraDataBlock
{
        mat4 view;
        mat4 invVview;
        mat4 projection;
        mat4 invProjection;
} camera;

layout(location = 0) in vec3 pos;

out vec3 vTex;

void TransfromVaryings()
{
    vTex = pos;
}

vec4 TransfromPositionCs()
{
    mat4 view = mat4(mat3(camera.view));
    vec4 res = camera.projection * view * vec4(pos, 1.0);
    return res.xyww;
}
