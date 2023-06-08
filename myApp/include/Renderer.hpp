#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <GL/glew.h>

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

#define ASSERT(x)                                                                                  \
    if (!(x)) __debugbreak()

#define GLCall(x)                                                                                  \
    GLClearError();                                                                                \
    x;                                                                                             \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{

  public:
    Renderer();
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
    void Draw(const VertexArray *va, const IndexBuffer *ib, const Shader *shader) const;
};

#endif //! RENDERER_HPP_