#pragma once
#include "Test.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Renderer.h"
#include "../VertexBufferLayout.h"

struct data
{
	float points[16];
};

namespace test
{

	class TestScaleTexture: public Test
	{
	public:
		TestScaleTexture();
		~TestScaleTexture();
		data OnUpdate(float deltaTime, unsigned int& vao, VertexArray* va, VertexBuffer* vb, VertexBufferLayout& layout, float(&positions)[16], int size);
		void onRenderer(Renderer& renderer, VertexArray& va,  IndexBuffer& ib,  Shader& shader);
		void OnImGuiRenderer() override;

	private:
		float m_ScaleValue;
	};
}


