#pragma once
#include "Renderer.h"
class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Height, m_Width, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot=0)const;
	void Unbind()const;

	inline int Get_Width() { return m_Width; }
	inline int Get_Height() { return m_Height; }
};

