#ifndef APP_HPP_
#define APP_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// #define IMGUI_USER_CONFIG "my_imgui_config.h"
#include <imgui.h>
// #include <implot.h>
#include <map>
#include <string>

/// Macro to disable console on Windows
// #if defined(_WIN32) && defined(APP_NO_CONSOLE)
//     #pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
// #endif

// Barebones Application Framework
class App
{
  public:
    // Constructor.
    App(std::string title, int w, int h, int argc, char const *argv[]);
    // Destructor.
    virtual ~App();
    // Called at top of run
    virtual void Start() {}
    // Update, called once per frame.
    virtual void Update() { /*implement me*/ }
    // Runs the app.
    void Run();
    // Get window size
    ImVec2 GetWindowSize() const;

    ImVec4 ClearColor;                     // background clear color
    GLFWwindow *Window;                    // GLFW window handle
    std::map<std::string, ImFont *> Fonts; // font map
    bool UsingDGPU;                        // using discrete gpu (laptops only)
};

#endif //! APP_HPP_
