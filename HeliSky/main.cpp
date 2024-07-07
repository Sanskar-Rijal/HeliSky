#include<stdio.h>
#include<GL/glew.h>
#include<string.h>
#include<GLFW/glfw3.h>
//windows dimenstions
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;
/**void CreateTriangle()
{
	GLfloat verticies[] =
	{ -1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0,1.0f,0.0f,
	};//vertices of triangle 
	//creating out vao
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VAO==vertex array object,we need to create VBO==vertex buffer object
	//to go inside VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//connecting the vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);//it takes 4 values
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

}**/
int main()
{
	//intitalise GLFW
	if (!glfwInit())//checking for erros ,if it fails than perfom this
	{
		printf("GLFW INITIALISATION FAILED");
		glfwTerminate();
		return 1;
	}
	//setup GLFW WINDOWS PROPERTIES
	//OPENGL VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE profile == NO backwards Compability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//ALLOW forward compability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Glfw window creation failed!");
		glfwTerminate();
		return 1;
	}
	//Get Buffer size information
	int bufferWidth, bufferHeight;
	// i will use function in glfw to grab this value
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for glew to use
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	//initializing glew
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	//setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	// loop until window closed 
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();
		//clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//it clears fresh starts,clears everything
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);
	}
	return 0;
}