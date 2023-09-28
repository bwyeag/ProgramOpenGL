#ifndef SHADER_HPP_FILE
#define SHADER_HPP_FILE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "type_load.hpp"

#include "Error.hpp"

#define DEAUFT_PROGRAM_SHADER_COUNT 2
#define PROGRAM_LOG_MAX_SIZE 8192
namespace Engine::Render
{
    class Shader
    {
    private:
        GLuint shader_id;
        GLenum shader_type;
    public:
        Shader() {};
        Shader(const string& path, GLenum type);
        Shader(const Shader& target)
            :shader_id(target.shader_id), shader_type(target.shader_type)
        {}
        Shader(Shader&& target) noexcept
            :shader_id(target.shader_id), shader_type(target.shader_type)
        {
            target.shader_id = 0;
        }
        Shader& operator=(const Shader& target)
        {
            this->shader_id = target.shader_id;
            this->shader_type = target.shader_type;

            return *this;
        }
        Shader& operator=(Shader&& target) noexcept
        {
            if (&target == this)
            {
                return *this;
            }
            this->shader_id = target.shader_id;
            this->shader_type = target.shader_type;

            target.shader_id = 0;
            return *this;
        }
        ~Shader()
        {
            glDeleteShader(this->shader_id);
        }
        GLuint GetID() const { return this->shader_id; }

    };

    class Program
    {
    private:
        GLuint program_id;
        vector<Shader> program_shader;
        mutable map<string, GLint> shader_uniformmap;
        void PrintLog() const;
        GLint GetUniformLocation(const string& target) const;
        GLint GetUniformBlockLocation(const string& target) const;
    public:
        Program(GLuint n = DEAUFT_PROGRAM_SHADER_COUNT)
        {
            if (n != 0)
            {
                program_shader.reserve(n);
                this->program_id = glCreateProgram();
            }
        }
        Program(const Program& target)
            :program_id(target.program_id), program_shader(target.program_shader),
            shader_uniformmap(target.shader_uniformmap)
        {}
        Program(Program&& target) noexcept
            :program_id(target.program_id),
            program_shader(forward<vector<Shader> >(target.program_shader)),
            shader_uniformmap(forward<map<string, GLint> >
                (target.shader_uniformmap))
        {
            target.program_id = 0;
        }
        Program& operator=(const Program& target)
        {
            this->program_id = target.program_id;
            this->program_shader = target.program_shader;
            this->shader_uniformmap = target.shader_uniformmap;
            return *this;
        }
        Program& operator=(Program&& target) noexcept
        {
            if (&target == this)
            {
                return *this;
            }
            this->program_id = target.program_id;
            this->program_shader = forward<vector<Shader> >(target.program_shader);
            this->shader_uniformmap = forward<map<string, GLint> >
                (target.shader_uniformmap);
            target.program_id = 0;
            return *this;
        }
        Shader& operator[](size_t index)
        {
            return this->program_shader [index];
        }
        ~Program()
        {
            glDeleteProgram(this->program_id);
        }
        void UseShader(Shader& t)
        {
            this->program_shader.push_back(t);
            glAttachShader(this->program_id, (this->program_shader.back()).GetID());
        }
        void MoveShader(Shader&& t)
        {
            this->program_shader.push_back(forward<Shader>(t));
            glAttachShader(this->program_id, (this->program_shader.back()).GetID());
        }
        void Use() const
        {
            glUseProgram(this->program_id);
        }
        void UnUse() const
        {
            glUseProgram(0);
        }
        void Link() const
        {
            glLinkProgram(this->program_id);
            this->PrintLog();
        }

        void useUniformBlockAt(const string& name, GLuint index)
        {
            GLint location = GetUniformBlockLocation(name);
            if (location != -1)
                glUniformBlockBinding(this->program_id, location, index);
        }
        //设置纹理，使value对应的纹理单元被使用（注：先glActiveTexture）
        void setTexture(const string& name, int unit)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1i(location, unit);
        }
        //设置布尔值
        void setBool(const string& name, bool value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1i(location, (int)value);
        }
        //设置int
        void setInt(const string& name, int value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1i(location, value);
        }
        //设置uint
        void setUint(const string& name, uint32_t value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1ui(location, value);
        }
        //设置浮点数
        void setFloat(const string& name, float value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1f(location, value);
        }
        //设置二维向量（float）
        void setVec2(const string& name, const glm::vec2& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2fv(location, 1, &value [0]);
        }
        //设置二维向量（float）
        void setVec2(const string& name, float x, float y)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2f(location, x, y);
        }

        //设置三维向量（float）
        void setVec3(const string& name, const glm::vec3& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3fv(location, 1, &value [0]);
        }
        //设置三维向量（float）
        void setVec3(const string& name, float x, float y, float z)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3f(location, x, y, z);
        }

        //设置四维向量（float）
        void setVec4(const string& name, const glm::vec4& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4fv(location, 1, &value [0]);
        }
        //设置四维向量（float）
        void setVec4(const string& name, float x, float y, float z, float w)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4f(location, x, y, z, w);
        }

        //设置2*2矩阵（float）
        void setMat2(const string& name, const glm::mat2& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix2fv(location, 1, GL_FALSE, &mat [0][0]);
        }
        //设置3*3矩阵（float）
        void setMat3(const string& name, const glm::mat3& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix3fv(location, 1, GL_FALSE, &mat [0][0]);
        }
        //设置4*4矩阵（float）
        void setMat4(const string& name, const glm::mat4& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix4fv(location, 1, GL_FALSE, &mat [0][0]);
        }
        //设置双精度浮点数
        void setDouble(const string& name, double value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform1d(location, value);
        }
        //设置二维向量（double）
        void setVec2(const string& name, const glm::dvec2& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2dv(location, 1, &value [0]);
        }
        //设置二维向量（double）
        void setVec2(const string& name, double x, double y)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2d(location, x, y);
        }

        //设置三维向量（double）
        void setVec3(const string& name, const glm::dvec3& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3dv(location, 1, &value [0]);
        }
        //设置三维向量（double）
        void setVec3(const string& name, double x, double y, double z)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3d(location, x, y, z);
        }

        //设置四维向量（double）
        void setVec4(const string& name, const glm::dvec4& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4dv(location, 1, &value [0]);
        }
        //设置四维向量（double）
        void setVec4(const string& name, double x, double y, double z, double w)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4d(location, x, y, z, w);
        }

        //设置2*2矩阵（double）
        void setMat2(const string& name, const glm::dmat2& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix2dv(location, 1, GL_FALSE, &mat [0][0]);
        }
        //设置3*3矩阵（double）
        void setMat3(const string& name, const glm::dmat3& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix3dv(location, 1, GL_FALSE, &mat [0][0]);
        }
        //设置4*4矩阵（double）
        void setMat4(const string& name, const glm::dmat4& mat)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniformMatrix4dv(location, 1, GL_FALSE, &mat [0][0]);
        }

        //设置二维向量（int）
        void setVec2(const string& name, const glm::ivec2& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2iv(location, 1, &value [0]);
        }
        //设置二维向量（int）
        void setVec2(const string& name, int x, int y)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2i(location, x, y);
        }

        //设置三维向量（int）
        void setVec3(const string& name, const glm::ivec3& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3iv(location, 1, &value [0]);
        }
        //设置三维向量（int）
        void setVec3(const string& name, int x, int y, int z)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3i(location, x, y, z);
        }

        //设置四维向量（int）
        void setVec4(const string& name, const glm::ivec4& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4iv(location, 1, &value [0]);
        }
        //设置四维向量（int）
        void setVec4(const string& name, int x, int y, int z, int w)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4i(location, x, y, z, w);
        }
        //设置二维向量（uint32_t）
        void setVec2(const string& name, const glm::uvec2& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2uiv(location, 1, &value [0]);
        }
        //设置二维向量（uint32_t）
        void setVec2(const string& name, uint32_t x, uint32_t y)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform2ui(location, x, y);
        }

        //设置三维向量（uint32_t）
        void setVec3(const string& name, const glm::uvec3& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3uiv(location, 1, &value [0]);
        }
        //设置三维向量（uint32_t）
        void setVec3(const string& name, uint32_t x, uint32_t y, uint32_t z)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform3ui(location, x, y, z);
        }

        //设置四维向量（uint32_t）
        void setVec4(const string& name, const glm::uvec4& value)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4uiv(location, 1, &value [0]);
        }
        //设置四维向量（uint32_t）
        void setVec4(const string& name, uint32_t x, uint32_t y, uint32_t z, uint32_t w)
        {
            GLint location = GetUniformLocation(name);
            if (location != -1)
                glUniform4ui(location, x, y, z, w);
        }
    };
}
#endif //!SHADER_HPP_FILE