#include"Renderer.h"
#include<iostream>
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
		;
	}

}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[openGL error](" << error << ")" <<
			function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;

}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader&shader,unsigned int draw_type) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCALL(glDrawElements(draw_type, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	

}

void Renderer::Clear()const
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


}
