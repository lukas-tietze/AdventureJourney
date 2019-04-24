#version 430 core
// Attributes
layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 nrml;
layout(location = 4) in vec4 tex;
// Output varyings
out vec4 vclr;

layout(std140, binding = 0) uniform objectDataBlock
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

void main()
{
	gl_Position = camera.projection * camera.view * object.model * vec4(pos, 1.0);

	// vclr = vec4(normalize(clr), 1.0);

    vclr = vec4(0.3f, 0.4f, 0.f, 1.f);
}
