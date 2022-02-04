#version 460
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 m_normal;

out vec4 normal;

uniform mat4 m_porj;
uniform mat4 m_tran;

void main() {
	normal = m_tran * m_normal;
	gl_Position = m_porj * m_tran * position;
}
