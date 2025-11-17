#include "TextureTest.h"
#include "Texture.h"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <iostream>
#include <filesystem>

namespace test
{
	TextureTest::TextureTest()
	{
		std::string folderPath = "res/textures"; // Replace with your folder's path
		int fileCount = 0;

		try {
			// Iterate through the directory entries
			for (const auto& entry : std::filesystem::directory_iterator(folderPath)) 
			{
				// Check if the current entry is a regular file (not a directory)
				if (std::filesystem::is_regular_file(entry.status())) {
					fileCount++;
					m_filenames.emplace_back(entry.path().filename().string());
				}
			}
			fillItems();
			std::cout << "Number of files in '" << folderPath << "': " << fileCount << std::endl;
		}
		catch (const std::filesystem::filesystem_error& ex) {
			std::cerr << "Error accessing folder: " << ex.what() << std::endl;
		}
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
		const char* modeitems[] = { "Text Box", "Scroll Select"};
		ImGui::ListBox("Choose Mode", &m_modeInt,modeitems , 2);
		m_mode = static_cast<SelectionMode>(m_modeInt);
		
		switch (m_mode)
		{

		case SelectionMode::TextBox:
			ImGui::InputText("Image Name", &m_FileName);
			if (ImGui::Button("Select Image"))
			{
				m_FilePath = "res/textures/";
				m_FilePath.append(m_FileName);
				
				texture.changeTexture(m_FilePath,0);
			}
			break;

		case SelectionMode::ScollableList:
			ImGui::ListBox("Selectable Images", &m_currentItem, m_items, 36);
			
			m_FilePath = "res/textures/";
			m_FileName = m_filenames[m_currentItem];
			m_FilePath.append(m_FileName);

			texture.changeTexture(m_FilePath,0);
			break;
		
		default:
			ImGui::Text("Default Text");
			break;
		}
		
		//texture.changeTexture(m_FilePath);
	}
	void TextureTest::fillItems()
	{
		for (int i = 0; i < m_filenames.size(); i++)
		{
			m_items[i] = (char*)m_filenames[i].c_str();
		}
	}
}