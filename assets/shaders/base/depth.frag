#version 430 core
// This is the no-operation shader used generate depth maps etc.

vec4 GetAlbedo();

void main(void)
{
    if(GetAlbedo().a < 0.5)
        discard;
}
