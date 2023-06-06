#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

class VertexBuffer
{
  private:
    unsigned int m_RendererID;

  public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

#endif //! VERTEXBUFFER_HPP_