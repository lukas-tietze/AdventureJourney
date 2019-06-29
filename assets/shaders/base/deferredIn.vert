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
layout(location = 1) in vec3 nrm;
layout(location = 2) in vec4 clr;
layout(location = 3) in vec2 tex;

out vec3 vNrm;
out vec2 vTex;
out vec4 vClr;

void main()
{
    vNrm = (object.normalMat * vec4(nrm, 0.0)).xyz;
    vTex = tex;
    vClr = clr;
    
    gl_Position = camera.projectionMat * camera.viewMat * object.modelMat * vec4(pos, 1.0);
}