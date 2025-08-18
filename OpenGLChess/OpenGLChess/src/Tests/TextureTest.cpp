#include "TextureTest.h"
#include "../Texture.h"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <iostream>

namespace test
{
	TextureTest::TextureTest()
	{
	}
	TextureTest::~TextureTest()
	{
	}
	void TextureTest::OnUpdate(float deltaTime)
	{
		
	}
	void TextureTest::onRenderer()
	{

	}
	void TextureTest::OnImGuiRenderer(Texture& texture)
	{
		//ImGui::ShowDemoWindow();
		ImGui::InputText("Image Name", &m_FileName);
		if (ImGui::Button("Select Image"))
		{
			m_FilePath = "res/textures/";
			m_FilePath.append(m_FileName);
			std::cout << m_FilePath << std::endl;
			texture.changeTexture(m_FilePath);
		}
		
		//std::cout << m_FileName << std::endl;
	}
}