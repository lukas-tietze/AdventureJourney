#include "GlUtils.hpp"

template <unsigned int NUM_BUFFS>
glutil::GlWatch<NUM_BUFFS>::GlWatch()
{
    next = 0;
    glGenQueries(NUM_BUFFS, query);
    for (unsigned int i = 0; i < NUM_BUFFS; i++)
        cpu_time[i] = 0;
}

template <unsigned int NUM_BUFFS>
glutil::GlWatch<NUM_BUFFS>::~GlWatch()
{
    glDeleteQueries(NUM_BUFFS, query);
    for (unsigned int i = 0; i < NUM_BUFFS; i++)
        query[i] = 0;
}

template <unsigned int NUM_BUFFS>
void glutil::GlWatch<NUM_BUFFS>::take()
{
    glQueryCounter(query[next], GL_TIMESTAMP);
    glGetInteger64v(GL_TIMESTAMP, cpu_time + next);
    next = (next + 1) % NUM_BUFFS;
}

template <unsigned int NUM_BUFFS>
double glutil::GlWatch<NUM_BUFFS>::get_gpu_time_in_ms()
{
    GLuint64 time_ns = 0;
    glGetQueryObjectui64v(query[(next) % NUM_BUFFS], GL_QUERY_RESULT, &time_ns);
    return static_cast<double>(time_ns) / 1000000.0;
}

template <unsigned int NUM_BUFFS>
double glutil::GlWatch<NUM_BUFFS>::get_cpu_time_in_ms()
{
    return static_cast<double>(cpu_time[next]) / 1000000.0;
}