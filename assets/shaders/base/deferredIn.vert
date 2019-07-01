#version 430 core

invariant gl_Position;

layout(std140, binding = 1) uniform cameraDataBlock
{
        mat4 viewMat;
        mat4 invViewMat;
        mat4 projectionMat;
        mat4 invProjectionMat;

} camera;

layout(std140, binding = 2) uniform objectDataBlock
{
        mat4 modelMat;
        mat4 normalMat;

} object;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texcoord;

out vec3 vNormalWs;
out vec2 vTexcoord;
out vec4 vColor;

void main()
{
    vNormalWs = (object.normalMat * vec4(normal, 0.0)).xyz;
    vTexcoord = texcoord;
    vColor = color;
    
    gl_Position = camera.projectionMat * camera.viewMat * object.modelMat * vec4(pos, 1.0);
}