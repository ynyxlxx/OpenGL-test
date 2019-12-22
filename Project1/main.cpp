#include "libs.h"

Vertex vertices[] =
{
	//position						//color							// texcoord					//normal
	glm::vec3(-0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 3, //triangle 1
	1, 2, 3  //triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint& program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::fstream input_file;

	//vertex shader
	input_file.open("shader/vertex_shader.glsl");
	if (input_file.is_open())
	{
		while (getline(input_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR::LOADING_SHADER::COULD_NOT_OPEN_VERTEX_FILE." << "\n";
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
		std::cout << "ERROR::LOADING_SHADER::COULD_NOT_COMPILE_VERTEX_SHADER." << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//fragment shader
	temp = "";
	src = "";

	input_file.open("shader/fragment_shader.glsl");
	if (input_file.is_open())
	{
		while (getline(input_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR::LOADING_SHADER::COULD_NOT_OPEN_FRAGMENT_FILE." << "\n";
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
		std::cout << "ERROR::LOADING_SHADER::COULD_NOT_COMPILE_FRAGMENT_SHADER." << "\n";
		std::cout << infoLog << "\n";
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
		std::cout << "ERROR::LOADING_SHADER::COULD_NOT_LINK_PROGRAM." << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	//end
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.y += 2.f;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.y -= 2.f;
	}
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

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Test", NULL, NULL);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window); //important.

	//init glew.(needs window and opengl context)
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	//opengl options
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//init shader
	Shader core_program("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
	/*GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();*/

	//model

	//VAO, VBO, EBO	
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set VertexAttribPointer and Enable
	////position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	////color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	////texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	////normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//bind VAO 0
	glBindVertexArray(0);

	//Texture
	Texture texture0("Image/pusheen.png", GL_TEXTURE_2D, 0);


	//Material 
	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture0.getTextureUnit());


	//Matrix init
	glm::vec3 position(0.f, 0.f, 2.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(2.f);

	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);


	glm::vec3 camPosition(0.f, 0.f, 3.0f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.0f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	glm::mat4 ProjectionMatrix(1.0f);

	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float> (framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	//Light
	glm::vec3 lightPos0(0.f, 0.f, 4.f);

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");
	//glUniform3fv(glGetUniformLocation(core_program, "lightPos0"), 1, glm::value_ptr(lightPos0));
	//glUniform3fv(glGetUniformLocation(core_program, "cameraPos"), 1, glm::value_ptr(camPosition));

	/*glUseProgram(core_program);

	glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

	glUseProgram(0);*/

	//main loop

	while (!glfwWindowShouldClose(window))
	{
		//Update Input
		glfwPollEvents();

		//Update 
		updateInput(window);
		///DRAW

		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Use a program
		
		//glUseProgram(core_program);
		core_program.use();

		//update uniforms.
		core_program.set1i(texture0.getTextureUnit(), "texture0");
		//glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);

		//move, rotate, scale
		updateInput(window, position, rotation, scale);

		glm::mat4 ModelMatrix(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		glm::mat4 ProjectionMatrix(1.f);
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float> (framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");
		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		core_program.setMat4fv(ViewMatrix, "ViewMatrix");

		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));

		//activate texture
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);*/
		texture0.bind();
		material0.sendToShader(core_program);

		//Bind vertex array object
		glBindVertexArray(VAO);

		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		//End Draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);			////clean the stuff.
		glUseProgram(0);

		texture0.unbind();

		core_program.unuse();
	}


	//end of program
	glfwTerminate();


	return 0;
}