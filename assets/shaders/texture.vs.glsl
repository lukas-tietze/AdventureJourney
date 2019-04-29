#version 430 core
// Attributes
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nrml;
layout(location = 4) in vec2 tex_coord;

layout(std140,binding = 1) uniform cameraDataBlock
{
	mat4 view;
	mat4 inv_view;
	mat4 projection;
	mat4 inv_projection;
	vec4 near_far_width_height;

} camera;

layout(std140,binding = 2) uniform objectDataBlock
{
	mat4 model;
	mat4 normal;

} object;

layout(binding = 0) uniform sampler2D grassTex;
layout(binding = 1) uniform sampler2D pebbleTex;
layout(binding = 2) uniform sampler2D distributionTex;

// Output varyings
out vec4 vclr;
out vec3 vnrm_ws;
out vec3 vpos_ws;

out vec2 vtex;

void main()
{
    float res = 0;
    const int sampleRange = 4;
    const float sampleStep = 0.05;

    for(int s = 0; s < sampleRange; s++)
    {
        for(int t = 0; t < sampleRange; t++)
        {
            vec2 offset = vec2((s - sampleRange / 2) * sampleStep, (t - sampleRange / 2) * sampleStep);
            res += texture(distributionTex, tex_coord + offset).b;
        }
    }

	vec3 pos_os = pos;
    pos_os.y += res / (sampleRange * sampleRange);

	gl_Position = camera.projection * camera.view * object.model * vec4(pos_os, 1.0);
	vnrm_ws = (object.normal * vec4(nrml, 0.0)).xyz;
	vpos_ws = (object.model * vec4(pos, 1.0)).xyz;
	vtex = tex_coord;
	vclr = vec4(1.0f);
}
