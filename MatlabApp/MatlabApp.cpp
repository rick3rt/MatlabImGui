#include "MatlabApp.h"

MatlabApp::~MatlabApp()
{
    if (m_ImageTexture) delete m_ImageTexture;
}

void MatlabApp::Start()
{
    setFont("resource/fonts/Roboto-Medium.ttf", 18.0f);
    m_isRunning = true;
    m_ImageTexture = new ImageTexture("resource/img/img1.jpg");
}

void MatlabApp::UpdateUI()
{
    if (ImGui::Begin("UI"))
    {
        ImGui::Text("Both types:");
        float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.50f;
        ImGui::ColorPicker4("##MyColor##5", (float *)&m_Color,
                            ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview |
                                ImGuiColorEditFlags_AlphaBar);

        w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.25;
        if (ImGui::Button("Red", ImVec2(w, 0))) { m_Color = {1.0f, 0.0f, 0.0f, 1.0f}; }
        ImGui::SameLine();
        if (ImGui::Button("Green", ImVec2(w, 0))) { m_Color = {0.0f, 0.0f, 1.0f, 1.0f}; }
        ImGui::SameLine();
        if (ImGui::Button("Blue", ImVec2(w, 0))) { m_Color = {0.0f, 1.0f, 0.0f, 1.0f}; }
    }
    ImGui::End();

    // draw image
    if (ImGui::Begin("OpenGL Texture Text"))
    {
        ImGui::Text("pointer = %p", m_ImageTexture->texture);
        ImGui::Text("size = %d x %d", m_ImageTexture->width, m_ImageTexture->height);
        if (ImGui::Button("img1")) m_ImageTexture->Update("resource/img/img1.jpg");
        if (ImGui::Button("img2")) m_ImageTexture->Update("resource/img/img2.png");

        ImGui::Image((void *)m_ImageTexture->texture,
                     ImVec2(m_ImageTexture->width, m_ImageTexture->height));
    }
    ImGui::End();

    // plot data
    ImGui::Begin("Plot");
    if (ImPlot::BeginPlot("Line Plot"))
    {
        ImPlot::SetupAxes("x", "y");
        ImPlot::PlotLine("f(x)", m_XData.data(), m_YData.data(), m_XData.size());
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        ImPlot::EndPlot();
    }
    ImGui::End();

    ImGui::Begin("PlotRaw");
    if (ImPlot::BeginPlot("Line Plot"))
    {
        ImPlot::SetupAxes("x", "y");
        ImPlot::PlotLine("f(x)", m_XDataRaw, m_YDataRaw, m_SizeRaw);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        ImPlot::EndPlot();
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
    // ImGui::ShowDebugLogWindow();
}

void MatlabApp::UpdateGL() {}

void MatlabApp::setData(const double *xdata, const double *ydata, size_t size)
{
    m_XData.clear();
    m_YData.clear();
    m_XData.insert(m_XData.end(), xdata, xdata + size);
    m_YData.insert(m_YData.end(), ydata, ydata + size);
}

void MatlabApp::setRawData(const double *xdata, const double *ydata, size_t size)
{
    m_XDataRaw = (double *)xdata;
    m_YDataRaw = (double *)ydata;
    m_SizeRaw = size;
}
