#include "TransformTest.h"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
namespace test
{
	TransformTest::TransformTest(TextureObject* o): obj(o)
	{
		testTranslation=obj->returnTransform().returnTranslation();
	}
	void TransformTest::OnUpdate(float deltaTime)
	{
		obj->updateTransform(testTranslation);
	}
	void TransformTest::onRenderer()
	{
	}
	void TransformTest::OnImGuiRenderer()
	{
		ImGui::SliderFloat3("Translation", &testTranslation.x, 0.0f, 1280.0f);
	}
}


