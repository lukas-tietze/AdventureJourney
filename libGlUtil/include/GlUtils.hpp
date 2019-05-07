#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "GlmToStringConversions.hpp"
#include "Exception.hpp"

#include <string>

namespace glutil
{
struct CreateInfo
{
    std::string windowTitle;
};

extern const CreateInfo DefaultCreateInfo;

//Data Getters
int GetWindowWidth();
int GetWindowHeight();
float GetAspectRatio();
double GetMouseX();
double GetMouseY();
double GetMouseDeltaX();
double GetMouseDeltaY();
double GetScrollX();
double GetScrollY();
GLFWwindow *GetWindow();
bool HasWindow();

//Setters
void SetCustomTitle(const std::string &);
void SetCursorGameMode(bool);

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
bool QueryNextEvent(Event &out);
bool IsKeyDown(int key);
bool IsKeyUp(int key);
bool IsModifierDown(int modifier);
bool IsModifierUp(int modifier);
bool WasKeyPressed(int key);
bool WasKeyReleased(int key);
bool IsButtonDown(int button);
bool IsButtonUp(int button);
bool WasButtonPressed(int button);
bool WasButtonReleased(int button);
bool WasWindowResized();
bool WasMouseMoved();
bool WasScrolled();

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

class GlErrorException : public util::Exception
{
public:
    GlErrorException(GLenum error);
};

const std::string &GetGlErrorMessage(GLenum error);
void ThrowOnGlError();
void PrintGlError(const std::string &marker = "");
void PrintAllGlErrors(const std::string &marker = "");

extern const glm::vec3 AXIS_X;
extern const glm::vec3 AXIS_Y;
extern const glm::vec3 AXIS_Z;
extern const glm::vec3 ORIGIN;

enum class DrawMode : uint32_t
{
    CG2_POINTS = GL_POINTS,
    CG2_LINES = GL_LINES,
    CG2_LINE_LOOP = GL_LINE_LOOP,
    CG2_LINE_STRIP = GL_LINE_STRIP,
    CG2_TRIANGLES = GL_TRIANGLES,
    CG2_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    CG2_TRIANGLE_FAN = GL_TRIANGLE_FAN,
};

enum class DataType : uint32_t
{
    CG2_BYTE = GL_BYTE,
    CG2_UBYTE = GL_UNSIGNED_BYTE,
    CG2_SHORT = GL_SHORT,
    CG2_USHORT = GL_UNSIGNED_SHORT,
    CG2_INT = GL_INT,
    CG2_UINT = GL_UNSIGNED_INT,
    CG2_HALF_FLOAT = GL_HALF_FLOAT,
    CG2_FLOAT = GL_FLOAT,
    CG2_DOUBLE = GL_DOUBLE,
    CG2_INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
    CG2_UINT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
};

template <unsigned int NUM_BUFFS = 16>
class GlWatch
{
    GLuint query[NUM_BUFFS];
    GLint64 cpu_time[NUM_BUFFS];
    GLuint next;

public:
    GlWatch();
    ~GlWatch();

    void take();
    double get_gpu_time_in_ms();
    double get_cpu_time_in_ms();
};
} // namespace glutil

#include "libGlUtil/src/GlUtils/GlWatch.inl"