#pragma once
//#include <iostream>
#include <string>
//#include <map>
#include <vector>
#include <algorithm>
#include <memory>

#include <glad/glad.h>

#include "bBufferObjects.h"

/*
* Class Author: Dallin Carling Lovin
*/

class bVertexArrayObjects {
private:
	struct bVertexAttribute {
		GLuint index;
		std::string name;
	};

	struct bVertexArray {
		GLuint opengl_name;
		std::string label;
		std::vector<bVertexAttribute> attributes;
	};

	std::vector<bVertexArray> vertex_arrays;

public:
	//constructors

	//Default contructor creates only one vertex array object
	bVertexArrayObjects() {
		bVertexArray new_vao;
		new_vao.label = "0";
		glCreateVertexArrays(1, &new_vao.opengl_name);
		vertex_arrays.push_back(new_vao);
	}

	//Create a specified number of vertex array objects.
	//Label will be the opengl numerical name.
	bVertexArrayObjects(GLint num_vaos) {

		for (int i = 0; i < num_vaos; i++) {
			bVertexArray new_vao;
			new_vao.label = std::to_string(i);
			glCreateVertexArrays(1, &new_vao.opengl_name);
			glObjectLabel(GL_VERTEX_ARRAY, new_vao.opengl_name,
				-1, new_vao.label.c_str()); //TODO: need a constant that indicates what -1 means in this context.
			vertex_arrays.push_back(new_vao);
		}
	}

	//Create a specified number of vertex array objects with labels for each
	bVertexArrayObjects(GLint num_vaos, const std::vector<std::string>& labels) {

		for (int i = 0; i < num_vaos; i++) {
			bVertexArray new_vao;
			new_vao.label = labels.at(i);
			glCreateVertexArrays(1, &new_vao.opengl_name);
			glObjectLabel(GL_VERTEX_ARRAY, new_vao.opengl_name,
				-1, labels.at(i).c_str());
			vertex_arrays.push_back(new_vao);
		}
	}

	//Destructor
	//Delete all vertex array objects.
	~bVertexArrayObjects() {
		std::vector<bVertexArray>::iterator it;
		for (it = vertex_arrays.begin(); it != vertex_arrays.end(); it++) {
			glDeleteVertexArrays(1, &it->opengl_name);
		}
	}

	void createVertexAttribute();

	GLuint getOpenglName(const std::string& label);

};