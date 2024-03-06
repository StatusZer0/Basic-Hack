#include <imgui-cocos.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include "hacks.hpp"

using namespace geode::prelude;

bool showMenu = false;

class $modify (CCKeyboardDispatcher)
{
	bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool down, bool repeat)
	{
		if (key == enumKeyCodes::KEY_F6 && down)
		{
			showMenu = !showMenu;
		}

		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
	}
};

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {}).draw([] {

		if (showMenu) {

        	ImGui::Begin("Basic Hack");

			ImGui::BeginChild("Scrolling");
				for (int n = 0; n < 50; n++)
				{
   					ImGui::Button("%04d: Some text", n);
				}
				ImGui::EndChild();

			if (ImGui::Button("Test Alert"))
			{
				FLAlertLayer::create(
					"Basic Hack", //title
					"Let's hope this works.", //content
					"It worked" // button
				)->show();
			}

			ImGui::End();
		}
    });
}