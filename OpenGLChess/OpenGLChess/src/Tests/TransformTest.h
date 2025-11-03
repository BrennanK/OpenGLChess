#pragma once
#include "Test.h"
#include "TextureObject.h"
#include "RenderTransform.h"

namespace test
{
	class TransformTest : public Test
	{
	private:

		glm::vec3 testTranslation;
		TextureObject* obj;

	public:
		TransformTest() = default;

		TransformTest(TextureObject* o);

		void OnUpdate(float deltaTime) override;
		void onRenderer() override;
		void OnImGuiRenderer() override;
	};
}

