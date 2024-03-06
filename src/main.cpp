#include <imgui-cocos.hpp>

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        ImGui::ShowDemoWindow();
    });
}