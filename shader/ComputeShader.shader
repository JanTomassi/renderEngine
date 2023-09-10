#version 430
layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_output;
uniform vec2 windowSize;
uniform mat4 m_proj;
uniform vec3 camera_position;
uniform vec3 camera_front;

// ray definition, with an origin point and a direction vector
float distance_from_sphere(in vec3 p, in vec3 c, float r)
{
	return length(p - c) - r;
}

// for unit cube, with better annotation
float cubeSDF(vec3 p) {
	// If d.x < 0, then -1 < p.x < 1, and same logic applies to p.y, p.z
	// So if all components of d are negative, then p is inside the unit cube
	vec3 d = abs(p) - vec3(1);

	// Assuming p is inside the cube, how far is it from the surface?
	// Result will be negative or zero.
	float insideDistance = min(max(d.x, max(d.y, d.z)), 0);

	// Assuming p is outside the cube, how far is it from the surface?
	// Result will be positive or zero.
	float outsideDistance = length(max(d, 0));

	return insideDistance + outsideDistance;
}

float map_the_world(in vec3 p)
{
	float sphere_0 = distance_from_sphere(p, vec3(0.0), 1);
	float cube_0 = cubeSDF(p);

	// Later we might have sphere_1, sphere_2, cube_3, etc...

	return sphere_0;
}

vec3 calculate_normal(in vec3 p)
{
	const vec3 small_step = vec3(0.001, 0.0, 0.0);

	float gradient_x = map_the_world(p + small_step.xyy) - map_the_world(p - small_step.xyy);
	float gradient_y = map_the_world(p + small_step.yxy) - map_the_world(p - small_step.yxy);
	float gradient_z = map_the_world(p + small_step.yyx) - map_the_world(p - small_step.yyx);

	vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

	return normalize(normal);
}

vec3 ray_march(in vec3 ro, in vec3 rd)
{
	float total_distance_traveled = 0.0;
	const int NUMBER_OF_STEPS = 128;
	const float MINIMUM_HIT_DISTANCE = 0.001;
	const float MAXIMUM_TRACE_DISTANCE = 1000.0;

	for (int i = 0; i < NUMBER_OF_STEPS; ++i)
	{
		vec3 current_position = ro + total_distance_traveled * rd;

		float distance_to_closest = map_the_world(current_position);

		if (distance_to_closest < MINIMUM_HIT_DISTANCE)
		{
			//return vec3(1.0, 1.0, 1.0);
			return calculate_normal(current_position) * 0.5 + 0.5;;
		}

		if (total_distance_traveled > MAXIMUM_TRACE_DISTANCE)
		{
			break;
		}
		total_distance_traveled += distance_to_closest;
	}
	return vec3(0.0);
}

void main() {
	// base pixel colour for image
	vec4 pixel = vec4(0.0, 0.0, 0.0, 1.0);

	// get index in global work group i.e x,y position
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	// get cordinet in [-1,1] range
	vec2 window_cordinate = (pixel_coords / windowSize) * 2 - 1;

	window_cordinate.x = -window_cordinate.x * (windowSize.x / windowSize.y);

	vec4 ro = vec4(camera_position, 1.0);
	vec4 rd = normalize(m_proj * vec4(window_cordinate, 1.0, 1.0));

	vec3 shaded_color = ray_march(ro.xyz, rd.xyz);

	// output to a specific pixel in the image
	imageStore(img_output, pixel_coords, vec4(shaded_color.xyz, 1.0));
}
