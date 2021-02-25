#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
uniform mat4 u_Translation;
uniform mat4 u_Rotation;
	
void main()
{
	gl_Position = u_Translation * u_Rotation * position;
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
	
void main()
{
	color = vec4(0.2, 0.5, 0.8, 1.0);
}