#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() : m_va_index(0) { GLCall(glGenVertexArrays(1, &m_RendererID)); }

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_RendererID)); }

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RendererID)); }

void VertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    this->Bind();
    vb.Bind();
    const auto &elements = layout.GetElements();
    size_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GLCall(glEnableVertexAttribArray(m_va_index));
        GLCall(glVertexAttribPointer(m_va_index, element.count, element.type, element.normalized,
                                     layout.GetStride(), (const void *)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        m_va_index++; // increment va index
    }
    GLCall(glEnableVertexAttribArray(0));
}
