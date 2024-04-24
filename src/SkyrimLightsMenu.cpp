#include "SkyrimLightsMenu.hpp"

void SLM::SkyrimLightsMenu::Serialize(SKSE::SerializationInterface* intfc) const
{
	scene.Serialize(intfc);
}

void SLM::SkyrimLightsMenu::Deserialize(SKSE::SerializationInterface* intfc)
{
	scene.GetProps().clear();
	scene.Deserialize(intfc);
}

void SLM::SkyrimLightsMenu::DoFrame()
{
	if (IsMenuActive())
	{
		if (showDemo)
		{
			// Show ImGui documentation instead
			ImGui::ShowDemoWindow();
		}
		else
		{
			// Draw main window
			bool open = true;
			ImGui::BeginDisabled(scene.IsHidden());
			if (ImGui::Begin("##Main", &open))
			{
				scene.DrawControlWindow();
			}

			if (!open)
				SetMenuActive(false);

			ImGui::End();
			ImGui::EndDisabled();
		}
	}

	// Show or Hide window
	if (ImGui::IsKeyPressed(ImGuiKey_End, false))
	{
		logger::trace("Toggle menu");
		ToggleMenu();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_P, false))
	{
		scene.TogglePositioning();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape, false))
	{
		logger::trace("Hiding menu");
		Deactivate();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Tab, false))
	{
		scene.ImGuiGoBack();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_L, false))
	{
		scene.ToggleLookAround();
	}
#ifdef DEBUG
	else if (ImGui::IsKeyPressed(ImGuiKey_H) && IsMenuActive())
	{
		ToggleShowDemo();
	}
#endif
}

inline bool SLM::SkyrimLightsMenu::IsMenuActive() const { return IsActive; }

void SLM::SkyrimLightsMenu::Deactivate()
{
	SetMenuActive(false);
}

void SLM::SkyrimLightsMenu::ToggleMenu()
{
	SetMenuActive(!IsActive);
}

void SLM::SkyrimLightsMenu::SetMenuActive(bool setActive)
{
	auto& io = ImGui::GetIO();

	if (setActive)
	{

		// Show ImGui mouse
		{
			io.WantCaptureMouse = true;
			io.MouseDrawCursor  = true;
		}
		scene.Activate();
		RE::PlaySound("UIJournalTabsSD");
	}
	else
	{

		// Hide ImGui mouse
		{
			io.MouseDrawCursor  = false;
			io.WantCaptureMouse = false;
		}
		scene.Deactivate();
		RE::PlaySound("UIMenuCancel");
	}

	IsActive = setActive;
}

void SLM::SkyrimLightsMenu::SetImGuiStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding     = ImVec2(15, 15);
	style->WindowRounding    = 5.0f;
	style->ChildRounding     = 5.0f;
	style->FramePadding      = ImVec2(5, 5);
	style->FrameRounding     = 4.0f;
	style->ItemSpacing       = ImVec2(12, 8);
	style->ItemInnerSpacing  = ImVec2(8, 6);
	style->IndentSpacing     = 25.0f;
	style->ScrollbarSize     = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize       = 5.0f;
	style->GrabRounding      = 3.0f;
	style->DisabledAlpha     = 0.3f;

	style->Colors[ImGuiCol_Text]                 = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled]         = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg]             = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg]              = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg]              = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border]               = ImVec4(0.80f, 0.80f, 0.83f, 0.35f);
	style->Colors[ImGuiCol_BorderShadow]         = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg]              = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive]        = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg]              = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive]        = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg]            = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark]            = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab]           = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button]               = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered]        = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive]         = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header]               = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered]        = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive]         = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered]    = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive]     = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines]            = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered]     = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram]        = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}

inline void SLM::SkyrimLightsMenu::ToggleShowDemo() { showDemo = !showDemo; }

void SLM::SkyrimLightsMenu::Revert()
{
	scene.GetProps().clear();
}

bool SLM::SkyrimLightsMenu::AllowGameInput(RE::InputEvent* event)
{
	const auto* buttonEvt  = event->AsButtonEvent();
	const auto* controlMap = RE::ControlMap::GetSingleton();

	if (!RE::PlayerCamera::GetSingleton()->IsInFreeCameraMode())
		return false;

	return (buttonEvt && (buttonEvt->GetIDCode() == controlMap->GetMappedKey("Forward", buttonEvt->GetDevice()) ||
							 buttonEvt->GetIDCode() == controlMap->GetMappedKey("Back", buttonEvt->GetDevice()) ||
							 buttonEvt->GetIDCode() == controlMap->GetMappedKey("Strafe Left", buttonEvt->GetDevice()) ||
							 buttonEvt->GetIDCode() == controlMap->GetMappedKey("Strafe Right", buttonEvt->GetDevice()))) ||
	       (event->GetDevice() == RE::INPUT_DEVICE::kMouse && scene.IsHidden());
}

bool SLM::SkyrimLightsMenu::AllowImGuiInput(RE::InputEvent* event)
{
	if (!scene.IsHidden())
		return true;

	// Block all mouse input
	return !(event->GetDevice() == RE::INPUT_DEVICE::kMouse);
}
