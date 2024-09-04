#include<stdio.h>
#include<GL/glew.h>
#include<string.h>
#include<GLFW/glfw3.h>
//windows dimenstions
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;
//making external shades
//vertex shader
static const char* vshader = "                          \n\
#version 330                                                \n\
layout(location =0) in vec3 pos;                             \n\
void main()                                                 \n\
{                                                           \n\
    gl_Position= vec4(0.4 * pos.x,0.4 * pos.y,pos.z,1.0);               \n\
}";
//fragment shader
static const char* fshader = "                          \n\
#version 330                                                \n\
out vec4 colour;                           \n\
void main()                                                 \n\
{                                                           \n\
    colour = vec4(0.0f,1.0f,0.0f,1.0f);               \n\
}";
void CreateTriangle()
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
	//to go inside VBO we use  buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//connecting the vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);//it takes 4 values
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);//unbinding it 
}
void Addshader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theshader = glCreateShader(shaderType);

	const GLchar* thecode[1];

	thecode[0] = shaderCode;

		GLint codelength[1];
		codelength[0] = strlen(shaderCode);

		glShaderSource(theshader, 1, thecode, codelength);
		glCompileShader(theshader);

		GLint result = 0;
		GLchar elog[1024] = { 0 };

		glGetShaderiv(theshader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(theshader, sizeof(elog), NULL, elog);
			printf("Error linking program %d shader:'%s'\n ", shaderType,elog);
			return;
		}

		glAttachShader(theProgram, theshader);

}
void CompileShaders()
{
	shader = glCreateProgram();//creates program and give it a id
		if(!shader)
		{
			printf("error creating shader in program ");
			return;
		}
		//addd shader to the program we create a seperate function void shader
		Addshader(shader, vshader, GL_VERTEX_SHADER);
		Addshader(shader, fshader, GL_FRAGMENT_SHADER);

		//place to work on errors
		GLint result = 0;
		GLchar elog[1024] = { 0 };


		glLinkProgram(shader);

		glGetProgramiv(shader, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
			printf("error linking program '%s'\n", elog);
			return;
		}


		glValidateProgram(shader);
		glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
			printf("error validating program '%s'\n", elog);
			return;
		}
}
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

	CreateTriangle();
	CompileShaders();

	// loop until window closed 
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get + handle user input events
		glfwPollEvents();
		//clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//it clears fresh starts,clears everything
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3); 

		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}