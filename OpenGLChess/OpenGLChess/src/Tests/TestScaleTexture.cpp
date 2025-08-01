#include "TestScaleTexture.h"
#include "../Renderer.h"
#include <imgui/imgui.h>
namespace test
{
	TestScaleTexture::TestScaleTexture():m_ScaleValue(1.0f)
	{
	}

	TestScaleTexture::~TestScaleTexture()
	{
	}

	void TestScaleTexture::OnUpdate(float deltaTime)
	{
		/*	To Do:
		*		Clear Vertex Array
		*		Make new Vertex Buffer
		*		Unbind/Rebind
				Re-add Vertex Buffer to Vertex Array
		*/
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

