#ifndef ELEMENT_RENDER_HPP_FILE
#define ELEMENT_RENDER_HPP_FILE
#include "glad/glad.h"

#include "type_load.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

#include "RenderObject_base.hpp"

#define DEAUFT_ELEMENT_RENDER_VBO_COUNT 1
namespace Engine::Render
{
    /// @brief 使用索引渲染对象
    class ElementRender : public renderobject_base
    {
    private:
        /// @brief 渲染顶点索引数组
        IndexBuffer render_ibo;
        /// @brief 着色器
        Program* render_shader;
    public:
        IndexBuffer& getIBO()
        {
            return this->render_ibo;
        }
        ElementRender(uint32_t vbo_size)
            : renderobject_base(vbo_size), render_ibo(), render_shader(nullptr)
        {}
        ElementRender(const ElementRender& target)
            :renderobject_base(target), render_ibo(target.render_ibo), render_shader(target.render_shader)
        {}
        ElementRender(ElementRender&& target)
            :renderobject_base(forward<renderobject_base>((renderobject_base)target)),
            render_ibo(target.render_ibo), render_shader(target.render_shader)
        {}
        void setProgram(Program& shader)
        {
            render_shader = &shader;
        }
        void RenderAll() const
        {
            this->render_ibo.Bind();
            render_shader->Use();
            glDrawElements(this->render_ibo.GetIndexType(), this->render_ibo.GetIndexCount(),
                this->render_ibo.GetIndexType(), nullptr);
        }
        void RenderAll(Program& shader)
        {
            this->render_ibo.Bind();
            shader.Use();
            glDrawElements(this->render_ibo.GetIndexType(), this->render_ibo.GetIndexCount(),
                this->render_ibo.GetIndexType(), nullptr);
        }
        void RenderStartAt(GLint start) const
        {
            this->render_ibo.Bind();
            render_shader->Use();
            glDrawElementsBaseVertex(this->render_ibo.GetIndexType(), this->render_ibo.GetIndexCount(),
                this->render_ibo.GetIndexType(), nullptr, start);
        }
        void RenderStartAt(GLint start, Program& shader)
        {
            this->render_ibo.Bind();
            shader.Use();
            glDrawElementsBaseVertex(this->render_ibo.GetIndexType(), this->render_ibo.GetIndexCount(),
                this->render_ibo.GetIndexType(), nullptr, start);
        }
    };

}

#endif