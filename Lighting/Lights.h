#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

//struct LightData {
//	std::string name;
//	int LightId;
//	int LightType;
//};
//
//	LightData* selectedLightData = nullptr;

class Lights
{
public:


	
	static Lights* Instance();

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

