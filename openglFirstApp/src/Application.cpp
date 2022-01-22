#include "Application.h"

#include <fstream>

std::string vs = R"glsl(
		#version 460
		layout(location = 0) in vec4 position;
		void main(){
			gl_Position = position;
		}
		)glsl";
std::string fs = R"glsl(
		#version 460
		layout(location = 0) out vec4 color;

		void main(){
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}
		)glsl";

int main(void)
{
	std::ifstream in("C:\\Users\\jangi\\Downloads\\chat.stl", std::ios::binary);

	char c;
	while (in.get(c))
	{
		std::cout << c;
	}

	//GLFWwindow* window;
	///* Initialize the library */
	//GLCALL(glfwInit());

	//GLCALL(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE));
	////glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	///* Create a windowed mode window and its OpenGL context */
	//window = GLCALL(glfwCreateWindow(640, 480, "Hello World", NULL, NULL));

	//GLCALL(test_window_creation(window));

	//glfwSwapInterval(5);
	//GLCALL(glEnable(GL_DEPTH_TEST));

	//// Enable debug output
	//GLCALL(glEnable(GL_DEBUG_OUTPUT));
	//GLCALL(glDebugMessageCallback(MessageCallback, 0));

	//float positions[9] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 1.5f
	//};

	//GLuint vao = 0;
	//GLCALL(glGenVertexArrays(1, &vao));
	//GLCALL(glBindVertexArray(vao));

	//unsigned int buffer;
	//GLCALL(glGenBuffers(1, &buffer));
	//GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	//GLCALL(glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW));

	//GLCALL(glEnableVertexAttribArray(0));
	//GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

	//shader base_shader = shader(vs, fs);
	//base_shader.useShader();

	///* Loop until the user closes the window */
	//while (!glfwWindowShouldClose(window))
	//{
	//	/* Render here */
	//	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT););

	//	GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));

	//	/* Swap front and back buffers */
	//	GLCALL(glfwSwapBuffers(window));

	//	/* Poll for and process events */
	//	GLCALL(glfwPollEvents());
	//}

	//GLCALL(glfwTerminate());
	return 0;
}