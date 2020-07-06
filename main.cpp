#define GLEW_STATIC
#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GLFW/glfw3.h"


struct WindowInfo {
	std::string Title;
	int Width;
	int Height;
	bool FullScreen;
	GLFWwindow* Window;
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

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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

	InitializeWindow(myWindow);

	while (!glfwWindowShouldClose(myWindow.Window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(myWindow.Window);
	}
	glfwTerminate();
	return 0;
}
