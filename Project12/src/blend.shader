#shader vertex

#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP*position;
	fragmentColor = vertexColor;
};


#shader fragment

#version 330 core
layout(location = 0) out vec4 color;
in vec4 fragmentColor;
void main()
{
	
	color = vec4(0.5,0.5,0.8,1.0);

};