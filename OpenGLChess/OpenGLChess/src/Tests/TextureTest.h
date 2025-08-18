#pragma once
#include "Test.h"
#include <string>
#include "../Texture.h"
namespace test
{
	class TextureTest: public Test
	{
	public:
		TextureTest();
		~TextureTest();
		void OnUpdate(float deltaTime) override;
		void onRenderer() override;
		void OnImGuiRenderer(Texture& texture);
	private:

		std::string m_FileName;
		std::string m_FilePath;
	};
}

