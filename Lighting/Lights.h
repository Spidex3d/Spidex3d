#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>


class Lights
{
public:


	
	static Lights* Instance();

	static void ImGuiLightsSetUp();

	void LightSetUp();

	void LightRender();

	//std::vector<LightData> myLights;
	//std::vector<LightData> myLights = {
	//		{"Light1", 1},
	//		{"Light2", 2},
	//		// Add more lights as needed
	//};


private:



};

