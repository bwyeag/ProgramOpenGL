#include "Buffer.hpp"

namespace Engine::Render
{
	Buffer::Buffer(GLenum type, GLsizeiptr size, GLbitfield flags)
		: buffer_type(type), buffer_size(size), buffer_flags(flags),
		map_access(0), map_range { 0,0 }, is_mapping(false)
	{
		glCreateBuffers(1, &this->buffer_id);
		glNamedBufferStorage(this->buffer_id, size, nullptr, flags);
	}
	Buffer::Buffer(GLenum type, const void* data, GLsizeiptr size, GLbitfield flags)
		: buffer_type(type), buffer_size(size), buffer_flags(flags),
		map_access(0), map_range { 0,0 }, is_mapping(false)
	{
		glCreateBuffers(1, &this->buffer_id);
		glNamedBufferStorage(this->buffer_id, size, data, flags);
	}
	Buffer::Buffer(const Buffer& target)
		: buffer_type(target.buffer_type), buffer_size(target.buffer_size),
		buffer_flags(target.buffer_flags), map_access(0), map_range({ 0,0 }),
		is_mapping(false)
	{
		glCreateBuffers(1, &this->buffer_id);
		glBindBuffer(GL_COPY_WRITE_BUFFER, this->buffer_id);
		glBindBuffer(GL_COPY_READ_BUFFER, target.buffer_id);
		glNamedBufferStorage(this->buffer_id, target.buffer_size, nullptr, target.buffer_flags);
		glCopyNamedBufferSubData(target.buffer_id, this->buffer_id, 0, 0, target.buffer_size);
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
		glBindBuffer(GL_COPY_READ_BUFFER, 0);
	}
	Buffer& Buffer::operator=(Buffer&& target) noexcept
	{
		if (&target == this)
		{
			return *this;
		}

		this->buffer_id = target.buffer_id;
		this->buffer_type = target.buffer_type;
		this->buffer_size = target.buffer_size;
		this->buffer_flags = target.buffer_flags;
		this->map_flags = target.map_flags;
		this->map_range = target.map_range;
		this->is_mapping = target.is_mapping;

		target.buffer_id = 0;
		return *this;
	}
	void Buffer::Copy(const Buffer& read_buffer, data_range read_range, GLintptr write_offset)
	{
		//glBindBuffer(GL_COPY_WRITE_BUFFER, this->buffer_id);
		//glBindBuffer(GL_COPY_READ_BUFFER, read_buffer.buffer_id);
		glCopyNamedBufferSubData(read_buffer.buffer_id, this->buffer_id, read_range.offset, write_offset, read_range.length);
	}
	void Buffer::Copy(const Buffer& read_buffer, GLintptr write_offset)
	{
		//glBindBuffer(GL_COPY_WRITE_BUFFER, this->buffer_id);
		//glBindBuffer(GL_COPY_READ_BUFFER, read_buffer.buffer_id);
		glCopyNamedBufferSubData(read_buffer.buffer_id, this->buffer_id, 0, write_offset, read_buffer.buffer_size);
	}
	void* Buffer::BeginMap(GLenum access) const
	{
		this->map_range = { 0,this->buffer_size };
		this->map_access = access;
		this->is_mapping = true;
		return glMapBuffer(this->buffer_id, access);
	}
	void* Buffer::BeginMapRange(data_range& range, GLbitfield flags) const
	{
		this->map_range = range;
		this->map_flags = flags;
		this->is_mapping = true;
		return glMapBufferRange(this->buffer_id, range.offset, range.length, flags);
	}
	void Buffer::Copy(const void* data)
	{
		//glBindBuffer(GL_COPY_WRITE_BUFFER, this->buffer_id);
		glNamedBufferSubData(this->buffer_id, 0, this->buffer_size, data);
	}
	void Buffer::Copy(const void* data, data_range write_range)
	{
		//glBindBuffer(GL_COPY_WRITE_BUFFER, this->buffer_id);
		glNamedBufferSubData(this->buffer_id, write_range.offset, write_range.length, data);
	}
	Buffer::Buffer(Buffer&& target) noexcept
	{
		buffer_id = target.buffer_id;
		buffer_type = target.buffer_type;
		buffer_size = target.buffer_size;
		buffer_flags = target.buffer_flags;
		map_flags = target.map_flags;
		map_range = target.map_range;
		is_mapping = target.is_mapping;

		target.buffer_id = 0;
	}

}