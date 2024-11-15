#pragma once
#include <imgui\ImGuiAF.h>
#include <imgui\imgui.h>
#include <imgui\imgui_internal.h>

#ifndef SPIDEX_INLINE
#define SPIDEX_INLINE 
#endif // !SPIDEX_INLINE

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;

// List of the Objects
const int OBJ_CAMERA = 0; // Main Camera
const int OBJ_LIGHT_0 = 1;
const int OBJ_LIGHT_1 = 2;
const int OBJ_LIGHT_2 = 3;
const int OBJ_CUBE = 4;
const int OBJ_PLANE = 5;
const int OBJ_TUBE = 6;
const int OBJ_SPHERE = 7;
const int OBJ_TORUS = 8;
const int OBJ_PYRAMID = 9;
const int OBJ_OBJ_MODEL = 20;
const int OBJ_SKY_BOX = 30;
const int OBJ_TERRAIN = 35;
const int OBJ_WATER = 40;



enum FontIndex : int {
	REG_FONT_INDEX = 0,
	SMALL_FONT_INDEX,
	TINY_FONT_INDEX,
};

const float FONT_SIZE = 28.0f; // comic
const float SMALL_FONT_SIZE = 13.0f;
const float TINY_FONT_SIZE = 10.0f;

constexpr const char* FONT_PATH_MAIN = "Fonts/comic.ttf";

constexpr const char* ROBOTO_REG_PATH = "Fonts/Roboto-Regular.ttf";
constexpr const char* FA_REG_PATH = "Fonts/FA-Regular-400.otf";
constexpr const char* FA_SOLID_PATH = "Fonts/FA-Solid-900.otf";



// Colors
const ImVec4 COLOR_LIGHTBLUE(0.43f, 0.7f, 0.89f, 1.0f);
const ImVec4 COLOR_LIGHTGREEN(0.0f, 0.9f, 0.0f, 1.0f);

const ImVec4 COLOR_NONE(0.0f, 0.0f, 0.0f, 0.0f);

constexpr const char* SHADER_VERSION = "#version 460";

const ImGuiTreeNodeFlags NODE_FLAGS = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth |
ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick;
const ImGuiTreeNodeFlags NODE_SELECTED_FLAGS = NODE_FLAGS | ImGuiTreeNodeFlags_Selected;
const ImGuiTreeNodeFlags ROOT_SELECTED_FLAGS = NODE_FLAGS | ImGuiTreeNodeFlags_DefaultOpen;

static float SPIDEX_INLINE setFont(int index) {
	ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[index]);
}

static float SPIDEX_INLINE resetFont() {
	ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[REG_FONT_INDEX]);
}

static float SPIDEX_INLINE getLineHeight(bool withPadding = true) {
	if (withPadding)
		return (ImGui::GetTextLineHeight() + 2.0f * (ImGui::GetStyle().FramePadding.y));
	return ImGui::GetTextLineHeight();

}
