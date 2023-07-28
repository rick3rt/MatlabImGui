#ifndef DEMO_HPP_
#define DEMO_HPP_

#include "Application.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

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
    ImVec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    float scale = 0.5f;

  public:
    using App::App;

    ~Demo();

    // will run during initialization
    void Start() override;

    // display loop
    void UpdateUI() override;
    void UpdateGL() override;
};

#endif //! DEMO_HPP_
