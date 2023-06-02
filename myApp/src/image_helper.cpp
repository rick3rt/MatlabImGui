#include "image_helper.h"

// include here to compile.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool LoadTextureFromFile(const char *filename, GLuint *out_texture, int *out_width, int *out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char *image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on
    // WebGL for non power-of-two textures glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
    // GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image_data);
    stbi_image_free(image_data);

    // check if out_texture already was set:
    if (*out_texture != 0) glDeleteTextures(1, out_texture);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool LoadTextureFromMemory(const uint8_t *image_data, const int image_width, const int image_height,
                           GLuint *out_texture, int *out_width, int *out_height)
{
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on
    // WebGL for non power-of-two textures
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image_data); // only work with RGB for now

    // GLenum error;
    // if ((error = glGetError()) != GL_NO_ERROR) { std::cout << "gl error: " << error << std::endl;
    // }

    // check if out_texture already was set:
    if (*out_texture != 0) { glDeleteTextures(1, out_texture); }

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    // GLenum error;
    // if ((error = glGetError()) != GL_NO_ERROR) { std::cout << "gl error: " << error << std::endl;
    // }

    return true;
}

bool UpdateTextureFromMemory(const uint8_t *new_image_data, const int new_image_width,
                             const int new_image_height, const GLuint image_texture,
                             const int image_width, const int image_height)
{
    glBindTexture(GL_TEXTURE_2D, image_texture);
    if (new_image_height == image_height && new_image_width == image_width)
    {
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, new_image_data);
        return true;
    }
    return false;
}