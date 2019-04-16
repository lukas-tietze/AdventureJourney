#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <string>

namespace glutil
{
struct CreateInfo
{
    std::string windowTitle;
};

extern const CreateInfo DefaultCreateInfo;

//Data
int GetWindowWidth();
int GetWindowHeight();
GLFWwindow *GetWindow();
bool HasWindow();
void SetCustomTitle(const std::string &);

//Lifecycle
bool Init(CreateInfo = DefaultCreateInfo);
void Loop();
void Quit();
bool DestroyGlContext();
void UpdateTitle();

//Handlers
void HandleResize(GLFWwindow *win, int w, int h);
void HandleScroll(GLFWwindow *win, double xoffset, double yoffset);
void HandleKeyboard(GLFWwindow *win, int key, int scancode, int action, int mods);
void HandleMouseButton(GLFWwindow *win, int button, int action, int mods);
void HandleCursor(GLFWwindow *win, double x, double y);

template <unsigned int NUM_BUFFS = 16>
class GlWatch
{
    GLuint query[NUM_BUFFS];
    GLint64 cpu_time[NUM_BUFFS];
    GLuint next;

  public:
    GlWatch()
    {
        next = 0;
        glGenQueries(NUM_BUFFS, query);
        for (unsigned int i = 0; i < NUM_BUFFS; i++)
            cpu_time[i] = 0;
    }
    ~GlWatch()
    {
        glDeleteQueries(NUM_BUFFS, query);
        for (unsigned int i = 0; i < NUM_BUFFS; i++)
            query[i] = 0;
    }

    void take()
    {
        glQueryCounter(query[next], GL_TIMESTAMP);
        glGetInteger64v(GL_TIMESTAMP, cpu_time + next);
        next = (next + 1) % NUM_BUFFS;
    }

    /**
	 * @brief get_time_in_ms will query and return the oldest gpu timestamp!
	 * @return time in ms
	 */
    double get_gpu_time_in_ms()
    {
        GLuint64 time_ns = 0;
        glGetQueryObjectui64v(query[(next) % NUM_BUFFS], GL_QUERY_RESULT, &time_ns);
        return static_cast<double>(time_ns) / 1000000.0;
    }

    /**
	 * @brief get_time_in_ms will return the oldest cpu timestamp!
	 * @return time in ms
	 */
    double get_cpu_time_in_ms()
    {
        return static_cast<double>(cpu_time[next]) / 1000000.0;
    }
};
} // namespace glutil