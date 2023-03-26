#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\0";

int main() {
	//Creating Window With OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,//Creating Vertices of a triangle
		0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
		0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL Testing", NULL, NULL);

	glfwMakeContextCurrent(window);
	
	gladLoadGL();//GLAD loads needed configs for OpenGL+

	glViewport(0, 0, 800, 800);
	//using Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//adding vertex shader in source
	glCompileShader(vertexShader); //sending values to compiler for vertex shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//adding vertex shader in source
	glCompileShader(fragmentShader); //sending values to compiler for vertex shader

	GLuint shaderProgram = glCreateProgram(); //program to both shaders working together

	glAttachShader(shaderProgram, vertexShader); ///attaching shader to shaderProgram
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//we send data from CPU to GPU with batches, called buffers
	GLuint VAO, VBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//This line sets the clear color, which is used to clear the color buffer when glClear() is called
	glClear(GL_COLOR_BUFFER_BIT);//This line clears the color buffer using the clear color specified by glClearColor()
	glfwSwapBuffers(window);//Swaps the first and Back Buffers in the window


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}