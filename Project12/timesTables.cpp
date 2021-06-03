
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include <math.h>

#define PI 3.14159265
#define TEN 100

void timesTables(std::vector<float> & arr, std::vector<unsigned int> & indx, int nop, float table,bool firstTime)
{

	
	
	nop = nop * TEN;
	if (firstTime)
	{
		float angle = 0;
		float angleDelta = (2 * PI) / nop;
		float r = 1;
		float x;
		float y;
		for (int i = 0; i < nop; i++)
		{
			x = r * cos(i * angleDelta);
			y = r * sin(i * angleDelta);
			arr.push_back(x);
			arr.push_back(y);
			angle += angleDelta;
		}

	}
	int inc = 0;
	for (int i = 0; i < nop; i++)
	{

		indx.push_back(inc % nop);
		indx.push_back((inc + 1) % nop);

		inc += 1;

	}
	int tab = table * TEN;
	for (int i = 0; i < nop / TEN; i += 1)
	{

		indx.push_back(i * TEN);
		indx.push_back((i * tab) % nop);

	}

}
int main()
{
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		if (!glfwInit())
			exit(EXIT_FAILURE);
		GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glewInit();
		//glfwSwapInterval(4);
		

		float buff[12] =
		{
			0.5,0.5,
			-0.5,0.5,
			-0.5,-0.5,
			0.5,-0.5

		};
		unsigned int ind[6] =
		{
			0,1,2,2,3,0
		};

		Shader sh("b.shader");
		sh.Bind();
		sh.SetUnifrom4f("u_color", 1.0, 1.0, 1.0, 0.0);
		Renderer ren;
		float w = 0.01;
		float h = 0;
		float breathe = 1.0f;
		float tab = 0;
		bool first = true;
		std::vector<float>arr;
		
		while (!glfwWindowShouldClose(window))
		{
			std::vector<unsigned int>indx;
			timesTables(arr, indx, 200, tab,first);
			VertexBuffer vbo(arr.data(), arr.size() * sizeof(float));
			vbo.Bind();
			
			IndexBuffer ibo(indx.data(), indx.size());

			ibo.Bind();
			VertexBufferLayout layout;
			layout.Push<float>(2);
			VertexArray va;
			va.AddBuffer(vbo, layout);
			va.Bind();

			ren.Clear();
			ren.Draw(va, ibo, sh, GL_LINES);

			first = false;
			tab += 0.01;

			sh.SetUnifrom4f("u_color", 1.0 - h, 0.0 + h, 1.0f - breathe * h * 100,1);

			h += 0.001;
			
			if ((1.0f - breathe * h*100) < 0.0)
			{
				breathe = -1.0f;
			}
			else if ((1.0f - breathe * h*100) > 1)
			{
				breathe = 1.0f;
			}


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;



}