#ifndef LAYOUT_ELEMENT_HPP_FILE
#define LAYOUT_ELEMENT_HPP_FILE
#include "glad/glad.h"

#include "type_load.hpp"
#include "Error.hpp"
#include "RenderFunction.hpp"

namespace Engine::Render
{
    /// @brief 用于存储顶点数组属性的结构
    struct layout_element
    {
        /// @brief 属性数据类型
        GLenum type;
        /// @brief 数据长度
        GLsizei size;
        /// @brief 复合对象包含多个信息
        /// @details 字节排序（高位）-8a-8b-8c-8d-（低位）a:是否归一化,
        ///          b:使用的index[1-255],c:是否启用,d:数量(1,2,3,4)
        mutable GLuint info;
        /// @brief 无参构造，不进行任何初始化
        layout_element() {}

        /// @brief 构造函数，初始化数据
        /// @param type 属性数据类型
        /// @param count 数量
        /// @param normalize 是否归一化到[-1,+1]或[0,1]（强制转换为float）
        layout_element(GLenum type, GLuint count, GLboolean normalize)
            :type(type), size(count* static_cast<GLuint>(TypeSize(type)))
        {
            this->info = 0x00000000;
            if (normalize == GL_TRUE)
            {
                this->info |= 0xFF000000;
            }
            this->info |= static_cast<GLubyte>(count);
        }
        /// @brief 移动构造函数（实际只是复制）
        /// @param target 移动目标
        layout_element(layout_element&& target) noexcept
            :type(target.type), size(target.size), info(target.info)
        {}
        /// @brief 复制构造函数
        /// @param target 复制目标
        layout_element(const layout_element& target)
            :type(target.type), size(target.size), info(target.info)
        {}
        layout_element& operator=(layout_element& target)
        {
            if (&target == this)
            {
                return *this;
            }
            type = target.type;
            size = target.size;
            info = target.info;
            return *this;
        }
        layout_element& operator=(layout_element&& target)
        {
            if (&target == this)
            {
                return *this;
            }
            type = target.type;
            size = target.size;
            info = target.info;
            return *this;
        }
        void setCount(GLuint count) const
        {
#ifdef _DEBUG
            if (count > 0xFF)
            {
                WARNING("INPUT","count过大")
            }
#endif
            this->info &= 0xFFFFFF00;
            this->info |= static_cast<GLubyte>(count);
        }

        GLuint getCount() const
        {
            return this->info & 0x000000FF;
        }
        GLboolean isEnable() const
        {
            return (this->info & 0x0000FF00) != 0;
        }
        void setEnable(bool enable) const
        {
            if (enable)
            {
                this->info |= 0x0000FF00;
            }
            else
            {
                this->info &= 0xFFFF00FF;
            }
        }
        GLboolean isNormalised() const
        {
            return (this->info & 0xFF000000) != 0;
        }
        void setNormalised(bool enable) const
        {
            if (enable)
            {
                this->info |= 0xFF000000;
            }
            else
            {
                this->info &= 0x00FFFFFF;
            }
        }
        void setIndex(GLuint index) const
        {
#ifdef _DEBUG
            if (index > 0xFF)
            {
                WARNING("INPUT","index过大")
            } 
#endif      
            this->info |= (index << 16);
        }
        GLuint getIndex() const
        {
            return (this->info & 0x00FF0000) >> 16;
        }
    };
}

#endif //!LAYOUT_ELEMENT_HPP_FILE