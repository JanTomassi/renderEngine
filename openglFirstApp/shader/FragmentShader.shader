#version 460

in vec4 normal;

layout(location = 0) out vec4 color;

void main() {
	float intensity = clamp(dot(normal, normalize(vec4(.5,-1,0,0))), 0, 1) + clamp(dot(normal, normalize(vec4(-.5, -1, 0, 0))), 0, 1);
	color = vec4(1.0, 0.8078431372549019607843137254902, 0.70588235294117647058823529411765, 1.0) * intensity;
}
