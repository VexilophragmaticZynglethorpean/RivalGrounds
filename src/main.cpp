#include "Graphics/Shaders/ShaderManager.h"
#include <glad/gl.h>
#include <Graphics/Window.h>

int main() {
	Window& window = Window::get_instance();
	ShaderManager& shader_manager = ShaderManager::get_instance();

	GLuint vao, vbo, ebo;
	glCreateVertexArrays(1, &vao);
	glCreateBuffers(1, &vbo);
	glCreateBuffers(1, &ebo);

	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1, 0, 0, // FBL
		-0.5, 0.5, -0.5, 0, 1, 0,  //FTL
		0.5, 0.5, -0.5, 0, 0, 1, //FTR
		0.5, -0.5, -0.5, 0, 1, 0,//FBR
		-0.5, -0.5, -1, 0, 0, 1,
		-0.5, 0.5, -1, 1, 0,0,
		0.5, 0.5, -1, 0, 1, 0,
		0.5, -0.5, -1, 1, 0, 0
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0,
		0, 1, 5,
		5, 4, 0,
		4, 5, 6,
		6, 7, 4,
		6, 7, 3,
		3, 2, 6
	};

	glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(ebo, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT));

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(GL_FLOAT));
	glVertexArrayElementBuffer(vao, ebo);

	while (window.is_open()) {
		window.init_graphics();

		glUseProgram(shader_manager.get("cube"));
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);

		window.render();
	}
}
