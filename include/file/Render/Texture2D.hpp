#ifndef TEXTURE2D_HPP_FILE
#define TEXTURE2D_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "Texture.hpp"
#include "LoadType.hpp"

#include "Buffer.hpp"

namespace Engine::Render
{
    /// @brief 二维纹理
    class Texture2D : public Texture
    {
    private:
        GLsizei mipmap_level;
        GLenum data_format;
        GLsizei data_width, data_height;

    public:
        /// @brief 构造函数
        /// @param format 纹理格式 
        /// @param width 纹理宽度
        /// @param height 纹理高度
        /// @param mipmap mipmap层级
        Texture2D(GLenum format, GLsizei width, GLsizei height, GLsizei mipmap = 0)
            : Texture(GL_TEXTURE_2D), mipmap_level(mipmap), data_format(format),
             data_width(width), data_height(height)
        {
            glTextureStorage2D(this->texture_id, this->mipmap_level, this->data_format,
                this->data_width, this->data_height);
        }
        Texture2D(Load::image_data& data, GLsizei mipmap = 0)
            : Texture(GL_TEXTURE_2D), mipmap_level(mipmap), data_width(data.width), data_height(data.height)
        {
            switch (data.channels)
            {
            case 1:
                this->data_format = GL_R8;
                break;
            case 2:
                this->data_format = GL_RG8;
                break;
            case 3:
                this->data_format = GL_RGB8;
                break;
            case 4:
                this->data_format = GL_RGBA8;
                break;
            }
            glTextureStorage2D(this->texture_id, this->mipmap_level, this->data_format,
                this->data_width, this->data_height);
            glTextureSubImage2D(this->texture_id, level, 0, 0, this->data_width,
                this->data_height, this->data_format, GL_UNSIGNED_BYTE, data.ptr);
        }
        ~Texture2D() {}

        /// @brief 设置数据
        /// @param level 使用第几层级
        /// @param type 数据类型
        /// @param data 数据指针
        setData(GLint level, GLenum type, const void *data)
        {
            glTextureSubImage2D(this->texture_id, level, 0, 0, this->data_width,
                this->data_height, this->data_format, type, data);
        }

        setDataByBuffer(GLint level, GLenum type, const Buffer& buffer)
        {
            buffer.Bind(GL_PIXEL_UNPACK_BUFFER);
            glTextureSubImage2D(this->texture_id, level, 0, 0, this->data_width,
                this->data_height, this->data_format, type, nullptr);
            buffer.UnBind(GL_PIXEL_UNPACK_BUFFER);
        }
    };

    /// @brief 二维多重采样纹理
    class Texture2DMS : public Texture
    {
    private:
        GLsizei sample_count;
        GLenum data_format;
        GLsizei data_width, data_height;
        GLboolean fix_sample;

    public:
        /// @brief 构造函数
        /// @param format 纹理格式
        /// @param width 纹理宽度 
        /// @param height 纹理高度 
        /// @param sample 采样数
        /// @param fixsample 是否固定采样数
        Texture2DMS(GLenum format, GLsizei width, GLsizei height, GLsizei sample, GLboolean fixsample = GL_FALSE)
            : Texture(GL_TEXTURE_2D_MULTISAMPLE), sample_count(sample), data_format(format),
             data_width(width), data_height(height), fix_sample(fixsample)
        {
            glTextureStorage2DMultisample(this->texture_id, this->sample_count, this->data_format,
                this->data_width, this->data_height, this->fix_sample);
        }
        Texture2DMS(Load::image_data& data, GLsizei sample, GLboolean fixsample = GL_FALSE)
            : Texture(GL_TEXTURE_2D),sample_count(sample), data_width(data.width),
             data_height(data.height),fix_sample(fixsample)
        {
            switch (data.channels)
            {
            case 1:
                this->data_format = GL_R8;
                break;
            case 2:
                this->data_format = GL_RG8;
                break;
            case 3:
                this->data_format = GL_RGB8;
                break;
            case 4:
                this->data_format = GL_RGBA8;
                break;
            }
            glTextureStorage2DMultisample(this->texture_id, this->sample_count, this->data_format,
                this->data_width, this->data_height, this->fix_sample);
            glTextureSubImage2D(this->texture_id, 0, 0, 0, this->data_width,
                this->data_height, this->data_format, GL_UNSIGNED_BYTE, data.ptr);
        }
        ~Texture2DMS() {}

        /// @brief 设置数据
        /// @param format 纹理格式 
        /// @param data 数据指针
        setData(GLenum type, const void *data)
        {
            glTextureSubImage2D(this->texture_id, 0, 0, 0,
                this->data_width, this->data_height, this->data_format, type, data);
        }

        setDataByBuffer(GLenum type, const Buffer& buffer)
        {
            buffer.Bind(GL_PIXEL_UNPACK_BUFFER);
            glTextureSubImage2D(this->texture_id, 0, 0, 0, this->data_width,
                this->data_height, this->data_format, type, nullptr);
            buffer.UnBind(GL_PIXEL_UNPACK_BUFFER);
        }
    };

    /// @brief 二维纹理数组
    class Texture2DArray : public Texture
    {
    private:
        GLsizei mipmap_level;
        GLenum data_format;
        GLsizei data_width, data_height, array_count;

    public:
        /// @brief 构造函数
        /// @param format 纹理格式 
        /// @param width 纹理宽度 
        /// @param height 纹理高度 
        /// @param count 数组纹理数
        /// @param mipmap mipmap层级
        Texture2DArray(GLenum type, GLsizei width, GLsizei height, GLsizei count, GLsizei mipmap = 0)
            : Texture(GL_TEXTURE_2D_ARRAY), mipmap_level(mipmap), data_format(type),
             data_width(width), array_count(count)
        {
            glTextureStorage3D(this->texture_id, this->mipmap_level, this->data_format,
                this->data_width, this->data_height, this->array_count);
        }
        ~Texture2DArray() {}

        /// @brief 设置数据
        /// @param level mipmap层级
        /// @param index 数组纹理索引
        /// @param format 纹理格式 
        /// @param data 数据指针
        setData(GLint level, GLsizei index, GLenum type, const void *data)
        {
            glTextureSubImage3D(this->texture_id, level, 0, 0, index, this->data_width, 
                this->data_height, 1, this->data_format, type, data);
        }

        setDataByBuffer(GLint level, GLsizei index, GLenum type, const Buffer& buffer)
        {
            buffer.Bind(GL_PIXEL_UNPACK_BUFFER);
            glTextureSubImage3D(this->texture_id, level, 0, 0, index, this->data_width, 
                this->data_height, 1, this->data_format, type, nullptr);
            buffer.UnBind(GL_PIXEL_UNPACK_BUFFER);
        }
    };

    /// @brief 二维多重采样纹理数组
    class Texture2DArrayMS : public Texture
    {
    private:
        GLsizei sample_count;
        GLenum data_format;
        GLsizei data_width, data_height, array_count;
        GLboolean fix_sample;

    public:
        /// @brief 构造函数
        /// @param format 纹理格式 
        /// @param width 纹理宽度 
        /// @param height 纹理高度 
        /// @param count 数组纹理数
        /// @param sample 采样数
        /// @param fixsample 是否固定采样数
        Texture2DArrayMS(GLenum type, GLsizei width, GLsizei height, GLsizei count, GLsizei sample, GLboolean fixsample = GL_FALSE)
            : Texture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY), sample_count(sample), data_format(type),
             data_width(width), array_count(count), fix_sample(fixsample)
        {
            glTextureStorage3DMultisample(this->texture_id, this->sample_count, this->data_format, 
                this->data_width, this->data_height, this->array_count, this->fix_sample);
        }
        ~Texture2DArrayMS() {}

        /// @brief 设置数据
        /// @param index 数组纹理索引
        /// @param format 纹理格式 
        /// @param data 数据指针
        setData(GLenum type, const void *data)
        {
            glTextureSubImage3D(this->texture_id, 0, 0, 0, index, this->data_width, 
                this->data_height, 1, this->data_format, type, data);
        }

        setDataByBuffer(GLsizei index, GLenum type, const Buffer& buffer)
        {
            buffer.Bind(GL_PIXEL_UNPACK_BUFFER);
            glTextureSubImage3D(this->texture_id, 0, 0, 0, index, this->data_width, 
                this->data_height, 1, this->data_format, type, nullptr);
            buffer.UnBind(GL_PIXEL_UNPACK_BUFFER);
        }
    };
} // namespace Engine::Render
#endif //! TEXTURE2D_HPP_FILE