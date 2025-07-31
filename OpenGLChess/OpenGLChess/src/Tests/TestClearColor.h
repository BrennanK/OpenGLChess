#pragma once
#include "Test.h"

namespace test // Remeber to override from a class inside a namespace we have to have it in that same namespace
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		virtual ~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void onRenderer() override;
		void OnImGuiRenderer() override;

	private:
		float m_Color[4];
	};
}
