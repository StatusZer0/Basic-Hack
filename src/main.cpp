#include <imgui-cocos.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {}).draw([] {
        ImGui::Begin("Basic Hack");

		if (ImGui::Button("Test Alert"))
		{
			FLAlertLayer::create(
				"Basic Hack", //title
				"Let's hope this works.", //content
				"It worked" // button
			)->show();
		}

		ImGui::End();
    });
}