#include "Shader.hpp"

namespace Engine::Render
{        
    Shader::Shader(const string& path, GLenum type)
        :shader_type(type)
    {

        ifstream reader(path, std::ios::in);
        if (!reader.is_open())
        {
            this->shader_id = 0;
            ERROR("Engine","未能成功打开文件：")
            ERRORINFO(path)
            return;
        }
        string shader_code((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
        reader.close();

        this->shader_id = glCreateShader(type);
        const char* res = shader_code.c_str();
        const GLint length = static_cast<GLint>(shader_code.size());
        glShaderSource(this->shader_id, 1, &res, &length);
        glCompileShader(this->shader_id);

        GLint success;
        glGetShaderiv(this->shader_id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            int length;
            glGetShaderiv(this->shader_id, GL_INFO_LOG_LENGTH, &length);
            ERROR("OpenGL","着色器编译失败:\n着色器文件:")
            ERRORINFO(shader_code << "\n----------------------------------------")
            char* log = (char*)malloc(sizeof(char) * length);
            if (log == nullptr)
            {
                ERROR("OpenGL","日志内存申请失败")
                throw std::bad_alloc();
            }
            else
            {
                glGetShaderInfoLog(this->shader_id, length, &length, log);
                ERROR("OpenGL","错误信息：\n")
                ERRORINFO("错误信息：\n" << log)
                free(log);
            }
        }
        return;
    }
    GLint Program::GetUniformLocation(const string& target) const
    {
        if (shader_uniformmap.find(target) != shader_uniformmap.end())
            return shader_uniformmap [target];
        GLint location = glGetUniformLocation(this->program_id, target.c_str());
        if (location != -1)
            shader_uniformmap [target] = location;
        return location;
    }
    GLint Program::GetUniformBlockLocation(const string& target) const
    {
        if (shader_uniformmap.find(target) != shader_uniformmap.end())
            return shader_uniformmap [target];
        GLint location = glGetUniformBlockIndex(this->program_id, target.c_str());
        if (location != -1)
            shader_uniformmap [target] = location;
        return location;
    }
    void Program::PrintLog() const
    {
        GLint success;
        glGetProgramiv(this->program_id, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLsizei length;
            glGetProgramiv(this->program_id, GL_INFO_LOG_LENGTH, &length);
            ERROR("OpenGL","着色器程序链接错误")
            char* log = (char*)malloc(length);
            if (log == nullptr)
            {
                ERROR("OpenGL","日志内存申请失败")
                throw std::bad_alloc();
            }
            else
            {
                glGetProgramInfoLog(this->program_id, PROGRAM_LOG_MAX_SIZE, nullptr, log);
                ERROR("OpenGL","错误信息：")
                ERRORINFO(log)
                free(log);
            }
        }
    }

}