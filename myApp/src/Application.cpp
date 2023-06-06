#include "Application.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#define USE_IMGUI 0

#include <iostream>
#include <stdio.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

/// Macro to request high performance GPU in systems (usually laptops) with both
/// dedicated and discrete GPUs
#if defined(_WIN32)
extern "C" __declspec(dllexport) unsigned long NvOptimusEnablement = 0;
extern "C" __declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0;
#endif

void StyeColorsApp()
{
    static const ImVec4 bg_dark = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);
    static const ImVec4 bg_mid = ImVec4(0.20f, 0.21f, 0.27f, 1.00f);
    static const ImVec4 accent_dark = ImVec4(0.292f, 0.360f, 0.594f, 1.000f);
    static const ImVec4 accent_light = ImVec4(0.409f, 0.510f, 0.835f, 1.000f);
    static const ImVec4 active = ImVec4(0.107f, 0.118f, 0.157f, 1.000f);
    static const ImVec4 attention = ImVec4(0.821f, 1.000f, 0.000f, 1.000f);

    auto &style = ImGui::GetStyle();
    style.WindowPadding = {6, 6};
    style.FramePadding = {6, 3};
    style.CellPadding = {6, 3};
    style.ItemSpacing = {6, 6};
    style.ItemInnerSpacing = {6, 6};
    style.ScrollbarSize = 16;
    style.GrabMinSize = 8;
    style.WindowBorderSize = style.ChildBorderSize = style.PopupBorderSize = style.TabBorderSize =
        0;
    style.FrameBorderSize = 1;
    style.WindowRounding = style.ChildRounding = style.PopupRounding = style.ScrollbarRounding =
        style.GrabRounding = style.TabRounding = 4;

    ImVec4 *colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.89f, 0.89f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
    colors[ImGuiCol_WindowBg] = bg_mid;
    colors[ImGuiCol_ChildBg] = ImVec4(0.20f, 0.21f, 0.27f, 0.00f);
    colors[ImGuiCol_PopupBg] = bg_mid;
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.06f);
    colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
    colors[ImGuiCol_FrameBgHovered] = accent_light;
    colors[ImGuiCol_FrameBgActive] = active;
    colors[ImGuiCol_TitleBg] = accent_dark;
    colors[ImGuiCol_TitleBgActive] = accent_dark;
    colors[ImGuiCol_TitleBgCollapsed] = accent_dark;
    colors[ImGuiCol_MenuBarBg] = accent_dark;
    colors[ImGuiCol_ScrollbarBg] = bg_mid;
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.89f, 0.89f, 0.93f, 0.27f);
    colors[ImGuiCol_ScrollbarGrabHovered] = accent_light;
    colors[ImGuiCol_ScrollbarGrabActive] = active;
    colors[ImGuiCol_CheckMark] = accent_dark;
    colors[ImGuiCol_SliderGrab] = accent_dark;
    colors[ImGuiCol_SliderGrabActive] = accent_light;
    colors[ImGuiCol_Button] = accent_dark;
    colors[ImGuiCol_ButtonHovered] = accent_light;
    colors[ImGuiCol_ButtonActive] = active;
    colors[ImGuiCol_Header] = accent_dark;
    colors[ImGuiCol_HeaderHovered] = accent_light;
    colors[ImGuiCol_HeaderActive] = active;
    colors[ImGuiCol_Separator] = accent_dark;
    colors[ImGuiCol_SeparatorHovered] = accent_light;
    colors[ImGuiCol_SeparatorActive] = active;
    colors[ImGuiCol_ResizeGrip] = accent_dark;
    colors[ImGuiCol_ResizeGripHovered] = accent_light;
    colors[ImGuiCol_ResizeGripActive] = active;
    colors[ImGuiCol_Tab] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
    colors[ImGuiCol_TabHovered] = accent_light;
    colors[ImGuiCol_TabActive] = accent_dark;
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = active;
    colors[ImGuiCol_PlotLines] = accent_light;
    colors[ImGuiCol_PlotLinesHovered] = active;
    colors[ImGuiCol_PlotHistogram] = accent_light;
    colors[ImGuiCol_PlotHistogramHovered] = active;
    colors[ImGuiCol_TableHeaderBg] = accent_dark;
    colors[ImGuiCol_TableBorderStrong] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
    colors[ImGuiCol_TextSelectedBg] = accent_light;
    colors[ImGuiCol_DragDropTarget] = attention;
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
#ifdef IMGUI_HAS_DOCK
    colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
#endif

    // ImPlot::StyleColorsAuto();

    // ImVec4 *pcolors = ImPlot::GetStyle().Colors;
    // pcolors[ImPlotCol_PlotBg] = ImVec4(0, 0, 0, 0);
    // pcolors[ImPlotCol_PlotBorder] = ImVec4(0, 0, 0, 0);
    // pcolors[ImPlotCol_Selection] = attention;
    // pcolors[ImPlotCol_Crosshairs] = colors[ImGuiCol_Text];

    // ImPlot::GetStyle().DigitalBitHeight = 20;

    // auto &pstyle = ImPlot::GetStyle();
    // pstyle.PlotPadding = pstyle.LegendPadding = {12, 12};
    // pstyle.LabelPadding = pstyle.LegendInnerPadding = {6, 6};
    // pstyle.LegendSpacing = {10, 2};
    // pstyle.AnnotationPadding = {4, 2};

    // const ImU32 Dracula[] = {4288967266, 4285315327, 4286315088, 4283782655, 4294546365,
    //                          4287429361, 4291197439, 4294830475, 4294113528, 4284106564};
    //                          ImPlot::GetStyle().Colormap =
    //                          ImPlot::AddColormap("Dracula", Dracula, 10);
}

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

App::App(std::string title, int w, int h, int argc, char const *argv[])
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) abort();

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only

    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    Window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (Window == NULL)
    {
        fprintf(stderr, "Failed to initialize GLFW window!\n");
        glfwTerminate();
        abort();
    }
    glfwMakeContextCurrent(Window);

    // init glew
    if (GLEW_OK != glewInit()) { abort(); }
    while (GLFW_NO_ERROR != glfwGetError(NULL))
    {
        ; /* glewInit may cause some OpenGL errors -- flush the error state */
    }

    // Print version on console to see that everything initialized correctly
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
    std::cout << "GLEW Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1); // Enable vsync

#if USE_IMGUI
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable docking
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    // ImPlot::StyleColorsDark();
    // ImGui::StyleColorsLight();
    ClearColor = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);
    StyeColorsApp();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look
    // identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    io.Fonts->AddFontFromFileTTF("resource/fonts/Roboto-Medium.ttf", 16.0f);
#endif
}

App::~App()
{
#if USE_IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    // ImPlot::DestroyContext();
    ImGui::DestroyContext();
#endif
    glfwDestroyWindow(Window);
    glfwTerminate();

    // if (this->sceneBuffer) { delete this->sceneBuffer; }
}

void App::Run()
{
    Start();

    // Main loop
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();

        // glClear(GL_COLOR_BUFFER_BIT);
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0.0f, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();

#if USE_IMGUI
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(); // allow docking in main viewport
#endif
        // update loop
        Update();
#if USE_IMGUI

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make
        // it easier to paste this code elsewhere. For this specific demo app we could also call
        // glfwMakeContextCurrent(window) directly)
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
#endif
        glfwSwapBuffers(Window);
    }
}

// void App::RenderViewport()
// {
//     ImGui::Begin("Scene");
//     {
//         ImGui::BeginChild("GameRender");

//         float width = ImGui::GetContentRegionAvail().x;
//         float height = ImGui::GetContentRegionAvail().y;

//         // *m_width = width;
//         // *m_height = height;

//         // ImGui::Image((ImTextureID)sceneBuffer->getFrameTexture(),
//         ImGui::GetContentRegionAvail(),
//         //              ImVec2(0, 1), ImVec2(1, 0));
//     }
//     ImGui::EndChild();
//     ImGui::End();
// }

ImVec2 App::GetWindowSize() const
{
    int w, h;
    glfwGetWindowSize(Window, &w, &h);
    return ImVec2(w, h);
}