#ifndef IMAGE_HELPER_H_
#define IMAGE_HELPER_H_

#include "GL/glew.h"
#include <cstdint>
#include <iostream>

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char *filename, GLuint *out_texture, int *out_width,
                         int *out_height);

bool LoadTextureFromMemory(const uint8_t *image_data, const int image_width, const int image_height,
                           GLuint *out_texture, int *out_width, int *out_height);

bool UpdateTextureFromMemory(const uint8_t *new_image_data, const int new_image_width,
                             const int new_image_height, const GLuint image_texture,
                             const int image_width, const int image_height);

#endif //! IMAGE_HELPER_H_
