#pragma once
//#include <iostream>
#include <string>
//#include <map>
#include <vector>
#include <algorithm>
#include <memory>

#include <glad/glad.h>

#include "bBufferObjects.h"
#include "constants.h"

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

	std::vector<std::shared_ptr<bVertexArray>> vertex_arrays;

public:
	//constructors

	//Default contructor with empty array of vertex array objects
	bVertexArrayObjects() { }

	//Create a specified number of vertex array objects.
	//Label will be the opengl numerical name.
	bVertexArrayObjects(GLint num_vaos) {

		for (int i = 0; i < num_vaos; i++) {
			auto ptr = std::make_shared<bVertexArray>(new bVertexArray);
			glCreateVertexArrays(1, &ptr->opengl_name);
			ptr->label = std::to_string(ptr->opengl_name);
			vertex_arrays.push_back(ptr);
		}
	}

	//Constructor that takes in an initializer list of labels.
	//Will create a VAOs for each label.
	bVertexArrayObjects(const std::initializer_list<std::string> l) {

		std::initializer_list<std::string>::iterator it;
		for (it = l.begin(); it != l.end(); it++) {
			auto ptr = std::make_shared<bVertexArray>(new bVertexArray);
			ptr->label = *it;
			glCreateVertexArrays(1, &ptr->opengl_name);
			glObjectLabel(GL_VERTEX_ARRAY, ptr->opengl_name,
				B_NULL_TERMINATED, ptr->label.c_str());
			vertex_arrays.push_back(ptr);
		}
	}

	//Destructor
	//Delete all vertex array objects.
	~bVertexArrayObjects() {
		std::vector<std::shared_ptr<bVertexArray>>::iterator it;
		for (it = vertex_arrays.begin(); it != vertex_arrays.end(); it++) {
			if (it->use_count() == 1)
			glDeleteVertexArrays(1, &(*it)->opengl_name);
		}
	}

	void createVertexAttribute();
	int size() { return vertex_arrays.size(); }
	std::shared_ptr<bVertexArray> getVertexArray(const std::string& label);
	std::shared_ptr<bVertexArray> getVertexArray(const GLuint opengl_name);
	std::vector<std::weak_ptr<bVertexArray>> getAllVertexArrays();

	GLuint getOpenglName(const std::string& label);

};