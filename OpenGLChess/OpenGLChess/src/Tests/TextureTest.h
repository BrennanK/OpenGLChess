#pragma once
#include "Test.h"
#include <string>
#include "Texture.h"
#include <vector>
namespace test
{
	static int m_currentItem=0;
	enum SelectionMode{TextBox, ScollableList};
	class TextureTest: public Test
	{
	public:
		TextureTest();
		~TextureTest();
		void OnUpdate(float deltaTime) override;
		void onRenderer() override;
		void OnImGuiRenderer(Texture& texture);
		void fillItems();
	private:

		std::string m_FileName;
		std::string m_FilePath;
		std::vector<std::string> m_filenames;
		char* m_items[36];
		SelectionMode m_mode= SelectionMode::TextBox;
		int m_modeInt = 0;
	};
}

