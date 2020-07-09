#define GLEW_STATIC
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "glm/gtx/string_cast.hpp"

struct WindowInfo {
	std::string Title;
	int Width;
	int Height;
	bool FullScreen;
	GLFWwindow* Window;
	float FovDegrees;
	float NearClip;
	float FarClip;

	static glm::mat4 GetPerspective(const WindowInfo window) {
		return glm::perspective(glm::radians(window.FovDegrees), (float)window.Width / (float)window.Height, window.NearClip, window.FarClip);
	}
};

FPSCamera mainCamera(glm::vec3(0.0f, 0.0f, 0.0f));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS) 
	{
		int debug = 1;
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		mainCamera.move(mainCamera.getLook());
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		mainCamera.move(-1.0f * mainCamera.getLook());
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		mainCamera.move(mainCamera.getRight());
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		mainCamera.move(-1.0f * mainCamera.getRight());
	}
		
}

void InitializeWindow(WindowInfo &info) {
	if (info.Title.empty()) {
		std::cerr << "Attempted to initialize window with invalid WindowInfo" << std::endl;
		return;
	}

	if (!glfwInit()) {
		std::cerr << "GLFW Initialization Failed!" << std::endl;
		return;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	info.Window = glfwCreateWindow(info.Width, info.Height, info.Title.c_str(), NULL, NULL);

	if (info.Window == NULL) {
		std::cerr << "Initializing window failed!" << std::endl;
		return;
	}

	glfwMakeContextCurrent(info.Window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Init Glew Fail" << std::endl;
		glfwTerminate();
		return;
	}

	glClearColor(0.0f, 0.35f, 0.75f, 1.0f);
	glViewport(0, 0, info.Width, info.Height);
	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(info.Window, key_callback);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(info.Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

const char* APP_TITLE = "Tom's 3D Engine!";
const int WIDTH = 1024;
const int HEIGHT = 768;
const bool FULLSCREEN = false;
GLFWwindow* activeWindow = NULL;

int main()
{
	WindowInfo myWindow;
	myWindow.Title = "Tom's 3D Engine";
	myWindow.Height = 768;
	myWindow.Width = 1024;
	myWindow.FovDegrees = 45.0f;
	myWindow.NearClip = 0.1f;
	myWindow.FarClip = 1000.0f;
	InitializeWindow(myWindow); // Must be early on in initialization!!!

	Mesh bunnyMesh;
	bunnyMesh.Load("Resources\\Models\\bowling_pin.obj");

	ShaderProgram basicShader;
	basicShader.loadShaders("Resources\\Shaders\\basic.vert", "Resources\\Shaders\\basic.frag");

	glm::mat4 perspectiveMatrix = WindowInfo::GetPerspective(myWindow);

	while (!glfwWindowShouldClose(myWindow.Window)) {
		glm::mat4 viewMatrix = mainCamera.getViewMatrix();
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -15.0f));
		mainCamera.rotate(0.2f, 0.0f);

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool XD = true;
		//ImGui::ShowAboutWindow(&XD);
		ImGui::Text(glm::to_string(mainCamera.getPosition()).c_str() );
		ImGui::Text(glm::to_string(mainCamera.getLook()).c_str() );

		std::stringstream ss;
		ss << mainCamera.getYaw();
		ImGui::Text(ss.str().c_str());
		ss.str("");
		ss << mainCamera.getPitch();
		ImGui::Text(ss.str().c_str());
		
		basicShader.use();
		basicShader.setUniform("projection", perspectiveMatrix);
		basicShader.setUniform("model", modelMatrix);
		basicShader.setUniform("view", viewMatrix);
		basicShader.setUniform("lightColor", glm::vec3(1.0f,0.2f,0.3f));
		bunnyMesh.Draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(myWindow.Window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
