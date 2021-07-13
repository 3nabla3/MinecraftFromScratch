#shader vertex
#version 440
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec3 color;

out vec3 i_color;

void main()
{
	i_color = color;
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
}


#shader fragment
#version 440
layout(location = 0) out vec4 color;

in vec3 i_color;

void main()
{
	color = vec4(i_color, 0.5);
}
