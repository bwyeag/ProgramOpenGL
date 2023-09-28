#include "openglUtility.hpp"

namespace Engine::Utility
{
    vector<GLFWframebuffersizefun> callback_framebuffersize;
    vector<GLFWerrorfun> vector_errorfun;
    vector<GLFWwindowposfun> vector_windowposfun;
    vector<GLFWwindowsizefun> vector_windowsizefun;
    vector<GLFWwindowclosefun> vector_windowclosefun;
    vector<GLFWwindowrefreshfun> vector_windowrefreshfun;
    vector<GLFWwindowfocusfun> vector_windowfocusfun;
    vector<GLFWwindowiconifyfun> vector_windowiconifyfun;
    vector<GLFWwindowmaximizefun> vector_windowmaximizefun;
    vector<GLFWframebuffersizefun> vector_framebuffersizefun;
    vector<GLFWwindowcontentscalefun> vector_windowcontentscalefun;
    vector<GLFWmousebuttonfun> vector_mousebuttonfun;
    vector<GLFWcursorposfun> vector_cursorposfun;
    vector<GLFWcursorenterfun> vector_cursorenterfun;
    vector<GLFWscrollfun> vector_scrollfun;
    vector<GLFWkeyfun> vector_keyfun;
    vector<GLFWcharfun> vector_charfun;
    vector<GLFWcharmodsfun> vector_charmodsfun;
    vector<GLFWdropfun> vector_dropfun;
    vector<GLFWmonitorfun> vector_monitorfun;
    vector<GLFWjoystickfun> vector_joystickfun;

    void utility_errorfun(int error_code, const char* description)
    {
        for (auto val : vector_errorfun)
        {
            val(error_code, description);
        }
    }

    void utility_windowposfun(GLFWwindow* window, int xpos, int ypos)
    {
        for (auto val : vector_windowposfun)
        {
            val(window, xpos, ypos);
        }
    }

    void utility_windowsizefun(GLFWwindow* window, int width, int height)
    {
        for (auto val : vector_windowsizefun)
        {
            val(window, width, height);
        }
    }

    void utility_windowclosefun(GLFWwindow* window)
    {
        for (auto val : vector_windowclosefun)
        {
            val(window);
        }
    }

    void utility_windowrefreshfun(GLFWwindow* window)
    {
        for (auto val : vector_windowrefreshfun)
        {
            val(window);
        }
    }

    void utility_windowfocusfun(GLFWwindow* window, int focused)
    {
        for (auto val : vector_windowfocusfun)
        {
            val(window, focused);
        }
    }

    void utility_windowiconifyfun(GLFWwindow* window, int iconified)
    {
        for (auto val : vector_windowiconifyfun)
        {
            val(window, iconified);
        }
    }

    void utility_windowmaximizefun(GLFWwindow* window, int maximized)
    {
        for (auto val : vector_windowmaximizefun)
        {
            val(window, maximized);
        }
    }

    void utility_framebuffersizefun(GLFWwindow* window, int width, int height)
    {
        for (auto val : vector_framebuffersizefun)
        {
            val(window, width, height);
        }
    }

    void utility_windowcontentscalefun(GLFWwindow* window, float xscale, float yscale)
    {
        for (auto val : vector_windowcontentscalefun)
        {
            val(window, xscale, yscale);
        }
    }

    void utility_mousebuttonfun(GLFWwindow* window, int button, int action, int mods)
    {
        for (auto val : vector_mousebuttonfun)
        {
            val(window, button, action, mods);
        }
    }

    void utility_cursorposfun(GLFWwindow* window, double xpos, double ypos)
    {
        for (auto val : vector_cursorposfun)
        {
            val(window, xpos, ypos);
        }
    }

    void utility_cursorenterfun(GLFWwindow* window, int entered)
    {
        for (auto val : vector_cursorenterfun)
        {
            val(window, entered);
        }
    }

    void utility_scrollfun(GLFWwindow* window, double xoffset, double yoffset)
    {
        for (auto val : vector_scrollfun)
        {
            val(window, xoffset, yoffset);
        }
    }

    void utility_keyfun(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        for (auto val : vector_keyfun)
        {
            val(window, key, scancode, action, mods);
        }
    }

    void utility_charfun(GLFWwindow* window, unsigned int codepoint)
    {
        for (auto val : vector_charfun)
        {
            val(window, codepoint);
        }
    }

    void utility_charmodsfun(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        for (auto val : vector_charmodsfun)
        {
            val(window, codepoint, mods);
        }
    }

    void utility_dropfun(GLFWwindow* window, int path_count, const char* paths[])
    {
        for (auto val : vector_dropfun)
        {
            val(window, path_count, paths);
        }
    }

    void utility_monitorfun(GLFWmonitor* monitor, int event)
    {
        for (auto val : vector_monitorfun)
        {
            val(monitor, event);
        }
    }

    void utility_joystickfun(int jid, int event)
    {
        for (auto val : vector_joystickfun)
        {
            val(jid, event);
        }
    }
}