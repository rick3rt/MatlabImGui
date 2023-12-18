#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <implot.h>
#include <map>
#include <string>

#include "FrameBuffer.h"

#define APP_SCALE 1.0f  // 2.0f
#define FONT_SCALE 1.0f // 3.0f

// Barebones Application Framework
class ImGuiApp
{
  public:
    // Constructor.
    ImGuiApp(std::string title, int w, int h, int argc, char const *argv[]);
    // Destructor.
    ~ImGuiApp();
    // Called at top of run
    virtual void Start() {}
    // Update, called once per frame.
    virtual void UpdateUI() {}
    virtual void UpdateGL() {}

    // Runs the app.
    void Run();

    // Set App font
    void setFont(std::string fname, float size);

    // Get window size
    ImVec2 GetWindowSize() const;

    bool isRunning() const { return m_Running; }
    void Stop() { m_Running = false; }

  private:
    FrameBuffer *m_FrameBuffer;
    ImVec2 m_openGLSize;
    // ImVec4 ClearColor;  // background clear color
    GLFWwindow *m_Window;   // GLFW window handle
    bool m_Running = false; // is app running
};
