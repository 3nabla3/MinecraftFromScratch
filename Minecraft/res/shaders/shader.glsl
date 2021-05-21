#shader vertex
#version 440
layout(location = 0) in vec3 vertex;

uniform mat4 u_Projection;
uniform mat4 u_Translation;
uniform mat4 u_Rotation;
uniform mat4 u_Position;

out vec3 i_color;
	
void main()
{
	i_color = vertex;
	gl_Position = u_Projection * u_Rotation * u_Translation * u_Position * vec4(vertex.xyz, 1.0);
}


#shader fragment
#version 440
layout(location = 0) out vec4 color;

uniform float u_rChannel;

in vec3 i_color;
void main()
{
	color = vec4(u_rChannel, i_color.gb, 1);
}
