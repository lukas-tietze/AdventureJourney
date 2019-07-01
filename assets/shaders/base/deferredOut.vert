#version 430 core

invariant gl_Position;

in vec2 pos;

out vec2 vTexcoord;

void main()
{
    gl_Position = vec4(pos, 1.0, 1.0);
    vTexcoord = pos * vec2(0.5) + vec2(0.5);
}