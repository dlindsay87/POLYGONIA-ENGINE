#include "shader.h"

namespace POLYGINE {
	
	//vertex shader
	void Shader::_compile_vertex() {
		_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vertexShader, 1, &_vertSource, NULL);
		glCompileShader(_vertexShader);

		glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_vertexShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog;
			exit(1);
		}
	}

	//fragment shader
	void Shader::_compile_fragment() {
		_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fragmentShader, 1, &_fragSource, NULL);	
		glCompileShader(_fragmentShader);

		glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_fragmentShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << _infoLog;
			exit(1);
		}
	}

	//shader program
	void Shader::_link_shader() {
		ID = glCreateProgram();

		glAttachShader(ID, _vertexShader);
		glAttachShader(ID, _fragmentShader);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetProgramInfoLog(ID, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _infoLog;
		}
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);
	}

	Shader::Shader(cc* vPath, cc* fPath) {
		_vertSource = fileReader(vPath);
		_fragSource = fileReader(fPath);
		
		_compile_vertex();
		_compile_fragment();
		_link_shader();
		
		cout << "Shader " << ID << " initialized." << endl;
	}
	
	Shader::~Shader() {
	    glDeleteProgram(ID);
	    delete[] _vertSource;
        delete[] _fragSource;
	}
	
	void Shader::use() {
		glUseProgram(ID);
	}
	
	int Shader::getUniformLocation(const str &name) {
		if (_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
            return _uniformLocationCache[name];
        }
		
		int loc = glGetUniformLocation(ID, name.c_str());
        if (loc != -1) _uniformLocationCache[name] = loc;   
        else {
			std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
			exit(1);
		}
        return loc;
	}

	void Shader::setMat4(const str &name, const glm::mat4 &mat) {
        int loc = getUniformLocation(name);
		if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }
	
	void Shader::setVec3(const str &name, const glm::vec3 &vec) {
        int loc = getUniformLocation(name);
		if (loc != -1) glUniform3fv(loc, 1, glm::value_ptr(vec));
    }
	
	void Shader::setVec3Array(const str &name, const glm::vec3 (&v)[5]) {
        int loc = getUniformLocation(name);
		if (loc != -1) glUniform3fv(loc, 5, glm::value_ptr(v[0]));
	}

}
