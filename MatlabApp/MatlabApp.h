#pragma once

#include "imga.h"
#include <vector>

class MatlabApp : public ImGuiApp
{
  private:
    bool m_isRunning = false;
    ImVec4 m_Color = {1.0f, 1.0f, 1.0f, 1.0f};
    ImageTexture *m_ImageTexture = nullptr;
    std::vector<double> m_XData;
    std::vector<double> m_YData;
    double *m_XDataRaw = nullptr;
    double *m_YDataRaw = nullptr;
    size_t m_SizeRaw = 0;

  public:
    using ImGuiApp::ImGuiApp;

    ~MatlabApp();

    // will run during initialization
    void Start() override;

    // display loop
    void UpdateUI() override;
    void UpdateGL() override;

    void SetColor(float r, float g, float b, float a = 1.0f) { m_Color = {r, g, b, a}; }
    void setData(const double *xdata, const double *ydata, size_t size);
    void setRawData(const double *xdata, const double *ydata, size_t size);
};