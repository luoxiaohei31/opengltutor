#include "check_gl.hpp"
#include <iostream>
#include "Game.hpp"
#ifdef _WIN32
#include <windows.h>
#include <cstdlib>
#include <clocale>
#endif

#define OFF
#ifdef ON

int main() {
#ifdef _WIN32
    try {
        // this is to support Unicode in the console
        static UINT oldCCP = GetConsoleOutputCP();
        if (!SetConsoleOutputCP(CP_UTF8)) {
            std::cerr << "warning: failed to chcp 65001 for utf-8 output\n";
        } else {
            std::atexit(+[] { SetConsoleOutputCP(oldCCP); });
        }
        static UINT oldCP = GetConsoleCP();
        if (!SetConsoleCP(CP_UTF8)) {
            std::cerr << "warning: failed to chcp 65001 for utf-8 input\n";
        } else {
            std::atexit(+[] { SetConsoleCP(oldCP); });
        }
        // this is to support Unicode in path name (make Windows API regard char * as UTF-8 instead of GBK)
        // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/setlocale-wsetlocale
        std::setlocale(LC_ALL, ".UTF-8");
        // this is to support ANSI control characters (e.g. \033[0m)
        static HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hIn != INVALID_HANDLE_VALUE && hOut != INVALID_HANDLE_VALUE) {
            static DWORD oldOutMode = 0;
            static DWORD oldInMode = 0;
            GetConsoleMode(hOut, &oldOutMode);
            GetConsoleMode(hIn, &oldInMode);
            if (SetConsoleMode(hOut, oldOutMode | 0x000C)) {
                std::atexit(+[] { SetConsoleMode(hOut, oldOutMode); });
                if (SetConsoleMode(hIn, oldInMode | 0x0200)) {
                    std::atexit(+[] { SetConsoleMode(hIn, oldInMode); });
                }
            }
        }
    } catch (...) {
        std::cerr << "warning: failed to set utf-8 locale\n";
    }
#endif

    // Initalize GLFW library
    if (!glfwInit()) {
        const char *errmsg = nullptr;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "failed to initialize GLFW: " << errmsg << '\n';
        return -1;
    }

    // Hint the version required: OpenGL 2.0
    constexpr int version = 20;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version / 10);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version % 10);
    if (version >= 33) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    // enable 4x MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Enable transparent framebuffer
    constexpr bool transparent = false;
    if (transparent) {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    }

    // Create main window
    constexpr char title[] = "Example";
    GLFWwindow *window = glfwCreateWindow(1024, 768, title, NULL, NULL);

    // Test if window creation succeed
    if (!window) {
        check_gl::opengl_show_glfw_error_diagnose();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Switch to fullscreen mode
    constexpr bool fullscreen = false;
    if (fullscreen) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        if (monitor) {
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            if (mode) {
                glfwSetWindowSize(window, mode->width, mode->height);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
                std::cerr << "Entered fullscreen mode: " << mode->width << 'x' << mode->height
                    << " at " << mode->refreshRate << " Hz\n";
            }
        }
    } else {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        if (monitor) {
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            if (mode) {
                int width, height;
                glfwGetWindowSize(window, &width, &height);
                glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
            }
        }
    }

    // Load glXXX function pointers (only after this you may use OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        std::cerr << "GLAD failed to load GL functions\n";
        return -1;
    }
    check_gl::opengl_try_enable_debug_message();

    // Print diagnostic information
    std::cerr << "OpenGL version: " << (const char *)glGetString(GL_VERSION) << '\n';

    // Enable V-Sync
    glfwSwapInterval(1);

    // Create game instance
    auto &game = Game::get();
    game.set_window(window);

    // Initialize data structures
    game.initialize();
    // Start main game loop
    while (!glfwWindowShouldClose(window)) {
        // Render graphics
        game.render();
        // Update screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#endif  // ON

#ifdef OFF
#include"myHomeWork.hpp"

static void render() {
    HollowCircle hc1{};
    hc1.setColr(120.0f, 255.0f, 189.0f);
    hc1.x = 0.0f;
    hc1.y = 0.7f * sinf(3.1415f / 3.0f);
    hc1.inner_raduis = 0.15f;
    hc1.top_raduis = 0.3f;
    hc1.start_angle = -(1.0f / 6.0f);
    hc1.end_angle = (1.0f / 2.0f + 1.0f / 6.0f);
    hc1.paint();
    
    HollowCircle hc2 = hc1;
    hc2.setColr(255.0f, 193.0f, 120.0f);
    hc2.x = -0.35f;
    hc2.y = 0.0f;
    hc2.start_angle = 1.0f / 6.0f;
    hc2.end_angle = 1.0f;
    hc2.paint();

    HollowCircle hc3 = hc1;
    hc3.setColr(255.0f, 120.0f, 177.0f);
    hc3.x = 0.35f;
    hc3.y = 0.0f;
    hc3.start_angle = (1.0f / 4.0f + 1.0f / 12.0f);
    hc3.end_angle = 1.0f + 1.0f / 6.0f;
    hc3.paint();

}

int main() {
    if (!glfwInit()) {
        const char* errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "failed to initialize GLFW: " << errmsg << '\n';
        return -1;
    }

    // hint the version required: OpenGL 2.0
    constexpr int version = 20;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_VERSION_MAJOR, version / 10);
    glfwWindowHint(GLFW_VERSION_MINOR, version % 10);
    if (version >= 33)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(640, 640, "主窗口", nullptr, nullptr);
    if (!window) {
        const char* errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "GLFW failed to create window" << errmsg << '\n';
        std::cerr << "============================================\n";
        if (!strcmp(errmsg, "X11: The DISPLAY environment variable is missing")) {
            std::cerr << "You seems not running with graphic display\n";
        }
        else if (!strcmp(errmsg, "WGL: The driver does not appear to support OpenGL")) {
            std::cerr << "Please consider install an OpenGL driver,or use mesa driver\n";
        }
        else if (!strcmp(errmsg, "WGL: Failed to create OpenGL context")) {
            std::cerr << "Your driver seems not supporting the required OpenGL version\n";
        }
        std::cerr << "- If you have a physical graphic card (e.g. NVIDIA), install it from your graphic card vendor official website: http://www.nvidia.com/Download/index.aspx\n";
        std::cerr << "- If you are using Windows, download opengl32.dll from https://pan.baidu.com/s/1TZ6nVJC7DZIuUarZrGJYow?pwd=opgl and place it into the same directory as this executable file (alternatively you may download opengl32sw.dll from Internet and rename it to opengl32.dll to place into the same directory as this executable file)\n";
        std::cerr << "- If you are using Linux or WSL1, install the mesa driver: https://ubuntuhandbook.org/index.php/2021/07/install-latest-mesa-ubuntu-20-04-21-04/";
        std::cerr << "- If you use WSL2, install WSLg: https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/gui-apps\n";
        std::cerr << "- If you are using SSH remote server, try connect it using ssh -X <ip address>\n";
        std::cerr << "- If you are using MacOS, you probably want to use Windows or Linux instead for better OpenGL support\n";
        std::cerr << "- If you are using a Laptop with dual-cards, make sure you have switch to dedicated card (NVIDIA) instead of the integrated card (Intel)\n";
        std::cerr << "==============================================\n";
        system("pause");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowPos(window, 1920/2-width/2, 1080/2-height/2);

    // Load glXXX function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        std::cerr << "GLAD failed to load GL function\n";
        return -1;
    }
    std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

    CHECK_GL(glEnable(GL_POINT_SMOOTH));
    /*****************开启抗锯齿********************/
    CHECK_GL(glEnable(GL_BLEND));
    CHECK_GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    /*********************************************/
    //CHECK_GL(glPointSize(64.0f));

    // start main game loop
    while (!glfwWindowShouldClose(window)) {
        // render graphics
        CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));
        render();

        // refresh screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
#endif // !OFF

