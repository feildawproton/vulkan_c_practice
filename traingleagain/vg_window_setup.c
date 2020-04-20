#include "vg_setup.h"

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;
const char* WINDOW_NAME = "Hello Window";
#define WINDOW_MONITOR NULL
#define WINDOW_SHARE NULL

//BEGIN SECTION: GLFW WINDOW CREATE DESTROY
GLFWwindow* create_GLFWwindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	return glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, WINDOW_MONITOR, WINDOW_SHARE);
}
void destroy_GLFWwindow(GLFWwindow* pMyWindow)
{
	glfwDestroyWindow(pMyWindow);
	glfwTerminate();
}
//END SECTION: GLFW WINDOW CREATE DESTROY