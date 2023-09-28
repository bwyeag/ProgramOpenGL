#ifndef RENDER_FUNCTION_HPP_FILE
#define RENDER_FUNCTION_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"

namespace Engine::Render
{
	struct data_range
	{
		GLintptr offset;
		GLsizeiptr length;
	};

    constexpr inline bool IsInteger(GLenum type)
	{
		switch (type)
		{
		case GL_BYTE: return true;
		case GL_UNSIGNED_BYTE: return true;
		case GL_SHORT: return true;
		case GL_UNSIGNED_SHORT: return true;
		case GL_INT: return true;
		case GL_UNSIGNED_INT: return true;
		case GL_FIXED: return false;
		case GL_FLOAT: return false;
		case GL_HALF_FLOAT: return false;
		case GL_DOUBLE: return false;
		case GL_INT_2_10_10_10_REV: return false;
		case GL_UNSIGNED_INT_2_10_10_10_REV: return false;
		default:
			throw;
		}
	}
    constexpr inline size_t TypeSize(GLenum type)
    {
        switch (type)
		{
		case GL_BYTE: return sizeof(GLbyte);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		case GL_SHORT: return sizeof(GLshort);
		case GL_UNSIGNED_SHORT: return sizeof(GLushort);
		case GL_INT: return sizeof(GLint);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_FIXED: return sizeof(GLfixed);
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_HALF_FLOAT: return sizeof(GLhalf);
		case GL_DOUBLE: return sizeof(GLdouble);
		case GL_INT_2_10_10_10_REV: return sizeof(GLuint);
		case GL_UNSIGNED_INT_2_10_10_10_REV: return sizeof(GLuint);
		default:
			throw;
		}
    }
	
	/// @brief 用于真正复制对象数据（大多类复制会产生新对象）
	/// @tparam T 对象名
	/// @param read 复制对象
	/// @return 对象右值引用
	/// @warning 请注意被复制对象的生存时间
	template<typename T>
	T&& CopyObject(const T& read)
	{
		uint8_t data[sizeof(T)];
		memcpy(data, &read, sizeof(T));
		return move(*(T*)data);
	}
}

#endif //!RENDER_FUNCTION_HPP_FILE