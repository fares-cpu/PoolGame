#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertex_path, const char* fragment_path);

	void use();

	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	void set_vec2(const std::string& name, float x, float y);
	void set_vec3(const std::string& name, float x, float y, float z);
	void set_vec3(const std::string& name, glm::vec3 vec);
	void set_vec4(const std::string& name, float x, float y, float z, float w);
	void set_mat4(const std::string& name, glm::mat4 mat);

};

