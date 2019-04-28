#version 430 core

layout(location = 4) uniform vec3 cam_pos_ws;

// Input varying
in vec4 vclr;

in vec3 vnrm_ws;
in vec3 vpos_ws;

// Output fragment color
out vec4 fclr;

struct LightData{
	vec4 position_ws;
	vec4 color;
	vec4 speed; // This can be ignored !!!
};

// std140 definiert das padding-Verhalten,  binding = 0 : Das 0te UBO
layout(std140, binding = 0)
uniform globalLightDataBlock
{
    LightData lights[8];
} globalLights;

void main()
{
    const int count = 8;
    float nDotL, a, nDotH; 
    vec3 light_color = vec3(0);
    vec4 lPos;
    vec3 lCol;

	for(int i = 0; i < count; i++)
    {
        lPos = globalLights.lights[i].position_ws;
        lCol = globalLights.lights[i].color.rgb;

        nDotL = dot(vec4(vnrm_ws, 1.f), lPos);

        if(nDotL > 0)
        {
            a = 1 / (1 + pow(distance(vpos_ws, lPos.xyz), 2));
            light_color += nDotL * lCol * vclr.rgb * a;

            nDotH = dot(vnrm_ws, (lPos.xyz + vpos_ws) / length(lPos.xyz + vpos_ws));

            if(nDotH > 0)
                light_color += lCol * pow(nDotH, 64);
        }
    }

	fclr.rgb = light_color.rgb;
	fclr.a = 1.0;
}
