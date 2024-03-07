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

std::string category;

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {}).draw([] {

		if (showMenu) {

        	ImGui::Begin("Basic Hack");

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{
					if (ImGui::MenuItem("Bypass")) { category = "Bypass"; }
					if (ImGui::MenuItem("Cheats")) { category = "Cheats"; }
					if (ImGui::MenuItem("Close", "F6")) { showMenu = false; }
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::Text("Basic Hack by StatusZer0" + Mod::get()->getVersion().toString());
			ImGui::Separator();

			Hacks::getHackList(category);

			ImGui::Text(category);
			ImGui::BeginChild("Scrolling");
				for (size_t i = 0; i < allHacks.size; i++)
				{
   					const auto& obj = allHacks[i];
					ImGui::Text(obj.name);
					ImGui::Text(obj.desc);
					switch (obj.type)
					{
						case "bool":
							ImGui::Checkbox(obj.name);
							break;

						case "float":
							ImGui::SliderFloat(obj.name, %f, 0.1f, 2f);
							break;

						case "button":
							ImGui::Button(obj.name);
							break;
					}
					
					ImGui::Spacing();
				}
				ImGui::EndChild();

			if (ImGui::Button("Test Alert"))
			{
				FLAlertLayer::create(
					"Basic Hack", //title
					"Using any hacks from the <cb>Cheats</c> category on rated levels may get you <cr>banned from the leaderboards!</c> Please use <cy>Safe Mode</c> when using these!", //content
					"OK" // button
				)->show();
			}

			ImGui::End();
		}
    });
}