#include "TestScaleTexture.h"
#include "../Renderer.h"
#include <imgui/imgui.h>
namespace test
{
	TestScaleTexture::TestScaleTexture():m_ScaleValue(2.0f)
	{
	}

	TestScaleTexture::~TestScaleTexture()
	{
	}

	
	data TestScaleTexture::OnUpdate(float deltaTime,unsigned int& vao ,VertexArray* va, VertexBuffer* vb,VertexBufferLayout& layout, float(&positions)[16], int size)
	{
		/*	To Do:
		*		Clear Vertex Array
		*		Make new Vertex Buffer
		*		Unbind/Rebind
				Re-add Vertex Buffer to Vertex Array
		*/
		
		data returnValue{};

		for (int i = 0; i < size; i++)
		{
			if (i % 4 == 0 || i % 4 == 1)
			{
				positions[i] = 50.0f * m_ScaleValue;
			}
			returnValue.points[i] = positions[i];
		}
		
		//va->DeleteArray();
		//va->Unbind();

		//*va = VertexArray();

		//vb->DeleteBuffer();
		//vb->Unbind();

		//*vb = VertexBuffer(returnValue.points, 4 * 4 * sizeof(float));
		//va->clearVertexAttributeArray(layout,vao);
		//va->AddBuffer(*vb, layout);

		vb->ChangeData(positions,4*4*sizeof(float));
		return returnValue;
		
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

