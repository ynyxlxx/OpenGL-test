#pragma once

#include "libs.h"
#include "Camera.h"

//Enumerations
enum shader_enum{ SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_0 = 0, TEX_0_SPECULAR, 
					TEX_1, TEX_1_SPECULAR };
enum material_enum { MAT_0 = 0};
enum mesh_enum { MESH_QUAD = 0};

class Game
{
private:
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta time
	float dt;
	float curTime;
	float lastTime;
	
	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//Camera
	Camera camera;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	
	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;

	//Lights
	std::vector<glm::vec3*> lights;

//Private Functions

	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterial();
	void initModels();
	void initLights();
	void initUniforms();

	void updateUniforms();

//Static Variables

public:
	//Constructors, Deconstructors
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		int GL_VERSION_MAJOR, int GL_VERSION_MINOR,
		bool resizable);
	
	virtual ~Game();

//Accessors
	int getWindowShouldClose();

//Modifiers
	void setWindowShouldClose();

//Functions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();

//Static Variables

//Static Functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};

