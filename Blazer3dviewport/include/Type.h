#pragma once

#include <memory>

#include <glad/glad.h>




auto getPtrOf(GLenum type, bool shared) -> decltype()
{

}

GLint getSizeOf(GLenum type)
{
	switch (type)
	{
	case GL_BOOL:					return sizeof(GLboolean);
	case GL_BOOL_VEC2:			return sizeof(GLboolean) * 2;
	case GL_BOOL_VEC3:			return sizeof(GLboolean) * 3;
	case GL_BOOL_VEC4:			return sizeof(GLboolean) * 4;

	case GL_BYTE:					return sizeof(GLbyte);
	case GL_UNSIGNED_BYTE:		return sizeof(GLubyte);

	case GL_SHORT:					return sizeof(GLshort);
	case GL_UNSIGNED_SHORT:		return sizeof(GLushort);

	case GL_INT:					return sizeof(GLint);
	case GL_INT_VEC2:				return sizeof(GLint) * 2;
	case GL_INT_VEC3:				return sizeof(GLint) * 3;
	case GL_INT_VEC4:				return sizeof(GLint) * 4;

	case GL_UNSIGNED_INT:		return sizeof(GLuint);
	case GL_UNSIGNED_INT_VEC2:	return sizeof(GLuint) * 2;
	case GL_UNSIGNED_INT_VEC3:	return sizeof(GLuint) * 3;
	case GL_UNSIGNED_INT_VEC4:	return sizeof(GLuint) * 4;

	case GL_FIXED:					return sizeof(GLfixed);

	case GL_HALF_FLOAT:			return sizeof(GLhalf);

	case GL_FLOAT:					return sizeof(GLfloat);
	case GL_FLOAT_VEC2:			return sizeof(GLfloat) * 2;
	case GL_FLOAT_VEC3:			return sizeof(GLfloat) * 3;
	case GL_FLOAT_VEC4:			return sizeof(GLfloat) * 4;

	case GL_DOUBLE:				return sizeof(GLdouble);
	case GL_DOUBLE_VEC2:			return sizeof(GLdouble) * 2;
	case GL_DOUBLE_VEC3:			return sizeof(GLdouble) * 3;
	case GL_DOUBLE_VEC4:			return sizeof(GLdouble) * 4;

	default: return 0; //Error
	};
}