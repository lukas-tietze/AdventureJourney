#version 430 core
invariant gl_Position;

vec4 TransfromPositionCs();
void TransfromVaryings();

void main()
{
    gl_Position = TransfromPositionCs();
    TransfromVaryings();
}
