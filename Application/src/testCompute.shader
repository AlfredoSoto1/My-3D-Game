#shader compute

#version 430

layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba8, binding = 0) uniform image2D img_output;

float random(vec2 st) {
	return fract(sin(dot(st.xy,
		vec2(12.9898, 78.233))) *
		43758.5453123);
}

void main() {

	// base pixel colour for image
	vec4 pixel = vec4(1.0, 1.0, 1.0, 1.0);
	// get index in global work group i.e x,y position
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	//
	// interesting stuff happens here later
	//

	// output to a specific pixel in the image
	imageStore(img_output, pixel_coords, vec4(random(pixel_coords), random(pixel_coords), random(pixel_coords), 1.0));


	//// get index in global work group i.e x,y position
	//ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	//ivec2 imgResolution = imageSize(img_output);
	//float width = imgResolution.x;
	//float height = imgResolution.y;

	//// base pixel colour for image
	//vec4 pixel = vec4(pixel_coords.x / width, pixel_coords.y / height, 0.0, 1.0);
	////  vec4 pixel2 = vec4(pixel_coords.x / width, pixel_coords.y / height, 1.0, 1.0);
	//  //
	//  // interesting stuff happens here later
	//  //

	//  // output to a specific pixel in the image
	//imageStore(img_output, pixel_coords, vec4(1.0));

	////  imageStore(img_output2, pixel_coords, pixel2);
}