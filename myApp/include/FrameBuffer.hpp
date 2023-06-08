#ifndef FRAMEBUFFER_HPP_
#define FRAMEBUFFER_HPP_

// FrameBuffer.h
#include "Renderer.hpp"

#include <iostream>

class FrameBuffer
{
  private:
    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;

  public:
    FrameBuffer(float width, float height);
    ~FrameBuffer();
    unsigned int getFrameTexture();
    void RescaleFrameBuffer(float width, float height);
    void Bind() const;
    void Unbind() const;
};

#endif //! FRAMEBUFFER_HPP_