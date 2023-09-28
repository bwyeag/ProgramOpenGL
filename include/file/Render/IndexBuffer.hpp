#ifndef INDEX_BUFFER_HPP_FILE
#define INDEX_BUFFER_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "RenderFunction.hpp"
#include "Buffer.hpp"
namespace Engine::Render
{
    /// @brief 顶点索引类
    class IndexBuffer : public Buffer
	{
	private:
		/// @brief 绘制时索引排布方法
		GLenum draw_type;
		/// @brief 索引数据类型
		GLenum index_type;
		/// @brief 索引数量
		GLsizei index_count;
	public:
		IndexBuffer()
			: Buffer(GL_ELEMENT_ARRAY_BUFFER)
		{}
		IndexBuffer(GLenum draw_type, GLenum index_type, const void* data, GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
			: Buffer(GL_ELEMENT_ARRAY_BUFFER, data, size, flags), draw_type(draw_type), index_type(index_type),
            index_count(size / TypeSize(index_type))
		{}
		IndexBuffer(GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
			: Buffer(GL_ELEMENT_ARRAY_BUFFER, size, flags)
		{}
		IndexBuffer(const IndexBuffer& target)
			: Buffer((Buffer)target), draw_type(target.draw_type), index_type(target.index_type),
			index_count(target.index_count)
		{}
		IndexBuffer(IndexBuffer&& target)
			: Buffer((Buffer&&)target), draw_type(target.draw_type), index_type(target.index_type),
			index_count(target.index_count)
		{}
		IndexBuffer& operator=(IndexBuffer&& target) noexcept
		{
			buffer_id = target.buffer_id;
			buffer_type = target.buffer_type;
			buffer_size = target.buffer_size;
			buffer_flags = target.buffer_flags;
			map_flags = target.map_flags;
			map_range = target.map_range;
			is_mapping = target.is_mapping;

			draw_type = target.draw_type;
			index_type = target.index_type;
			index_count = target.index_count;

			target.buffer_id = 0;
			return *this;
		}
		void SetData(GLenum draw_type, GLenum index_type)
		{
			this->SetDrawType(draw_type);
			this->SetDataType(index_type);
		}
		void SetDrawType(GLenum draw_type)
		{
			this->draw_type = draw_type;
		}
		void SetDataType(GLenum index_type)
		{
			this->index_type = index_type;
			this->index_count = this->buffer_size / TypeSize(index_type);
		}
		GLenum GetDrawType() const
		{
			return this->draw_type;
		}
		GLenum GetIndexType() const
		{
			return this->index_type;
		}
		GLsizei GetIndexCount() const
		{
			return this->index_count;
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
		~IndexBuffer() {}
	};
}

#endif //!INDEX_BUFFER_HPP_FILE