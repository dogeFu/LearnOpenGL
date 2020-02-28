
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_loader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void read_file(const char* path,string &des) {
	//读文件，生成shader,绑定到program
	ifstream reader;
	string line;
	reader.open(path);
	if (reader.is_open()) {
		while (getline(reader, line))
		{
			des += line;
			des += "\n";
		}
		reader.close();
	}
	else {
		cout << "read file fail! " << path << endl;
	}
}

ShaderLoader::ShaderLoader(const char* vertexPath, const char * framePath) {
	string vertex_code, frame_code;
	read_file(vertexPath, vertex_code);
	read_file(framePath, frame_code);

	//compile shader
	unsigned int vertex_shader, frame_shader;
	vertex_shader = compile_shader(vertex_code.c_str() , 0);
	frame_shader = compile_shader(frame_code.c_str(), 1);

	this->ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, frame_shader);
	glLinkProgram(ID);
	check_link_error(ID);

	glDeleteShader(vertex_shader);
	glDeleteShader(frame_shader);
}

ShaderLoader::~ShaderLoader() {

}

void ShaderLoader::set_int(const char* name, int value) {
	int location = glGetUniformLocation(ID, name);
	glUniform1i(location, value);
}

void ShaderLoader::set_bool(const char* name, bool value) {
	int location = glGetUniformLocation(ID, name);
	glUniform1i(location, (int)value);
}

void ShaderLoader::set_float(const char* name, float value) {
	int location = glGetUniformLocation(ID, name);
	glUniform1f(location, value);
}

void ShaderLoader::set_mat4(const char* name,glm::mat4 &value) {
	int location = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderLoader::use() {
	glUseProgram(this->ID);
}



unsigned int ShaderLoader::compile_shader(const char* shader_code,int type) {
	unsigned int shader;
	shader = type == 0 ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &shader_code, NULL);
	glCompileShader(shader);
	check_compile_error(shader);
	return shader;
}

void ShaderLoader::check_compile_error(unsigned int shader) {
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		cout << "ERROR::SHADER_COMPILATION_ERROR:\n" << infoLog << "\n" << endl;
	}
}

void ShaderLoader::check_link_error(unsigned int program) {
	int success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR : \n"<< infoLog << "\n" << std::endl;
	}
}