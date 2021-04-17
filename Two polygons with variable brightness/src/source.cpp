#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <ShaderProgram.h>

std::vector<float> poly_1;
std::vector<float> poly_2;
std::vector<unsigned int> indices;
std::vector<unsigned int> indices_2;

GLuint VBO;
GLuint EBO;
GLuint VAO[2];
static bool wireframe = false;
//float intensity = sin(x) * 0.5f + 0.5f;
float intensity = 0.2f;

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight) {
	glViewport(0, 0, givenWidth, givenHeight);
}

// Dhmioyrgoyme ena inpupt apo to plhktrologioy opoy opote patame to escape tha kleinei to parathiro
void ProcessInput(GLFWwindow* givenWindow, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(givenWindow, GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (!wireframe) {
			wireframe = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			wireframe = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		intensity += 0.1f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		intensity -= 0.1f;
	}
	if (intensity >= 1)
		intensity = 1;
	if (intensity <= 0)
		intensity = 0;
}



void polygons() {
	poly_1 =
	{
		 0.1f, -0.4f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.6f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.9f, -0.4f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.7f, -0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.1f, -0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
	};


	poly_2 =
	{
		0.8f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.7f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.7f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	};

	indices =
	{
		0, 1, 2, 3, 4, 5
	};

	indices_2 =
	{
		0, 1, 2, 3, 4, 5, 6, 7
	};
}


GLuint InitObject(const std::vector<float> vertices, bool use_indices, const std::vector<unsigned int> indices, bool colour) {

	if (colour == true) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float))); // 3*sizeof float opw kai prin apla twra ksekinaem apo thn trith thesh dhladh 3*sizeof float
		glEnableVertexAttribArray(1);
	}
	else {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

	}
	if (use_indices == true) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	}
	return VBO;
}



int main() {

	// Arxikopoihsh twn synartisewn mas 

	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return EXIT_FAILURE; // Pisteuw to idio me return -1;
	}

	// Parathiro

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL exercise 1", NULL, NULL);

	if (!window) {
		std::cout << "Failed to initialize the window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// Setaroume thn Callback synarthsh
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize glew" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Telos h arxikopoihsh

	// Eisagwgh twn pinakwn me tiw syntegamenes twn antikeimenwn
	polygons();

	Shader shaderProgram("res/Shaders/VertexShader.glsl", "res/Shaders/FragmentShader.glsl"); //kaloyme thn klash

	// Me glPolygonMode kai thn epilogh GL_LINE provaloyme mono to perigrama toy object mas kai me thn glLineWidth peirazoyme to paxos twn gramwn
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glLineWidth(10.0f);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(2, VAO);

	// first object into first VAO
	glBindVertexArray(VAO[0]);
	InitObject(poly_1, true, indices, true);
	glBindVertexArray(0);

	// second object in second VAO
	glBindVertexArray(VAO[1]);
	InitObject(poly_2, true, indices_2, true);
	glBindVertexArray(0);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSetKeyCallback(window, ProcessInput); // Kaloume thn processinput gia na exoume anadrash me ta plhktra 

		//ProcessInput(window); 

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		// Render Using the shader program
		shaderProgram.use();


		glBindVertexArray(VAO[0]);
		glDrawElements(GL_POLYGON, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//float time = glfwGetTime();
		//float intensity = sin(time) *0.5f + 0.5f; ////////// KANONIKOPOIHSH [0,1]

		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "intensity");
		glUniform1f(uniformLocation, intensity);

		glBindVertexArray(VAO[1]);
		glDrawElements(GL_POLYGON, indices_2.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate(); //Panta terminate thn glfw
	return EXIT_SUCCESS; //To idio me return 0;
}