#include "bVertexArrayObjects.h"

GLuint bVertexArrayObjects::getOpenglName(const std::string& label) {
	//Search through the vector for a matching label
	std::vector<bVertexArray>::iterator it;
	it = std::find_if(vertex_arrays.begin(), vertex_arrays.end(),
		[&label](bVertexArray& vert_arr) {
			if (vert_arr.label == label)
				return true;
			return false;
		});

	if (it != vertex_arrays.end())
		return it->opengl_name;
	return 0; //If this happens, the label was not found.
}

void bVertexArrayObjects::createVertexAttribute() {

}