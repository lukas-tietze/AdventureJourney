#version 430 core
// Attributes
layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 clr;
// Uniforms
layout(location = 0) uniform mat4 MVP;

// Output varyings
out vec4 vclr;

void main()
{
	gl_Position = MVP * pos;

	vclr = vec4(clr.r / 255.0,
                clr.g / 255.0,
                clr.b / 255.0,
                clr.a / 255.0);

    // vclr = vec4(0.3f, 0.4f, 0.f, 1.f);
}
