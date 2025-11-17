#pragma once
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderTransform.h"
class TextureObject2
{
private:
	float m_vertexPositions[16]{
			-150.0f,-150.0f, 0.0f,0.0f,//0
			150.0f,-150.0f, 1.0f, 0.0f, //1
			150.0f,150.0f,  1.0f,1.0f, //2
			-150.0f,150.0f, 0.0f,1.0f };
	unsigned int indices[6] // array of indices points such that we can draw multiple triangles without having to store duplicate positions
	{
		0,1,2,
		2,3,0
	};
	VertexArray va;
	VertexBuffer vb = VertexBuffer(m_vertexPositions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	IndexBuffer ib = IndexBuffer(indices, 6);
	Shader so = Shader("../OpenGLChess/res/shaders/Basic2.shader");
	Texture texture = Texture("../OpenGLChess/res/textures/nice gear.jpg");
	RenderTransform rt;

public:
	TextureObject2();
	VertexArray& returnVa() { return va; }
	IndexBuffer& returnIb() { return ib; }
	Shader& returnSo() { return so; }
	RenderTransform returnTransform() { return rt; }

	void updateTransform(glm::vec3 newTranslation);
	void updateTexture(std::string& filePath, unsigned int slot);
};