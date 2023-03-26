#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	//Creating Window With OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL Testing", NULL, NULL);

	glfwMakeContextCurrent(window);
	
	gladLoadGL();//GLAD loads needed configs for OpenGL
	glViewport(0, 0, 800, 800);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//This line sets the clear color, which is used to clear the color buffer when glClear() is called
	glClear(GL_COLOR_BUFFER_BIT);//This line clears the color buffer using the clear color specified by glClearColor()
	glfwSwapBuffers(window);//Swaps the first and Back Buffers in the window


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}