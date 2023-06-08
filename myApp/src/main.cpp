#define TEST_CASE_1

#ifdef TEST_CASE_1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Application.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

// some data
float positions[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, // 0
    0.5f,  -0.5f, 1.0f, 0.0f, // 1
    0.5f,  0.5f,  1.0f, 1.0f, // 2
    -0.5f, 0.5f,  0.0f, 1.0f, // 3
};

unsigned int indices[] = {
    0, 1, 2, // triangle 1
    2, 3, 0, // triangle 2
};

class Demo : public App
{
  private:
    VertexArray *m_va;
    VertexBuffer *m_vb;
    IndexBuffer *m_ib;
    VertexBufferLayout *m_layout;
    Shader *m_shader;
    Texture *m_texture;
    Renderer *m_renderer;

    float r = 0.0f;
    float increment = 0.05f;

  public:
    using App::App;

    ~Demo();

    // will run during initialization
    void Start() override;

    // display loop
    void UpdateUI() override;
    void UpdateGL() override;
};

void Demo::Start()
{

    m_va = new VertexArray();
    m_vb = new VertexBuffer(positions, sizeof(positions));
    m_ib = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));
    m_layout = new VertexBufferLayout();
    m_shader = new Shader("resource/shader/texture.shader");
    m_texture = new Texture("resource/textures/small_alpha.png");
    m_renderer = new Renderer();

    m_layout->Push<float>(2); // position coordinates
    m_layout->Push<float>(2); // texture coordinates
    m_va->AddBuffer(*m_vb, *m_layout);

    m_shader->Bind();
    m_shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    m_texture->Bind(0);
    m_shader->SetUniform1i("u_Texture", 0);
}

void Demo::UpdateUI()
{

    ImGui::Begin("test");
    ImGui::Button("test");
    ImGui::Button("test");
    ImGui::End();

    // bind_framebuffer();

    // glUseProgram(shader);
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);
    // glUseProgram(0);

    // unbind_framebuffer();
}
void Demo::UpdateGL()
{

    // clear screen
    m_renderer->Clear();
    // bind shader and set uniform
    m_shader->Bind();

    // shader.SetUniform4f("u_Color", r, 0.3f, 0.8, 1.0f);

    // draw vertexarray and indexbuffer using shader
    m_renderer->Draw(m_va, m_ib, m_shader);

    // update r
    if (r > 1.0f)
        increment = -0.05f;
    else if (r < 0.0f)
        increment = 0.05f;
    r += increment;
}
Demo::~Demo()
{
    if (m_va) { delete m_va; }
    if (m_vb) { delete m_vb; }
    if (m_ib) { delete m_ib; }
    if (m_layout) { delete m_layout; }
    if (m_shader) { delete m_shader; }
    if (m_texture) { delete m_texture; }
    if (m_renderer) { delete m_renderer; }
}

int main(int argc, char const *argv[])
{
    Demo app("Demo App", 1280, 760, argc, argv);
    app.Run();

    return 0;
}

#endif

#if 0
const unsigned int width = 1280;
const unsigned int height = 720;
const char title[] = "test";

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) abort();

    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only

    // Create window with graphics context
    GLFWwindow *Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (Window == NULL)
    {
        fprintf(stderr, "Failed to initialize GLFW window!\n");
        glfwTerminate();
        abort();
    }
    glfwMakeContextCurrent(Window);

    // init glew
    if (GLEW_OK != glewInit()) { abort(); }
    /* glewInit may cause some OpenGL errors -- flush the error state */
    while (GLFW_NO_ERROR != glfwGetError(NULL)) {}

    // Print version on console to see that everything initialized correctly
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
    std::cout << "GLEW Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1); // Enable vsync

    // =========
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f,  -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f,  1.0f, 1.0f, // 2
        -0.5f, 0.5f,  0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2, // triangle 1
        2, 3, 0, // triangle 2
    };

    // float triangle_colors[] = {
    //     1.0, 1.0, 0.0, // rgb
    //     0.0, 0.0, 1.0, // rgb
    //     1.0, 0.0, 0.0, // rgb
    // };

    // texture alpha blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    {
        VertexArray m_va; // vertex array that will hold vertex buffer and their attributes
        VertexBuffer m_vb(positions, sizeof(positions)); // size in bytes
        VertexBufferLayout m_layout;
        m_layout.Push<float>(2); // position coordinates
        m_layout.Push<float>(2); // texture coordinates
        m_va.AddBuffer(m_vb, m_layout);

        // VertexBuffer m_vb_colors(triangle_colors, sizeof(float) * 9);
        // VertexBufferLayout m_layout_colors;
        // m_layout.Push<float>(3);
        // m_va.AddBuffer(m_vb_colors, m_layout_colors);

        IndexBuffer m_ib(indices, sizeof(indices) / sizeof(unsigned int));

        Shader shader("resource/shader/texture.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("resource/textures/small_alpha.png");
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;

        // unbind everything
        m_va.Unbind();
        m_vb.Unbind();
        m_ib.Unbind();
        shader.Unbind();

        float r = 0.0f;
        float increment = 0.05;

        // =========================================================================
        // main loop
        // =========================================================================

        while (!glfwWindowShouldClose(Window))
        {
            // clear screen
            renderer.Clear();
            // bind shader and set uniform
            shader.Bind();
            // shader.SetUniform4f("u_Color", r, 0.3f, 0.8, 1.0f);
            // draw vertexarray and indexbuffer using shader
            renderer.Draw(m_va, m_ib, shader);

            // update r
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            glfwSwapBuffers(Window);
            glfwPollEvents();
        }
    }

    // =========================================================================
    // cleanup
    // =========================================================================
    glfwDestroyWindow(Window);
    glfwTerminate();

    return 0;
}
#endif
// =============================================================================
// =============================================================================
#ifdef TEST_CASE_2

#include <GL\glew.h>

#include <GLFW\glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

GLuint VAO;
GLuint VBO;
GLuint FBO;
GLuint RBO;
GLuint texture_id;
GLuint shader;

const char *vertex_shader_code = R"*(
#version 330

layout (location = 0) in vec3 pos;

void main()
{
	gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
}
)*";

const char *fragment_shader_code = R"*(
#version 330

out vec4 color;

void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
}
)*";

void create_triangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, // 1. vertex x, y, z
        1.0f,  -1.0f, 0.0f, // 2. vertex ...
        0.0f,  1.0f,  0.0f  // etc...
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void add_shader(GLuint program, const char *shader_code, GLenum type)
{
    GLuint current_shader = glCreateShader(type);

    const GLchar *code[1];
    code[0] = shader_code;

    GLint code_length[1];
    code_length[0] = strlen(shader_code);

    glShaderSource(current_shader, 1, code, code_length);
    glCompileShader(current_shader);

    GLint result = 0;
    GLchar log[1024] = {0};

    glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
        std::cout << "Error compiling " << type << " shader: " << log << "\n";
        return;
    }

    glAttachShader(program, current_shader);
}

void create_shaders()
{
    shader = glCreateProgram();
    if (!shader)
    {
        std::cout << "Error creating shader program!\n";
        exit(1);
    }

    add_shader(shader, vertex_shader_code, GL_VERTEX_SHADER);
    add_shader(shader, fragment_shader_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar log[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error linking program:\n" << log << '\n';
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error validating program:\n" << log << '\n';
        return;
    }
}

void create_framebuffer()
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void bind_framebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }

void unbind_framebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void rescale_framebuffer(float width, float height)
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW initialisation failed!\n";
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "My Window", NULL, NULL);
    if (!mainWindow)
    {
        std::cout << "GLFW creation failed!\n";
        glfwTerminate();
        return 1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew initialisation failed!\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    create_triangle();
    create_shaders();
    create_framebuffer();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(); // allow docking in main viewport

        ImGui::Begin("test");
        ImGui::Button("haha");
        ImGui::End();

        ImGui::Begin("My Scene");

        const float window_width = ImGui::GetContentRegionAvail().x;
        const float window_height = ImGui::GetContentRegionAvail().y;

        rescale_framebuffer(window_width, window_height);
        glViewport(0, 0, window_width, window_height);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage((void *)texture_id, ImVec2(pos.x, pos.y),
                                             ImVec2(pos.x + window_width, pos.y + window_height),
                                             ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::Render();

        bind_framebuffer();

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        unbind_framebuffer();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(mainWindow);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &texture_id);
    glDeleteRenderbuffers(1, &RBO);

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}

#endif