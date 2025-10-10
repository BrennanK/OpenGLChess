#include "TestClearColor.h"
#include "Renderer.h"
#include <imgui/imgui.h>
#include <iostream>
namespace test
{
	TestClearColor::TestClearColor() : m_Color{0.2f, 0.3f, 0.8f, 1.0f},m_Color_cache{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
		GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	TestClearColor::~TestClearColor()
	{
	
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}

	void TestClearColor::onRenderer()
	{
		if (m_Color[0] == m_Color_cache[0] && m_Color[1] == m_Color_cache[1] && m_Color[2] == m_Color_cache[2] && m_Color[3] == m_Color_cache[3])
		{
			return;
		}
		else
		{
			GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			for (int i = 0; i < 4; i++)
			{
				m_Color_cache[i] = m_Color[i];
			}
		}
		
	}

	void TestClearColor::OnImGuiRenderer()
	{
		ImGui::ColorEdit4("Clear Color", m_Color);
	}

}
