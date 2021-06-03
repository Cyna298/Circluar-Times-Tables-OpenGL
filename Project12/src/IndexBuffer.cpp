#include"IndexBuffer.h"

#include"Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count),m_RendererID(0)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCALL(glGenBuffers(1, &m_RendererID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_DYNAMIC_DRAW));

}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
