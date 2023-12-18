#pragma once

// FrameBuffer.h
#include "Renderer.h"

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