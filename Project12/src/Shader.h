#pragma once
#include<string>
#include<unordered_map>
#include "glm/ext/matrix_transform.hpp"
struct ShaderProgramSource
{
	std::string VertexSrc;
	std::string FragmentSrc;

};
class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind()const;
	//set uniforms
	void SetUnifrom1i(const std::string& name, int value);
	void SetUnifrom1f(const std::string& name, int value);
	void SetUnifrom3f(const std::string& name, float f0, float f1, float f2);
	void SetUnifrom4f(const std::string& name,float v0,float v1,float f2,float f3);
	void SetUnifromMat4f(const std::string& name, const glm::mat4 matrix);


private:
	 int GetUnifromLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

