#include "TestScaleTexture.h"
#include "../Renderer.h"
#include <imgui/imgui.h>
namespace test
{
	TestScaleTexture::TestScaleTexture(float(&positions)[16],int count):m_ScaleValue(2.0f),m_count(count)
	{
		for (int i = 0; i < count; i++)
		{
			m_scaledPositions[i] = positions[i];
		}
	}

	TestScaleTexture::~TestScaleTexture()
	{
	}

	
	void TestScaleTexture::OnUpdate(float deltaTime, float* positions, int size)
	{
		/*	To Do:
		*		Clear Vertex Array
		*		Make new Vertex Buffer
		*		Unbind/Rebind
				Re-add Vertex Buffer to Vertex Array
		*/
		
		float scaledPositions[16];

		for (int i = 0; i < size; i++)
		{
			if (i % 4 == 0 || i % 4 == 1)
			{
				//newPositions[i] = positions[i] * m_ScaleValue;
				m_scaledPositions[i] = positions[i] * m_ScaleValue;
			}
			//returnValue.points[i] = positions[i];
		}
		//vb->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), m_scaledPositions);
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float),positions);
		//return returnValue;
		
	}

	void TestScaleTexture::onRenderer(Renderer& renderer,VertexArray& va,IndexBuffer& ib, Shader& shader)
	{
		renderer.Draw(va, ib, shader);
	}

	

	void TestScaleTexture::OnImGuiRenderer()
	{
		ImGui::SliderFloat("Scale", &m_ScaleValue, 1.0f, 3.0f);
	}
}

