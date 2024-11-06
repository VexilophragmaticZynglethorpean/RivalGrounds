#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

static void GLAPIENTRY gl_debug_output(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam
);

class Window {
private:
	GLFWwindow* window;
	int height;
	int width;

	double last_time;
	double current_time;
	double delta_time;

	Window();
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

public:
	static Window& get_instance();

	int get_width() const;
	int get_height() const;
	float get_aspect_ratio() const;
	double get_delta_time() const;

	void init_graphics();
	bool is_open() const;
	void render();
};

#endif // WINDOW_H
