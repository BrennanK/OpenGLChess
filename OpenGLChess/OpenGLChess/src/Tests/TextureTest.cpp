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
		m_FilePath = "res/textures/";
		m_FilePath.append(m_FileName);
	}
	void TextureTest::onRenderer()
	{

	}
	void TextureTest::OnImGuiRenderer()
	{
		//ImGui::ShowDemoWindow();
		ImGui::InputText("Image Name", &m_FileName);
		ImGui::Button("Select Image");
		
		//std::cout << m_FileName << std::endl;
	}
}