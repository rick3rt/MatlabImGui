#include "Demo.hpp"

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <iostream>

float pos[]{
    -0.5000, -0.5000, // 0
    0.5000,  -0.5000, // 1
    0.5000,  0.5000,  // 2
    0.5000,  0.5000,  // 3
    -0.5000, -0.5000, // 4
    -0.5000, 0.5000,  // 5
};
unsigned int ind[] = {
    0, 1, 2, // triangle 1
    3, 4, 5, // triangle 2
};

float colors[] = {
    1, 0, 0, 1, // Red color, for the first vertex
    0, 1, 0, 1, // Green color, for the second vertex
    0, 0, 1, 1, // Blue color, for the third vertex
    0, 0, 1, 1, //
    1, 0, 0, 1, //
    0, 1, 0, 1, //

};

float triangle_colored[]{
    -0.5000, -0.5500, 1.0f, 0.0f, 0.0f, // x,y, - r,g,b
    0.5000,  -0.5500, 0.0f, 1.0f, 0.0f, // x,y, - r,g,b
    0.5000,  0.4500,  0.0f, 0.0f, 1.0f, // x,y, - r,g,b
};

Demo::~Demo()
{
    if (m_va) { delete m_va; }
    if (m_vb_col) { delete m_vb_col; }
    if (m_vb_pos) { delete m_vb_pos; }
    if (m_layout_col) { delete m_layout_col; }
    if (m_layout_pos) { delete m_layout_pos; }
    if (m_ib) { delete m_ib; }
    if (m_shader) { delete m_shader; }
    // if (m_texture) { delete m_texture; }
    if (m_renderer) { delete m_renderer; }
}

void Demo::Start()
{
    // configure font
    // this->setFont("resource/fonts/Roboto-Medium.ttf", 14.0f);

    m_va = new VertexArray();
    m_ib = new IndexBuffer(ind, sizeof(ind) / sizeof(unsigned int));

    m_vb_pos = new VertexBuffer(pos, sizeof(pos));
    m_vb_col = new VertexBuffer(colors, sizeof(colors));

    m_layout_pos = new VertexBufferLayout();
    m_layout_col = new VertexBufferLayout();
    m_layout_pos->Push<float>(2); // position coordinates
    m_layout_col->Push<float>(3); // color vales
    m_va->AddBuffer(*m_vb_pos, *m_layout_pos);
    m_va->AddBuffer(*m_vb_col, *m_layout_col);

    m_shader = new Shader("resource/shader/basic.shader");
    // m_texture = new Texture("resource/textures/small_alpha.png");
    m_renderer = new Renderer();

    m_shader->Bind();
    m_shader->SetUniform1f("u_Scale", scale);
    m_shader->SetUniform4f("u_Color", color.x, color.y, color.z, color.w);
    // m_texture->Bind(0);
    // m_shader->SetUniform1i("u_Texture", 0);
}

void Demo::UpdateUI()
{
    if (ImGui::Begin("UI"))
    {
        ImGui::Text("Both types:");
        float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.50f;
        ImGui::ColorPicker4("##MyColor##5", (float *)&color,
                            ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview |
                                ImGuiColorEditFlags_AlphaBar);

        w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.25;
        if (ImGui::Button("Red", ImVec2(w, 0))) { color = {1.0f, 0.0f, 0.0f, 1.0f}; }
        ImGui::SameLine();
        if (ImGui::Button("Green", ImVec2(w, 0))) { color = {0.0f, 0.0f, 1.0f, 1.0f}; }
        ImGui::SameLine();
        if (ImGui::Button("Blue", ImVec2(w, 0))) { color = {0.0f, 1.0f, 0.0f, 1.0f}; }

        ImGui::SliderFloat("Scale", &scale, 0.0f, 2.0f);

        ImGui::End();
    }

    ImGui::ShowDemoWindow();
    // ImGui::ShowDebugLogWindow();
}

void Demo::UpdateGL()
{
    m_renderer->Clear();                                                   // clear screen
    m_shader->Bind();                                                      // bind shader and set uniform
    m_shader->SetUniform1f("u_Scale", scale);                              // set rectangle scale
    m_shader->SetUniform4f("u_Color", color.x, color.y, color.z, color.w); // set drawing color
    m_renderer->Draw(m_va, m_ib, m_shader); // draw vertexarray and indexbuffer using shader
}
