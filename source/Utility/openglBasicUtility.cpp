#include "openglUtility.hpp"

namespace Engine::Utility
{
    //窗口大小
    unsigned int SCR_WIDTH = SCREEN_SIZE_WIDTH;
    unsigned int SCR_HEIGHT = SCREEN_SIZE_HEIGHT;

    //时间处理
    double delta_time = 0.0;
    double current_time = 0.0;
    double last_time = 0.0;

    //鼠标信息追踪
    double last_mouse_x = SCR_WIDTH / 2.0;
    double last_mouse_y = SCR_HEIGHT / 2.0;
    bool firstMouse = true;

    GLFWwindow* windowptr = nullptr;
    void processInput(GLFWwindow* windowptr)
    {
        if (glfwGetKey(windowptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(windowptr, true);

    }

    void framebuffer_size_callback(GLFWwindow* windowptr, int width, int height)
    {
        SCR_HEIGHT = height;
        SCR_WIDTH  = width;
        glViewport(0, 0, width, height);
    }

    void mouse_callback(GLFWwindow* windowptr, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            last_mouse_x = xpos;
            last_mouse_y = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - last_mouse_x;
        float yoffset = last_mouse_y - ypos;
        last_mouse_x = xpos;
        last_mouse_y = ypos;
    }

    /// @brief BasicUtility名称空间每帧事务
    void opengl_display()
    {
        //Part1: 计算每帧时间
        current_time = glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
        //Part2: 处理输入
        processInput(windowptr);
    }

    /// @brief 初始化OpenGL函数
    /// @return 初始化是否成功
    bool opengl_init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        windowptr = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME, NULL, NULL);
        if (windowptr == NULL)
        {
            ERROR("GLFW","创建窗口失败")
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(windowptr);
        //设置回调函数
        {
            glfwSetErrorCallback(utility_errorfun);
            glfwSetMonitorCallback(utility_monitorfun);
            glfwSetWindowPosCallback(windowptr, utility_windowposfun);
            glfwSetWindowSizeCallback(windowptr, utility_windowsizefun);
            glfwSetWindowCloseCallback(windowptr, utility_windowclosefun);
            glfwSetWindowRefreshCallback(windowptr, utility_windowrefreshfun);
            glfwSetWindowFocusCallback(windowptr, utility_windowfocusfun);
            glfwSetWindowIconifyCallback(windowptr, utility_windowiconifyfun);
            glfwSetWindowMaximizeCallback(windowptr, utility_windowmaximizefun);
            glfwSetFramebufferSizeCallback(windowptr, utility_framebuffersizefun);
            glfwSetWindowContentScaleCallback(windowptr, utility_windowcontentscalefun);
            glfwSetKeyCallback(windowptr, utility_keyfun);
            glfwSetCharCallback(windowptr, utility_charfun);
            glfwSetCharModsCallback(windowptr, utility_charmodsfun);
            glfwSetMouseButtonCallback(windowptr, utility_mousebuttonfun);
            glfwSetCursorPosCallback(windowptr, utility_cursorposfun);
            glfwSetCursorEnterCallback(windowptr, utility_cursorenterfun);
            glfwSetScrollCallback(windowptr, utility_scrollfun);
            glfwSetDropCallback(windowptr, utility_dropfun);
            glfwSetJoystickCallback(utility_joystickfun);
        }
        //添加回调函数
        AddFramebufferSizeCallback(framebuffer_size_callback);
        AddCursorPosCallback(mouse_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            ERROR("GLAD","创建失败")
            glfwTerminate();
            return false;
        }
#ifdef _DEBUG
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if ((flags & GL_CONTEXT_FLAG_DEBUG_BIT) == GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glError_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            INFO("OpenGL","启用调试上下文成功")
        }
        else
        {
            INFO("OpenGL","启用调试上下文失败")
        }
#endif
        return true;
    }
}
