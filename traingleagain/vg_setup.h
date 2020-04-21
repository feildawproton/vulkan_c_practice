#ifndef _VG_SETUP_H_
#define _VG_SETUP_H_

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif // !GLFW_INCLUDE_VULKAN

//BEGIN SECTION: GLFW WINDOW CREATE DESTROY
GLFWwindow* init_create_GLFWwindow();
void destroy_terminate_GLFWwindow(GLFWwindow* pMyWindow);
//END SECTION: GLFW WINDOW CREATE DESTROY

//BEGIN SECTION: GETS
static _inline const char* get_GLFWExtension(uint32_t* pn_RequiredEXTs)
{
	//this is based on the assumption of glfw of course... 
	//could add a check and blah blah blah
	return glfwGetRequiredInstanceExtensions(pn_RequiredEXTs);
}
//END SECTION: GETS
#endif // !_VG_SETUP_H_

