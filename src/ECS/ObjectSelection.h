#pragma once
#include <glad\glad.h>
#include "EntityNode.h"


/*
 My version of Object selection so we can click on an object in the scean and have it selected
 also we need to be selected in the scean node as well and if we select it in the treenode it needs to select it on screen
 we will need some sort of bounding box to show which object is selected
 it will need an object index, true/false is selected
*/

class ObjectSelection {

public:
	static ObjectSelection* Instance() {
		static ObjectSelection* objectSelect = new ObjectSelection;

		return objectSelect;
	}

	

	void ObjSelection() {

	  ImGui::Begin("Selection");

	  if (selectedData) {
		  ImGui::InputText("Selected Value", selectedData->value.data(), selectedData->value.size());
	  }
	  else {
		  ImGui::Text("No Object selected");
	  }

	  ImGui::End();

	}

	  ~ObjectSelection() {}

	void objInit(){
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_pickingTexture);
		glBindTexture(GL_TEXTURE_2D, m_pickingTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pickingTexture, 0);

		glGenTextures(1, &m_depthTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB ERROR, status: 0x%x\n", Status);
			exit(1);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void EnableWriting() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	}

	void DisableWriting() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	struct PixelInfo {
		int ObjectID = 0;
		int DrawID = 0;
		int PrimID = 0;
	
	void Print() {
		printf("Object %d draw %d prim %d\n", ObjectID, DrawID, PrimID);
	}
	};

	PixelInfo ReadPixel(unsigned int x, unsigned int y) {

		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
		glReadBuffer(GL_COLOR_ATTACHMENT0);

		PixelInfo Pixel;
		glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &Pixel);

		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);


		return Pixel;

	}

	//void TestTexture() {

	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	//	ImGui::Begin("Texture Test");
	//	const float window_width = ImGui::GetContentRegionAvail().x;
	//	const float window_height = ImGui::GetContentRegionAvail().y;

	//	//Rescale_frambuffer(window_width, window_height);
	//	glViewport(0, 0, window_width, window_height);

	//	ImVec2 pos = ImGui::GetCursorScreenPos();

	//	ImGui::GetWindowDrawList()->AddImage((void*)m_pickingTexture, ImVec2(pos.x, pos.y),
	//		ImVec2(pos.x + window_width, pos.y + window_height), ImVec2(0, 1), ImVec2(1, 0));

	//	ImGui::End();
	//	ImGui::PopStyleVar();
	//}

	



private:
	GLuint m_fbo = 0;
	GLuint m_pickingTexture = 0;
	GLuint m_depthTexture = 0;
	
	bool IsObjSelected;


};
