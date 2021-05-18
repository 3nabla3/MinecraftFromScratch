#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 u_Projection;
uniform mat4 u_Translation;
uniform mat4 u_Rotation;

out vec3 i_color;
	
void main()
{
	i_color = position;
	gl_Position = u_Projection * u_Rotation * u_Translation * vec4(position.xyz, 1.0);
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
	
in vec3 i_color;
void main()
{
	color = vec4(i_color, 0.5);
}
