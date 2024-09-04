#pragma once
#include "Configs.h"


SPIDEX_INLINE static bool IconButton(const char* icon, const ImVec2& size = ImVec2(getLineHeight(), 0.0f)) {
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Button, COLOR_NONE);

	// Font size!
	//setFont(TINY_FONT_INDEX);
	bool pressed = ImGui::ButtonEx(icon, size, ImGuiButtonFlags_AlignTextBaseLine);
	// reset font
	//resetFont();

	ImGui::PopStyleColor(3);
	return pressed;
}
