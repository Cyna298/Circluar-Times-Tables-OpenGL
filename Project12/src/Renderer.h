#pragma once
#include<GL/glew.h>
#include"VertexArray.h"
#include"IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader&shader, unsigned int draw_type)const;
	void Clear()const;
};
