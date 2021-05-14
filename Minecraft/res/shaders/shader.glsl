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
	gl_Position = u_Projection * u_Translation * u_Rotation * vec4(position.x, position.y, position.z, 1.0);
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
	
in vec3 i_color;
void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
