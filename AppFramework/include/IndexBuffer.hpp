#ifndef INDEXBUFFER_HPP_
#define INDEXBUFFER_HPP_

class IndexBuffer
{
  private:
    unsigned int m_RendererID;
    unsigned int m_Count;

  public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif //! INDEXBUFFER_HPP_