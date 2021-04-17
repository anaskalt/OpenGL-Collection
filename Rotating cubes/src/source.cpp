#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderProgram.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}

int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Lab3", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Data


	GLfloat vertices[] = {
		//position            //color             
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),

	};


	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader shaderProgram("res/Shaders/VertexShader.glsl", "res/Shaders/FragmentShader.glsl"); //kaloyme thn klash

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		float time = glfwGetTime();

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Using the shader program
		shaderProgram.use();

		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(0.0f, -5.0f, -20.0f));
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection;

		// 3D
		projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.3f, 100.0f);

		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		for (int i = 0; i < 3; i++)
		{
			glm::mat4 model;
			// AM -->> 57271 cube[0] -> 1.2 cube[1] -> 1.7 cube[3] -> 1.1


				model = glm::translate(identity, cubePositions[i]);

				if (i == 0) {
					model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 1.0f, 0.0f)); //gyrw apo ton eayto toy
					model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
				}

				if (i == 1) {
					model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(1.0f, 1.0f, 0.0f))* glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 0.5f, 0.0f)); // gyrw apo ton 0 
					//model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 0.0f, 0.1f)); //gyrw apo ton eayto toy
					model = glm::scale(model, glm::vec3(1.7f, 1.7f, 1.7f));
				}

				if (i == 2) {
					model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(1.0f, 1.0f, 0.0f))* glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(1.0f, 1.0f, 0.0f))* glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 0.2f, 0.0f)); // gyrw apo ton 0 
					//model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 0.0f, 0.1f)); // gyrw apo ton 1 
					//model = glm::rotate(model, glm::radians(90.0f) * time, glm::vec3(0.0f, 0.0f, 0.5f)); //gyrw apo ton eayto toy
					model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
				}

			int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
