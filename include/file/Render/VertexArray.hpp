#ifndef VERTEXARRAY_HPP_FILE
#define VERTEXARRAY_HPP_FILE
#include "glad/glad.h"

#include "type_load.hpp"
#include "Error.hpp"
#include "RenderFunction.hpp"
#include "layout_element.hpp"
#include "Buffer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#define DEAUFT_LAYOUT_COUNT 4
namespace Engine::Render
{
    /// @brief 顶点数组类
    class VertexArray
    {
    protected:
        /// @brief 在OpenGL中的id
        GLuint array_id;
        /// @brief 当前最后一个未使用的顶点属性索引
        GLuint layout_index;
    public:
        /// @brief 仅创建VertexArray
        /// @param n 对顶点属性存储的容量（可扩容）
        VertexArray()
        {
            /*DEBUG记录：<2023/8/4/12:37>
            * array_layouts(n)是初始化大小，对象有n个对象
            * 使用默认构造函数（在此处什么也不做）
            * 注意：不是容量！不是容量！
            * 此DEBUG记录已无用，但予以保留<2023/8/7/13:36>
            */
            glCreateVertexArrays(1, &this->array_id);
            layout_index = 0;
        }
        /// @brief 复制构造函数（复制数据）
        /// @param target 复制目标
        /// @details 复制数据，不创建新对象
        VertexArray(const VertexArray& target)
            :array_id(target.array_id), layout_index(0)
        {}
        /// @brief 移动构造函数
        /// @param target 移动目标
        VertexArray(VertexArray&& target) noexcept
            :array_id(target.array_id)
        {
            target.array_id = 0;
            layout_index = target.layout_index;
        }
        /// @brief 移动赋值运算符
        /// @param target 被移动的目标
        /// @return 自身的引用
        VertexArray& operator=(VertexArray&& target) noexcept;

        /// @brief 设置与VAO关联的VBO（当前绑定的VertexBuffer）的顶点属性（先绑定自身和VBO）
        /// @param target 设置顶点属性的目标
        /// @param range 顶点属性在VBO中的范围
        void Use(VertexBuffer& target, const data_range& range, bool enable = false)
        {
            size_t offset = 0;
            for (GLuint i = range.offset; i < range.offset + range.length;i++)
            {
                const layout_element& val = target.getLayout() [i];
                if ((val.isNormalised() == GL_FALSE) && IsInteger(val.type))
                {
                    glVertexAttribIPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else if (val.type == GL_DOUBLE)
                {
                    glVertexAttribLPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else
                {
                    glVertexAttribPointer(i, val.getCount(), val.type, val.isNormalised(),
                        target.getSize(), (const void*)offset);
                }
                val.setIndex(layout_index);
                if (enable)
                {
                    glEnableVertexAttribArray(this->layout_index);
                }
                val.setEnable(enable);
                this->layout_index++;
                offset += val.size;
            }
        }
        /// @brief 使用全部属性
        void UseAll(VertexBuffer& target, bool enable = false)
        {
            this->Use(target, { 0,GLsizei(target.getLayout().size()) }, enable);
        }
        /// @brief 强制设置未使用的最后一个顶点属性索引
        /// @param n 设置的索引
        void setIndex(GLuint n)
        {
            this->layout_index = n;
        }
        /// @brief 绑定VAO为当前VAO
        void Bind() const
        {
            glBindVertexArray(this->array_id);
        }
        /// @brief 解绑VAO
        void UnBind() const
        {
            glBindVertexArray(0);
        }
    };
    /// @brief 通过输入的layout_element指定的属性设置静态顶点属性(不包含压缩类型)
    /// @param index 要访问的属性
    /// @param v 数据指针
    /// @param array_layouts 属性数组
    void setStatic(GLuint index, const void* v, vector<layout_element>& array_layouts);
}
#endif //!VERTEXARRAY_HPP_FILE