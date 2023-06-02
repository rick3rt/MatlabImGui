
#include "Demo.hpp"

void Demo::Start()
{
    // on GUI create, put stuff to initialze GUI here
}

void Demo::Update()
{
    // on GUI update, put stuff to render and poll for updates here
    ImGui::ShowDemoWindow();

    ImGui::Begin("Viewport");
    ImGui::Button("test");
    ImGui::End();
}