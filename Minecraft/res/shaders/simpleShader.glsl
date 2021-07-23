#shader vertex
#version 440
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 i_color;
out vec2 i_texCoord;

void main()
{
	i_color = color;
	i_texCoord = texCoord;
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
}


#shader fragment
#version 440
layout(location = 0) out vec4 color;

in vec3 i_color;
in vec2 i_texCoord;

uniform float u_rChannel;
uniform sampler2D image;

void main()
{
	color = vec4(u_rChannel, i_color.gb, 0.5);
	//color = texture(image, i_texCoord);
}
