#include "ImGuiApp.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
// #include <iostream>
// #include <stdio.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

/// Macro to request high performance GPU in systems (usually laptops) with both
/// dedicated and discrete GPUs
#if defined(_WIN32)
extern "C" __declspec(dllexport) unsigned long NvOptimusEnablement = 0;
extern "C" __declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0;
#endif

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

ImGuiApp::ImGuiApp(std::string title, int w, int h, int argc, char const *argv[])
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) abort();

    // GL 3.0 + GLSL 330
    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only

    // Create window with graphics context
    m_Window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (!m_Window)
    {
        fprintf(stderr, "Failed to initialize GLFW window!\n");
        glfwTerminate();
        abort();
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_Window, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(m_Window);
    // glewExperimental = GL_TRUE;

    // init glew
    if (GLEW_OK != glewInit()) { abort(); }
    while (GLFW_NO_ERROR != glfwGetError(NULL)) {
    } /* glewInit may cause some OpenGL errors -- flush the error state */

    // Print version on console to see that everything initialized correctly
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
    std::cout << "GLEW Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1); // Enable vsync
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // create FrameBuffer
    glViewport(0, 0, bufferWidth, bufferHeight);
    m_FrameBuffer = new FrameBuffer(bufferWidth, bufferHeight);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable docking
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImPlot::StyleColorsDark();
    // ImGui::StyleColorsLight();
    // ClearColor = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);

    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(APP_SCALE);
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // load fonts
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", FONT_SCALE * 12.0f);
}

ImGuiApp::~ImGuiApp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    if (m_FrameBuffer) { delete m_FrameBuffer; }

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void ImGuiApp::Run()
{
    m_Running = true;
    Start();

    // Main loop
    while (!glfwWindowShouldClose(m_Window))
    {
        // close glfw window
        if (!isRunning()) { glfwSetWindowShouldClose(m_Window, true); }

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        // clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(); // allow docking in main viewport

        UpdateUI(); // UI update loop of app

        // Set window size for opengl, but only on very first creation of gui,
        // otherwise opengl will error because too small size for render window
        // ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_Once);
        // bool opengl_active = ImGui::Begin("OpenGL");
        // if (opengl_active)
        // {
        //     m_openGLSize = ImGui::GetContentRegionAvail();
        //     m_FrameBuffer->RescaleFrameBuffer(m_openGLSize.x, m_openGLSize.y);
        //     glViewport(0, 0, m_openGLSize.x, m_openGLSize.y);

        //     ImVec2 pos = ImGui::GetCursorScreenPos();
        //     unsigned int texture_id = m_FrameBuffer->getFrameTexture();
        //     ImGui::GetWindowDrawList()->AddImage((void *)texture_id, ImVec2(pos.x, pos.y),
        //                                          ImVec2(pos.x + m_openGLSize.x, pos.y +
        //                                          m_openGLSize.y), ImVec2(0, 1), ImVec2(1, 0));
        // }
        // ImGui::End();

        ImGui::Render(); // Rendering ImGui before openGL render calls

        // render framebuffer
        // if (opengl_active)
        // {
        //     m_FrameBuffer->Bind();
        //     UpdateGL(); // opengl update loop of app
        //     m_FrameBuffer->Unbind();
        // }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_Window);
    }
}

ImVec2 ImGuiApp::GetWindowSize() const
{
    int w, h;
    glfwGetWindowSize(m_Window, &w, &h);
    return ImVec2(w, h);
}

void ImGuiApp::setFont(std::string fname, float size)
{
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(fname.c_str(), size);
}