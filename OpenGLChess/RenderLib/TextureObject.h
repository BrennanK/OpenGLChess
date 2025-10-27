#pragma once
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
class TextureObject
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
	Shader so = Shader("../OpenGLChess/res/shaders/Basic.shader");
	Texture texture=Texture("../OpenGLChess/res/textures/kh3_box_art.jpg");


public:
	TextureObject();
	VertexArray& returnVa() { return va; }
	IndexBuffer& returnIb() { return ib; }
	Shader& returnSo() { return so; }
};