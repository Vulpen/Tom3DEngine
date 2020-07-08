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

	if (glewInit() != GLEW_OK) {
		std::cerr << "Init Glew Fail" << std::endl;
		glfwTerminate();
		return;
	}

	glClearColor(0.0f, 0.35f, 0.75f, 1.0f);
	glViewport(0, 0, info.Width, info.Height);
	glEnable(GL_DEPTH_TEST);

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
	InitializeWindow(myWindow); // Must be early on in initialization!!!

	FPSCamera mainCamera;

	Mesh bunnyMesh;
	bunnyMesh.Load("Resources\\Models\\bunny.obj");

	ShaderProgram basicShader;
	basicShader.loadShaders("Resources\\Shaders\\basic.vert", "Resources\\Shaders\\basic.frag");

	glm::mat4 perspectiveMatrix = WindowInfo::GetPerspective(myWindow);
	glm::mat4 viewMatrix = mainCamera.getViewMatrix();

	while (!glfwWindowShouldClose(myWindow.Window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool XD = true;
		ImGui::ShowAboutWindow(&XD);

		basicShader.use();
		basicShader.setUniform("projection", perspectiveMatrix);
		basicShader.setUniform("model", glm::mat4(1.0f));
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
