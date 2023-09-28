#ifndef BUFFER_HPP_FILE
#define BUFFER_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "RenderFunction.hpp"
#define DEFAULT_BUFFER_FLAG (GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT)
#define DEFAULT_MAP_ACCESS (GL_READ_WRITE)
#define DEFAULT_MAP_FLAG (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT)

namespace Engine::Render
{
	/// @brief Buffer类，所有Buffer的基类
	/// @warning 不会自动绑定到指定的绑定点
	class Buffer
	{
	protected:
		/// @brief 缓存id
		GLuint buffer_id;
		/// @brief 缓存类型（绑定时的绑定点）		
		GLenum buffer_type;
		/// @brief 缓存大小		
		GLsizeiptr buffer_size;
		/// @brief 缓存存储说明	
		GLbitfield buffer_flags;
 		/// @brief 映射信息	
 		union
		{
			mutable GLbitfield map_flags;
			mutable GLenum map_access;
		};
		/// @brief 映射区域		
		mutable data_range map_range;
		/// @brief 是否正在映射		
		mutable bool is_mapping;
	public:
		/// @brief 创建空对象（仅创建）
		Buffer()
			: buffer_id(0), buffer_type(0), buffer_size(0),
			buffer_flags(0), map_access(0), map_range { 0,0 },
			is_mapping(false)
		{
			glCreateBuffers(1, &this->buffer_id);
		}
		/// @brief 按type创建对象（不申请空间）
		/// @param type 对象绑定点
		Buffer(GLenum type)
			: buffer_type(type), buffer_size(0), buffer_flags(0),
			map_access(0), map_range { 0,0 }, is_mapping(false)
		{
			glCreateBuffers(1, &this->buffer_id);
		}
		/// @brief 按type创建空间为size的对象（不初始化）
		/// @param type 对象绑定点
		/// @param size 对象大小
		/// @param flags 对象存储说明（默认动态改变并允许读写映射）
		Buffer(GLenum type, GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG);
		/// @brief 按type创建空间为size的对象，并从data复制数据
		/// @param type 对象绑定点
		/// @param data 对象数据
		/// @param size 对象大小
		/// @param flags 对象存储说明（默认动态改变并允许读写映射）
		Buffer(GLenum type, const void* data, GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG);
		/// @brief 复制构造函数（深度复制，包括存储的数据）
		/// @param target 复制对象
		Buffer(const Buffer& target);
		/// @brief 移动构造函数
		/// @param target 移动目标
		Buffer(Buffer&& target) noexcept;
		/// @brief 移动赋值运算符
		/// @param target 移动目标
		/// @return 自身引用
		Buffer& operator=(Buffer&& target) noexcept;
		/// @brief 判断对象是否使用同一缓存
		/// @param target 判断目标
		/// @return 是否使用同一缓存
		bool operator==(Buffer& target)
		{
			return this->buffer_id == target.buffer_id;
		}
		~Buffer()
		{
			glDeleteBuffers(1, &this->buffer_id);
		}
		/// @brief 设置数据（仅申请）
		/// @param size 申请大小
		/// @param flags 读写方式（默认动态改变并允许读写映射）
		void InitData(GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
		{
			this->buffer_size = size;
			this->buffer_flags = flags;
			glNamedBufferStorage(this->buffer_id, size, nullptr, flags);
		}
		/// @brief 设置数据，从data复制数据
		/// @param data 数据
		/// @param size 申请大小
		/// @param flags 读写方式（默认动态改变并允许读写映射）
		void InitData(const void* data, GLsizeiptr size, GLbitfield flags = DEFAULT_BUFFER_FLAG)
		{
			this->buffer_size = size;
			this->buffer_flags = flags;
			glNamedBufferStorage(this->buffer_id, size, data, flags);
		}
		/// @brief 设置绑定点位置
		/// @param type 绑定点
		void SetBufferType(GLenum type)
		{
			this->buffer_type = type;
		}
		/// @brief 从另一个buffer复制数据，使用指定的位置
		/// @param read_buffer 读缓存
		/// @param read_range 读区域
		/// @param write_offset 写偏移
		void Copy(const Buffer& read_buffer, data_range read_range, GLintptr write_offset);
		/// @brief 从另一个buffer复制全部数据
		/// @param read_buffer 读缓存
		/// @param write_offset 写偏移
		void Copy(const Buffer& read_buffer, GLintptr write_offset);
		/// @brief 复制data指向的this->buffer_size大小的块
		/// @param data 数据指针
		void Copy(const void* data);
		/// @brief 复制data，以write_range为范围
		/// @param data 数据指针
		/// @param write_range 写区域
		void Copy(const void* data, data_range write_range);
		/// @brief 开始buffer映射（整个buffer）
		/// @param access 映射方式
		/// @return 映射指针
		/// @warning BeginMap()与StartMapRange()参数中access与flags不相同，不可混用
		/// @warning BeginMap()与EndMap()对应
		void* BeginMap(GLenum access = DEFAULT_MAP_ACCESS) const;
		/// @brief 开始buffer映射（在指定范围内）
		/// @param range 映射区域
		/// @param flags 映射方式
		/// @return 映射指针
		/// @warning BeginMap()与StartMapRange()参数中access与flags不相同，不可混用
		/// @warning BeginMapRange()与EndMapRange()对应
		void* BeginMapRange(data_range& range, GLbitfield flags = DEFAULT_MAP_FLAG) const;

		/// @brief 解除映射
		/// @return 映射后数据是否损坏
		bool EndMap() const
		{
			return glUnmapNamedBuffer(this->buffer_id);
		}
		/// @brief 解除范围映射（自动刷新（如果需要））
		/// @return 映射后数据是否损坏
		bool EndMapRange()
		{
			if ((this->map_flags & GL_MAP_FLUSH_EXPLICIT_BIT) == GL_MAP_FLUSH_EXPLICIT_BIT)
			{
				glFlushMappedNamedBufferRange(this->buffer_id, map_range.offset, map_range.length);
			}
			return glUnmapNamedBuffer(this->buffer_id);
		}
		/// @brief 刷新缓存到显存
		void FlushAll() const
		{
			glFlushMappedNamedBufferRange(this->buffer_id, 0, this->buffer_size);
		}
		/// @brief 刷新部分缓存到显存
		/// @param dr 部分范围
		void Flush(data_range& dr) const
		{
			glFlushMappedNamedBufferRange(this->buffer_id, dr.offset, dr.length);
		}
		/// @brief 抛弃缓存数据
		void ThrowAll()
		{
			glInvalidateBufferData(this->buffer_id);
		}
		/// @brief 抛弃缓存部分数据
		/// @param dr 部分范围
		void Throw(data_range& dr)
		{
			glInvalidateBufferSubData(this->buffer_id, dr.offset, dr.length);
		}
		/// @brief 绑定
		void Bind() const
		{
			glBindBuffer(this->buffer_type, this->buffer_id);
		}
		/// @brief 解绑
		void UnBind() const
		{
			glBindBuffer(this->buffer_type, 0);
		}
		/// @brief 以指定绑定点绑定
		/// @param type 绑定点
		void Bind(GLenum type) const
		{
			glBindBuffer(type, this->buffer_id);
		}
		/// @brief 从指定绑定点解绑
		/// @param type 绑定点
		void UnBind(GLenum type) const
		{
			glBindBuffer(type, 0);
		}
		/// @brief 获取缓存大小
		/// @return 缓存大小
		GLsizei GetBufferSize() const
		{
			return this->buffer_size;
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
	};
}
#endif //!BUFFER_HPP_FILE