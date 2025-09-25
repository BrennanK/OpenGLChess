#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct data
{
	float points[16];
};

namespace test
{

	class TestScaleTexture: public Test
	{
	public:
		TestScaleTexture(float(&positions)[16],int count);
		~TestScaleTexture();
		void OnUpdate(float deltaTime, float* positions, int size);
		void onRenderer(Renderer& renderer, VertexArray& va,  IndexBuffer& ib,  Shader& shader);
		void OnImGuiRenderer() override;

	private:
		float m_ScaleValue;
		int	  m_count;
		float m_scaledPositions[16];
		
	};
}


