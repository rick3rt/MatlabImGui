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

    {
        ImGui::Begin("Colormap");
        static ImPlotColormap map = ImPlotColormap_Viridis;
        if (ImPlot::ColormapButton(ImPlot::GetColormapName(map), ImVec2(225, 0), map))
        {
            map = (map + 1) % ImPlot::GetColormapCount();
            // We bust the color cache of our plots so that item colors will
            // resample the new colormap in the event that they have already
            // been created. See documentation in implot.h.
            ImPlot::BustColorCache("##Heatmap1");
        }

        ImGui::LabelText("##Colormap Index", "%s", "Change Colormap");
        // ImGui::SetNextItemWidth(225);
        // ImGui::DragFloatRange2("Min / Max", &scale_min, &scale_max, 0.01f, -20, 20);

        static ImPlotHeatmapFlags hm_flags = 0;

        ImGui::CheckboxFlags("Column Major", (unsigned int *)&hm_flags, ImPlotHeatmapFlags_ColMajor);

        static ImPlotAxisFlags axes_flags =
            ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks;

        ImPlot::PushColormap(map);

        if (ImPlot::BeginPlot("##Heatmap1", ImVec2(225, 225),
                              ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
        {
            ImPlot::SetupAxes(NULL, NULL, axes_flags, axes_flags);

            ImPlot::PlotHeatmap("heat", m_img.data(), m_img_rows, m_img_cols, m_img_min, m_img_max, NULL,
                                ImPlotPoint(0, 0), ImPlotPoint(1, 1), hm_flags);
            ImPlot::EndPlot();
        }
        ImGui::SameLine();
        ImPlot::ColormapScale("##HeatScale", m_img_min, m_img_max, ImVec2(60, 225), "%.1f");
        ImGui::End();
    }

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

void MatlabApp::setImageData(const double *img, size_t rows, size_t cols)
{
    m_img.clear();
    m_img.insert(m_img.end(), img, img + rows * cols);
    m_img_rows = rows;
    m_img_cols = cols;
    m_img_min = *std::min_element(m_img.begin(), m_img.end());
    m_img_max = *std::max_element(m_img.begin(), m_img.end());
}
