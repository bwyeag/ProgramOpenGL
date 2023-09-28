#ifndef RENDER_OBJECT_BASE
#define RENDER_OBJECT_BASE
#include "glad/glad.h"

#include "type_load.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

namespace Engine::Render
{
    /// @brief 渲染对象基类
    class renderobject_base : protected VertexArray
    {
    protected:
        /// @brief 渲染的VBO数组
        vector<VertexBuffer> render_vbos;
        /// @brief 顶点属性到布局元素对象的映射
        map<GLuint, const layout_element*> index_map;
        void Use(VertexBuffer& target, const data_range& range, bool enable = false);
        void Use_reset(VertexBuffer& target);
    public:
        /// @brief 构造函数
        /// @param serve VBO数组大小
        renderobject_base(uint32_t size)
            :VertexArray()
        {
            this->render_vbos.resize(size);
        }

        /// @brief 复制构造函数，自动重新绑定顶点属性
        /// @param target 目标
        renderobject_base(const renderobject_base& target)
            : VertexArray(), render_vbos(target.render_vbos), index_map()
        {
            this->Bind();
            for (VertexBuffer& a : this->render_vbos)
            {
                a.Bind();
                this->Use_reset(a);
            }
        }

        /// @brief 移动构造函数
        /// @param target 目标
        renderobject_base(renderobject_base&& target) noexcept
            : VertexArray(forward<VertexArray>(target)),
            render_vbos(forward<vector<VertexBuffer> >(target.render_vbos)),
            index_map(forward<map<GLuint, const layout_element*> >(target.index_map)) {}

        /// @brief 移动赋值运算符
        /// @param target 目标
        /// @return 自身引用
        renderobject_base& operator=(renderobject_base&& target) noexcept;

        ~renderobject_base() {}

        /// @brief 加载全部顶点属性，并输入VBO
        /// @param target 目标
        /// @param enable 是否启用
        void UseAttrib_All(VertexBuffer&& target, bool enable = false)
        {
            this->UseAttrib(forward<VertexBuffer>(target), { 0,GLsizeiptr(target.getLayout().size()) }, enable);
        }
        /// @brief 加载全部顶点属性，使用自身的VBO
        /// @param index 目标索引
        /// @param enable 是否启用
        void UseAttrib_All(uint32_t index, bool enable = false)
        {
            this->UseAttrib(index, { 0,GLsizeiptr(this->render_vbos[index].getLayout().size()) }, enable);
        }
        /// @brief 加载顶点属性，并输入VBO
        /// @param target 目标
        /// @param range 属性范围
        /// @param enable 是否启用
        void UseAttrib(VertexBuffer&& target, const data_range& range, bool enable = false)
        {
            this->render_vbos.push_back(forward<VertexBuffer>(target));
            VertexBuffer& data = this->render_vbos.back();
            data.Bind();
            this->Use(data, range, enable);
        }
        /// @brief 加载顶点属性，使用自身的VBO
        /// @param index 目标索引
        /// @param range 范围
        /// @param enable 是否启用
        void UseAttrib(uint32_t index, const data_range& range, bool enable = false)
        {
            this->Use(this->render_vbos[index], range, enable);
        }
        void setStartIndex(GLuint index)
        {
            this->VertexArray::setIndex(index);
        }
        /// @brief 获取index的VBO
        /// @param index 索引
        /// @return VBO
        VertexBuffer& operator[](uint32_t index)
        {
            return this->render_vbos [index];
        }
        /// @brief 启用index指定的顶点属性
        /// @param index 要启用的属性
        void EnableAt(GLuint index)
        {
            index_map[index]->setEnable(true);
            glEnableVertexArrayAttrib(this->array_id, index);
        }

        /// @brief 禁用index指定的顶点属性
        /// @param index 要禁用的属性
        void DisableAt(GLuint index)
        {
            index_map[index]->setEnable(false);
            glDisableVertexArrayAttrib(this->array_id, index);
        }
        /// @brief 绑定自身VAO
        void Bind() const
        {
            this->VertexArray::Bind();
        }
        /// @brief 解绑自身VAO
        void UnBind() const
        {
            this->VertexArray::UnBind();
        }
        /// @brief 设置静态顶点属性
        /// @param index 属性索引
        /// @param v 属性数据
        void setStatic(GLuint index, const void* v);
    };

}

#endif //!RENDER_OBJECT_BASE