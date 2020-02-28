#pragma once

class ShaderLoader {
public:
	unsigned int ID;
	ShaderLoader(const char* vertexPath, const char * framePath);

	~ShaderLoader();

	void use();

	void set_int(const char* name, int value);

	void set_bool(const char* name, bool value);

	void set_float(const char* name, float value);

	void set_mat4(const char * name, glm::mat4 &value);

private:
	unsigned int compile_shader(const char * shader_code, int type);
	void check_compile_error(unsigned int shader);
	void check_link_error(unsigned int shader);
};