#pragma once
#include "Test.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Renderer.h"
namespace test
{
	class TestScaleTexture: public Test
	{
	public:
		TestScaleTexture();
		~TestScaleTexture();
		void OnUpdate(float deltaTime) override;
		void onRenderer(Renderer& renderer, VertexArray& va,  IndexBuffer& ib,  Shader& shader);
		void OnImGuiRenderer() override;

	private:
		float m_ScaleValue;
	};
}


