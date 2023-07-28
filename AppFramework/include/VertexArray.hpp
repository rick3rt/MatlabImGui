#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray
{
  private:
    unsigned int m_RendererID;

    /**
     * @brief possible to associate multiple vertexbuffers and layouts via
     * AddBuffer. This is an internal counter to cound attribute arrays
     */
    unsigned int m_va_index;

  public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;
    void Unbind() const;
};

#endif //! VERTEXARRAY_HPP_
