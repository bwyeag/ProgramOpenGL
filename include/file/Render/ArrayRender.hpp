#ifndef RENDER_OBJECT_HPP_FILE
#define RENDER_OBJECT_HPP_FILE
#include "glad/glad.h"

#include "type_load.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "RenderObject_base.hpp"

#define DEAUFT_RENDER_VBO_COUNT 1
namespace Engine::Render
{
    /// @brief 使用顶点数组渲染对象
    class ArrayRender : public renderobject_base
    {
    private:
        /// @brief 渲染模式（顶点构成方式）
        GLenum draw_mode;
        /// @brief 顶点数目
        GLsizei vertex_count;
        /// @brief 渲染Shader
        Program* render_shader;
    public:
        ArrayRender(uint32_t vbo_size)
            : renderobject_base(vbo_size), render_shader(nullptr)
        {}
        ArrayRender(const ArrayRender& target)
            :renderobject_base(target), draw_mode(target.draw_mode),
            vertex_count(target.vertex_count), render_shader(target.render_shader)
        {}
        ArrayRender(ArrayRender&& target)
            :renderobject_base(forward<renderobject_base>((renderobject_base)target)),
            render_shader(target.render_shader)
        {}
        /// @brief 使用Shader（复制）
        /// @param p 目标
        void setProgram(Program& shader)
        {
            this->render_shader = &shader;
        }        
        void SetDrawMode(GLenum mode)
        {
            this->draw_mode = mode;
        }
        /// @brief 设置顶点数目
        /// @param n 顶点数目
        void SetVertexCount(GLsizei n) { this->vertex_count = n; }
        /// @brief 渲染全部
        void RenderAll() const
        {
            render_shader->Use();
            this->Bind();
            glDrawArrays(this->draw_mode, 0, this->vertex_count);
        }
        void RenderAll(Program& shader) const
        {
            shader.Use();
            this->Bind();
            glDrawArrays(this->draw_mode, 0, this->vertex_count);
        }
        void RenderAll_twice() const
        {
            this->Bind();
            glDrawArrays(this->draw_mode, 0, this->vertex_count);
        }
    };

}
#endif //! RENDER_OBJECT_HPP_FILE