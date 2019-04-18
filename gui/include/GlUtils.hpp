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

//Events
enum class EventType
{
    Scroll,
    Key,
    MouseButton,
    MouseMove,
    WindowResize,
};

struct Event
{
    EventType type;
    bool handled;

    union {
        struct
        {
            int key;
            int mods;
            bool handled;
        } keyEvent;

        struct
        {
            int button;
        } mouseEvent;
    };
};

//States
bool HasNextEvent();
const Event &QueryNextEvent();
bool IsKeyDown(int key);
bool IsKeyUp(int key);
bool WasKeyPressed(int key);
bool WasKeyReleased(int key);
bool IsButtonDown(int button);
bool IsButtonUp(int button);
bool WasButtonPressed(int button);
bool WasButtonReleased(int button);

class Screen
{
  public:
    virtual ~Screen();
    virtual void Render();
    virtual void Update(double);

    virtual void OnShow();
    virtual void OnHide();

    void Show();
};

void RequestNextScreen(Screen *);
void RequestBlankScreen();

GLuint LoadShader(const std::string &path, GLenum type);
GLuint CreateProgram(GLuint vs, GLuint fs);
GLuint CreateProgram(const std::string &vsSrc, const std::string &fsSrc);
bool CheckShader(GLuint shader);
bool CheckProgram(GLuint prog);
GLenum HandleGlError();

extern const glm::vec3 AXIS_X;
extern const glm::vec3 AXIS_Y;
extern const glm::vec3 AXIS_Z;
extern const glm::vec3 ORIGIN;

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