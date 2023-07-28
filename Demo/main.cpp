#define TEST_CASE_1

#ifdef TEST_CASE_1

#include "Demo.hpp"

int main(int argc, char const *argv[])
{
    Demo app("Demo App", 1280, 760, argc, argv);
    app.Run();
    return 0;
}

#endif

#ifdef TEST_CASE_2
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
#ifdef TEST_CASE_3
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

GLFWwindow *InitWindow()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 "
                        "compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

int main(void)
{
    GLFWwindow *window = InitWindow();
    if (!window) return -1;

    float positions[] = {
        -0.5f, -0.5f, // 0
        0.5f,  -0.5f, // 1
        0.5f,  0.5f,  // 2
        -0.5f, 0.5f   // 3
    };

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    {
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        IndexBuffer ib(indices, 6);

        VertexBufferLayout layout;
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        Shader shader("resource/shader/basic.shader");
        shader.Bind();

        float red = 0.0f;
        float step = 0.01f;

        Renderer renderer;

        do
        {
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", red, 0.3, 0.8, 1.0);

            renderer.Draw(va, ib, shader);

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();

            // increment red
            // if (red < 0.0f || red > 1.0f) step *= -1.0;
            // red += step;

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
#endif