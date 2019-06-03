#version 430 core

in vec3 vTex;

layout(binding = 4) uniform samplerCube skybox;

vec4 GetAlbedo()
{
   return texture(skybox, vTex);
}

