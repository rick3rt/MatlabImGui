#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
  private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    // caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;

  public:
    Shader(const std::string &filepath);
    ~Shader();

    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    void Bind() const;
    void Unbind() const;

    // set Uniforms
    void SetUniform1i(const std::string &name, int value);

    void SetUniform1f(const std::string &name, float v0);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

  private:
    int GetUniformLocation(const std::string &name);
};
