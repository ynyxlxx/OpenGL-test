#include "libs.h"
using namespace std;

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint &program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	string temp = "";
	string src = "";

	fstream input_file;

	//vertex shader
	input_file.open("vertex_shader.glsl");
	if (input_file.is_open())
	{
		while (getline(input_file, temp))
			src += temp + "\n";
	}
	else {
		cout << "ERROR::LOADING_SHADER::COULD_NOT_OPEN_VERTEX_FILE." << "\n";
		loadSuccess = false;
	}

	input_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{	
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::LOADING_SHADER::COULD_NOT_COMPILE_VERTEX_SHADER." << "\n";
		cout << infoLog << "\n";
		loadSuccess = false;
	}

	//fragment shader
	temp = "";
	src = "";

	input_file.open("fragment_shader.glsl");
	if (input_file.is_open())
	{
		while (getline(input_file, temp))
			src += temp + "\n";
	}
	else {
		cout << "ERROR::LOADING_SHADER::COULD_NOT_OPEN_FRAGMENT_FILE." << "\n";
		loadSuccess = false;
	}

	input_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::LOADING_SHADER::COULD_NOT_COMPILE_FRAGMENT_SHADER." << "\n";
		cout << infoLog << "\n";
		loadSuccess = false;
	}

	//program
	program = glCreateProgram();
	
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		cout << "ERROR::LOADING_SHADER::COULD_NOT_LINK_PROGRAM." << "\n";
		cout << infoLog << "\n";
		loadSuccess = false;
	}

	//end
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

int main()
{
	//init glfw
	glfwInit();

	//create window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
	

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "first try", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	/*glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);*/

	glfwMakeContextCurrent(window); //important.

	//init glew.(needs window and opengl context)
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "ERROR::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
	
	//init shader
	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();


	//main loop

	while (!glfwWindowShouldClose(window))
	{
		//Update Input
		glfwPollEvents();

		//Update 

		///DRAW
		
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Draw

		//End Draw
		glfwSwapBuffers(window);
		glFlush();
	}


	//end of program
	glfwTerminate();


	return 0;
}