#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <glad/gl.h>
#include <unordered_map>
#include <string>

class ShaderManager {
private:
	std::unordered_map<std::string, GLuint> database;

	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

public:
	static ShaderManager& get_instance();
	GLuint get(const std::string& program_name);
};

#endif // SHADERMANAGER_H
