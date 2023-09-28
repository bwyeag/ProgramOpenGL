#ifndef OPENGL_INIT_H
#define OPENGL_INIT_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "type_load.hpp"
#include "Error.hpp"

#define SCREEN_SIZE_WIDTH 800
#define SCREEN_SIZE_HEIGHT 600
#define WINDOW_NAME "LearnOpenGL"
namespace Engine::Utility
{
    extern bool firstMouse;

    extern unsigned int SCR_WIDTH;
    extern unsigned int SCR_HEIGHT;

    extern double current_time;
    extern double delta_time;
    extern double last_time;

    extern double last_mouse_x;
    extern double last_mouse_y;

    extern GLFWwindow* windowptr;

    void framebuffer_size_callback(GLFWwindow* windowptr, int width, int height);
    void processInput(GLFWwindow* windowptr);
    void mouse_callback(GLFWwindow* windowptr, double xposIn, double yposIn);
    void opengl_display();
    bool opengl_init();

    extern vector<GLFWframebuffersizefun> callback_framebuffersize;
    extern vector<GLFWframebuffersizefun> callback_framebuffersize;
    extern vector<GLFWframebuffersizefun> callback_framebuffersize;
    extern vector<GLFWerrorfun> vector_errorfun;
    extern vector<GLFWwindowposfun> vector_windowposfun;
    extern vector<GLFWwindowsizefun> vector_windowsizefun;
    extern vector<GLFWwindowclosefun> vector_windowclosefun;
    extern vector<GLFWwindowrefreshfun> vector_windowrefreshfun;
    extern vector<GLFWwindowfocusfun> vector_windowfocusfun;
    extern vector<GLFWwindowiconifyfun> vector_windowiconifyfun;
    extern vector<GLFWwindowmaximizefun> vector_windowmaximizefun;
    extern vector<GLFWframebuffersizefun> vector_framebuffersizefun;
    extern vector<GLFWwindowcontentscalefun> vector_windowcontentscalefun;
    extern vector<GLFWmousebuttonfun> vector_mousebuttonfun;
    extern vector<GLFWcursorposfun> vector_cursorposfun;
    extern vector<GLFWcursorenterfun> vector_cursorenterfun;
    extern vector<GLFWscrollfun> vector_scrollfun;
    extern vector<GLFWkeyfun> vector_keyfun;
    extern vector<GLFWcharfun> vector_charfun;
    extern vector<GLFWcharmodsfun> vector_charmodsfun;
    extern vector<GLFWdropfun> vector_dropfun;
    extern vector<GLFWmonitorfun> vector_monitorfun;
    extern vector<GLFWjoystickfun> vector_joystickfun;

    void utility_errorfun(int error_code, const char* description);
    void utility_windowposfun(GLFWwindow* window, int xpos, int ypos);
    void utility_windowsizefun(GLFWwindow* window, int width, int height);
    void utility_windowclosefun(GLFWwindow* window);
    void utility_windowrefreshfun(GLFWwindow* window);
    void utility_windowfocusfun(GLFWwindow* window, int focused);
    void utility_windowiconifyfun(GLFWwindow* window, int iconified);
    void utility_windowmaximizefun(GLFWwindow* window, int maximized);
    void utility_framebuffersizefun(GLFWwindow* window, int width, int height);
    void utility_windowcontentscalefun(GLFWwindow* window, float xscale, float yscale);
    void utility_mousebuttonfun(GLFWwindow* window, int button, int action, int mods);
    void utility_cursorposfun(GLFWwindow* window, double xpos, double ypos);
    void utility_cursorenterfun(GLFWwindow* window, int entered);
    void utility_scrollfun(GLFWwindow* window, double xoffset, double yoffset);
    void utility_keyfun(GLFWwindow* window, int key, int scancode, int action, int mods);
    void utility_charfun(GLFWwindow* window, unsigned int codepoint);
    void utility_charmodsfun(GLFWwindow* window, unsigned int codepoint, int mods);
    void utility_dropfun(GLFWwindow* window, int path_count, const char* paths[]);
    void utility_monitorfun(GLFWmonitor* monitor, int event);
    void utility_joystickfun(int jid, int event);

    inline void AddErrorCallback(GLFWerrorfun callback)
    {
        vector_errorfun.push_back(callback);
    }
    inline void AddMonitorCallback(GLFWmonitorfun callback)
    {
        vector_monitorfun.push_back(callback);
    }
    inline void AddWindowPosCallback(GLFWwindowposfun callback)
    {
        vector_windowposfun.push_back(callback);
    }
    inline void AddWindowSizeCallback(GLFWwindowsizefun callback)
    {
        vector_windowsizefun.push_back(callback);
    }
    inline void AddWindowCloseCallback(GLFWwindowclosefun callback)
    {
        vector_windowclosefun.push_back(callback);
    }
    inline void AddWindowRefreshCallback(GLFWwindowrefreshfun callback)
    {
        vector_windowrefreshfun.push_back(callback);
    }
    inline void AddWindowFocusCallback(GLFWwindowfocusfun callback)
    {
        vector_windowfocusfun.push_back(callback);
    }
    inline void AddWindowIconifyCallback(GLFWwindowiconifyfun callback)
    {
        vector_windowiconifyfun.push_back(callback);
    }
    inline void AddWindowMaximizeCallback(GLFWwindowmaximizefun callback)
    {
        vector_windowmaximizefun.push_back(callback);
    }
    inline void AddFramebufferSizeCallback(GLFWframebuffersizefun callback)
    {
        vector_framebuffersizefun.push_back(callback);
    }
    inline void AddWindowContentScaleCallback(GLFWwindowcontentscalefun callback)
    {
        vector_windowcontentscalefun.push_back(callback);
    }
    inline void AddKeyCallback(GLFWkeyfun callback)
    {
        vector_keyfun.push_back(callback);
    }
    inline void AddCharCallback(GLFWcharfun callback)
    {
        vector_charfun.push_back(callback);
    }
    inline void AddCharModsCallback(GLFWcharmodsfun callback)
    {
        vector_charmodsfun.push_back(callback);
    }
    inline void AddMouseButtonCallback(GLFWmousebuttonfun callback)
    {
        vector_mousebuttonfun.push_back(callback);
    }
    inline void AddCursorPosCallback(GLFWcursorposfun callback)
    {
        vector_cursorposfun.push_back(callback);
    }
    inline void AddCursorEnterCallback(GLFWcursorenterfun callback)
    {
        vector_cursorenterfun.push_back(callback);
    }
    inline void AddScrollCallback(GLFWscrollfun callback)
    {
        vector_scrollfun.push_back(callback);
    }
    inline void AddDropCallback(GLFWdropfun callback)
    {
        vector_dropfun.push_back(callback);
    }
    inline void AddJoystickCallback(GLFWjoystickfun callback)
    {
        vector_joystickfun.push_back(callback);
    }

    extern const char* string_BUFFER;
    extern const char* string_SHADER;
    extern const char* string_PROGRAM;
    extern const char* string_VERTEX_ARRAY;
    extern const char* string_QUERY;
    extern const char* string_PROGRAM_PIPELINE;
    extern const char* string_TRANSFORM_FEEDBACK;
    extern const char* string_SAMPLER;
    extern const char* string_TEXTURE;
    extern const char* string_RENDERBUFFER;
    extern const char* string_FRAMEBUFFER;
    extern const char* string_null;
    const char* GetObjectType(GLenum o);
    extern const char* string_DEBUG_SOURCE_API;
    extern const char* string_DEBUG_SOURCE_WINDOW_SYSTEM;
    extern const char* string_DEBUG_SOURCE_SHADER_COMPILER;
    extern const char* string_DEBUG_SOURCE_THIRD_PARTY;
    extern const char* string_DEBUG_SOURCE_APPLICATION;
    extern const char* string_DEBUG_SOURCE_OTHER;
    const char* GetSourceFrom(GLenum s);
    extern const char* string_GL_DEBUG_TYPE_ERROR;
    extern const char* string_GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR;
    extern const char* string_GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR;
    extern const char* string_GL_DEBUG_TYPE_PORTABILITY;
    extern const char* string_GL_DEBUG_TYPE_PERFORMANCE;
    extern const char* string_GL_DEBUG_TYPE_MARKER;
    extern const char* string_GL_DEBUG_TYPE_PUSH_GROUP;
    extern const char* string_GL_DEBUG_TYPE_POP_GROUP;
    extern const char* string_GL_DEBUG_TYPE_OTHER;
    const char* GetSourceType(GLenum s);
    extern const char* string_GL_DEBUG_SEVERITY_HIGH;
    extern const char* string_GL_DEBUG_SEVERITY_MEDIUM;
    extern const char* string_GL_DEBUG_SEVERITY_LOW;
    extern const char* string_GL_DEBUG_SEVERITY_NOTIFICATION;
    const char* GetSeverity(GLenum s);
    void glError_callback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
}

#endif //!OPENGL_INIT_H