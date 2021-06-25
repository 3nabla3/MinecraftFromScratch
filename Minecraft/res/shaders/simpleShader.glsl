#shader vertex
#version 440
layout(location = 0) in vec2 vertex;

void main()
{
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
}


#shader fragment
#version 440
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 0.0, 1.0);
}
