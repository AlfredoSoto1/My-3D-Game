//#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 out_textureCoords;
in vec3 out_normal;

uniform sampler2D u_texture;

uniform vec4 u_Color;

void main(void) {

	vec3 surfaceNormal = out_normal;
	vec3 lightDirection = vec3(0.0, 1.0, 0.0);
	vec3 lightColor = vec3(1.0);
	float brightness = 0.2;

	float nDotl = max(dot(surfaceNormal, lightDirection), 0.0);
	vec3 totalDiffuse = nDotl * lightColor;
	totalDiffuse = max(totalDiffuse, brightness);

	color = texture(u_texture, out_textureCoords);

	color = color * vec4(totalDiffuse, 1.0);

	//color = vec4(out_textureCoords, 0.0, 1.0);
	//color = u_Color;
}
