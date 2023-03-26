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
"	FragColor = vec4(1.0f,0.3f,0.5f,1.0f);\n"
"}\n\0";

int main() {
	//Creating Window With OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Vertices for the triangle
	GLfloat vertices[] = {
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,//Creating Vertices of a triangle
		0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
		0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL Testing", NULL, NULL);

	glfwMakeContextCurrent(window);
	
	gladLoadGL();//GLAD loads needed configs for OpenGL

	glViewport(0, 0, 800, 800);
	//using Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//adding vertex shader in source
	glCompileShader(vertexShader); //sending values to compiler for vertex shader

	//Using Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//adding vertex shader in source
	glCompileShader(fragmentShader); //sending values to compiler for vertex shader

	GLuint shaderProgram = glCreateProgram(); //program to both shaders working together

	//attaching two shaders
	glAttachShader(shaderProgram, vertexShader); ///attaching shader to shaderProgram
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	//Deleting shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//we send data from CPU to GPU with batches, called buffers
	//Create reference for the vertex array object and the vertex buffer
	GLuint VAO, VBO;
	//Generate VAO and VBO with one object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Make the VAO the current Array object by binging it
	glBindVertexArray(VAO);
	
	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Configure the vertex attribute so that opengl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the vertex attribute so that opengl knows to use it
	glEnableVertexAttribArray(0);

	//bind both VBO and VAO to 0 so we don't accidently modify the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//This line sets the clear color, which is used to clear the color buffer when glClear() is called
	glClear(GL_COLOR_BUFFER_BIT);//This line clears the color buffer using the clear color specified by glClearColor()
	glfwSwapBuffers(window);//Swaps the first and Back Buffers in the window


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which shader program to use
		glUseProgram(shaderProgram);
		//Bind the VAO so openGL knows to use
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		//Takecare of GLFW events
		glfwPollEvents();
	}
	//Delete all objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}