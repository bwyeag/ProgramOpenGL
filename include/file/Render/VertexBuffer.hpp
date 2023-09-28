#ifndef VERTEX_BUFFER_HPP_FILE
#define VERTEX_BUFFER_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "RenderFunction.hpp"
#include "Buffer.hpp"
#include "layout_element.hpp"

#define DEAUFT_VERTEX_ELEMENT_RESERVE 2
namespace Engine::Render
{
	/// @brief 顶点数据类
	class VertexBuffer : public Buffer
	{
	private:
		GLsizei vertex_size = 0;
		vector<layout_element> vertex_layout;
	public:
		VertexBuffer(uint32_t reserve = DEAUFT_VERTEX_ELEMENT_RESERVE)
			: Buffer(GL_ARRAY_BUFFER)
		{
			this->vertex_layout.reserve(reserve);
		}
		VertexBuffer(const void* data, GLsizeiptr size,
			GLbitfield flags = DEFAULT_BUFFER_FLAG,
			uint32_t reserve = DEAUFT_VERTEX_ELEMENT_RESERVE)
			: Buffer(GL_ARRAY_BUFFER, data, size, flags)
		{
			vertex_layout.reserve(reserve);
		}
		VertexBuffer(GLsizeiptr size,
			GLbitfield flags = DEFAULT_BUFFER_FLAG,
			uint32_t reserve = DEAUFT_VERTEX_ELEMENT_RESERVE)
			: Buffer(GL_ARRAY_BUFFER, size, flags)
		{
			vertex_layout.reserve(reserve);
		}
		VertexBuffer(const VertexBuffer& target)
			: Buffer(target), vertex_size(target.vertex_size),
			vertex_layout(target.vertex_layout)
		{}
		VertexBuffer(VertexBuffer&& target)
			: Buffer(forward<Buffer>(target)), vertex_size(target.vertex_size),
			vertex_layout(forward<vector<layout_element> >(target.vertex_layout))
		{}
		VertexBuffer& operator=(VertexBuffer&& target) noexcept
		{
			this->buffer_id = target.buffer_id;
			this->buffer_type = target.buffer_type;
			this->buffer_size = target.buffer_size;
			this->buffer_flags = target.buffer_flags;
			this->map_flags = target.map_flags;
			this->map_range = target.map_range;
			this->is_mapping = target.is_mapping;

			this->vertex_layout = forward<vector<layout_element> >(target.vertex_layout);
			this->vertex_size = target.vertex_size;

			target.buffer_id = 0;
			return *this;
		}
		~VertexBuffer() {}

		VertexBuffer& operator<<(const layout_element& data)
		{
			this->vertex_size += data.size;
			this->vertex_layout.push_back(data);
			return *this;
		}
		/// @brief 获取id
		operator GLuint() const
		{
			return this->buffer_id;
		}

		GLuint getID() const
		{
			return this->buffer_id;
		}
		GLsizei getSize() const
		{
			return this->vertex_size;
		}
		const vector<layout_element>& getLayout() const
		{
			return this->vertex_layout;
		}
	};

}

#endif //!VERTEX_BUFFER_HPP_FILE