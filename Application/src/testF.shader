#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 out_textureCoords;

uniform sampler2D u_texture;

uniform vec4 u_Color;

void main(void) {
	color = texture(u_texture, out_textureCoords);
	//color = vec4(out_textureCoords, 0.0, 1.0);
	//color = u_Color;
}
