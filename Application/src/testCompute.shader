#shader compute

#version 430

layout(local_size_x = 16, local_size_y = 16) in;
layout(rgba8, binding = 0) uniform image2D img_output;

layout(std430, binding = 0) buffer layoutName
{
	vec4 randomColor;
} LAYOUT;

float random(vec2 st) {
	return fract(sin(dot(st.xy,
		vec2(12.9898, 78.233))) *
		43758.5453123);
}

void main() {


	ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
	ivec2 imageResolution = imageSize(img_output);
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

	vec2 normalizedPixelCoords = vec2((float(pixelCoords.x) / imageResolution.x) * 2.0 - 1.0, (float(pixelCoords.y) / imageResolution.y) * 2.0 - 1.0);
	

	// get index in global work group i.e x,y position
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	// base pixel colour for image
	ivec2 imgResolution = imageSize(img_output);
	float width = imgResolution.x;
	float height = imgResolution.y;
	vec4 pixel = vec4(pixel_coords.x / width, pixel_coords.y / height, 0.0, 1.0);

	pixel = vec4(0.0, 0.0, 0.0, 1.0);
	pixel = vec4(normalizedPixelCoords , 0.0, 1.0);
	
	//
	// interesting stuff happens here later
	//

	float max_x = 5.0;
	float max_y = 5.0;
	ivec2 dims = imageSize(img_output); // fetch image dimensions
	float x = (float(pixel_coords.x * 2 - dims.x) / dims.x);
	float y = (float(pixel_coords.y * 2 - dims.y) / dims.y);
	vec3 ray_o = vec3(x * max_x, y * max_y, 0.0);
	vec3 ray_d = vec3(0.0, 0.0, -1.0); // ortho

	vec3 sphere_c = vec3(0.0, 0.0, -10.0);
	float sphere_r = 1.0;

	vec3 omc = ray_o - sphere_c;
	float b = dot(ray_d, omc);
	float c = dot(omc, omc) - sphere_r * sphere_r;
	float bsqmc = b * b - c;
	// hit one or both sides
	if (bsqmc >= 0.0) {
		//pixel = vec4(0.4, 0.4, 1.0, 1.0);
		pixel = LAYOUT.randomColor;
	}
	

	//  vec4 pixel2 = vec4(pixel_coords.x / width, pixel_coords.y / height, 1.0, 1.0);
	//
	// interesting stuff happens here later
	//

	// output to a specific pixel in the image
	imageStore(img_output, pixel_coords, pixel);
	//imageStore(img_output, pixel_coords, vec4(random(pixel_coords), random(pixel_coords), random(pixel_coords), 1.0));
}