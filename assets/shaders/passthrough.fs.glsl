#version 430 core

in vec4 vclr;
in vec2 vtex;

out vec4 fclr;

layout(location = 0) uniform sampler2D albedo;

void main()
{
	fclr = texture(albedo, vtex);
    // fclr = vec4(vtex, 0.0, 1.0);
}
 