#define GLFW_INCLUDE_NONE
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <iostream>

#include <Graphics/Window.h>

constexpr int MIN_OPENGL_VERSION_MAJOR = 3;
constexpr int MIN_OPENGL_VERSION_MINOR = 3;
constexpr GLFWmonitor* MONITOR_FOR_FULL_SCREEN = NULL;
constexpr GLFWwindow* WINDOW_TO_SHARE_RESOURCES_WITH = NULL;
constexpr const char* WINDOW_TITLE = "RivalGrounds";
constexpr int VSYNC = 1;

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void GLAPIENTRY gl_debug_output(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam
) {
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 131222) return;
	/*if (type == GL_DEBUG_TYPE_PERFORMANCE) return;*/

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;

}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

}

Window::Window() {
	if (!glfwInit()) {
		std::wcerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MIN_OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	#endif

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* video_mode = glfwGetVideoMode(primaryMonitor);


	window = glfwCreateWindow(
		video_mode->width / 2,
		video_mode->height / 2, 
		WINDOW_TITLE,
		MONITOR_FOR_FULL_SCREEN,
		WINDOW_TO_SHARE_RESOURCES_WITH
	);
	if (!window) {
		std::wcerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress)) {
		std::wcerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwSwapInterval(VSYNC);

	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
		glDebugMessageCallback(gl_debug_output, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Initialized debug context");
	}

	last_time = glfwGetTime();
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

Window& Window::get_instance() {
	static Window instance;
	return instance;
}

inline int Window::get_width() const {
	return width;
}

inline int Window::get_height() const {
	return height;
}

inline float Window::get_aspect_ratio() const {
	return static_cast<float>(width) / static_cast<float>(height);
}

inline double Window::get_delta_time() const {
	return delta_time;
}

void Window::init_graphics() {
	current_time = glfwGetTime();
	delta_time = current_time - last_time;
	last_time = current_time;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::is_open() const {
	return !glfwWindowShouldClose(window);
}

void Window::render() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
