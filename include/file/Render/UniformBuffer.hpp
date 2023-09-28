#ifndef UNIFORM_BUFFER_HPP_FILE
#define UNIFORM_BUFFER_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "Buffer.hpp"

namespace Engine::Render
{
    class UniformBuffer : public Buffer
    {
    private:
        GLuint bind_uniform_block;
    public:
    	UniformBuffer()
			: Buffer(GL_UNIFORM_BUFFER), bind_uniform_block(0)
		{}
		UniformBuffer(GLenum draw_type, GLenum index_type, const void* data, GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
			: Buffer(GL_UNIFORM_BUFFER, data, size, flags), bind_uniform_block(0)
		{}
		UniformBuffer(GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
			: Buffer(GL_UNIFORM_BUFFER, size, flags), bind_uniform_block(0)
		{}
		UniformBuffer(const UniformBuffer& target)
			: Buffer((Buffer)target), bind_uniform_block(target.bind_uniform_block)
		{}
		UniformBuffer(UniformBuffer&& target)
			: Buffer((Buffer&&)target), bind_uniform_block(target.bind_uniform_block)
		{}
		UniformBuffer& operator=(UniformBuffer&& target) noexcept
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

            bind_uniform_block = target.bind_uniform_block;

			target.buffer_id = 0;
			return *this;
		}
		~UniformBuffer() {}
        void setBindBlockAll(GLuint index)
        {
            this->bind_uniform_block = index;
            glBindBufferBase(GL_UNIFORM_BUFFER, index, this->buffer_id);
        }
        void setBindBlock(GLuint index, const data_range& range)
        {
            this->bind_uniform_block = index;
            glBindBufferRange(GL_UNIFORM_BUFFER, index, this->buffer_id, range.offest, range.length);
        }
    };
} // namespace Engine::Render

#endif //!UNIFORM_BUFFER_HPP_FILE