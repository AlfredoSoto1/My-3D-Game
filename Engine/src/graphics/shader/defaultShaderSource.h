#pragma once

#ifdef _DEFAULT_SHADER_SOURCE

const char* defaultVertexSource = R"(

#shader vertex
#version 330 core

layout(location = 0) in  vec2 position;

void main(void) {
	gl_Position = vec4(position, 0.0, 1.0);
}

)";

const char* defaultFragmentSource = R"(

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main(void) {
	color = vec4(1.0);
}

)";

#endif // !_DEFAULT_SHADER_SOURCE

