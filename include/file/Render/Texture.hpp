#ifndef TEXTURE_HPP_FILE
#define TEXTURE_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"

namespace Engine::Render
{
    class Texture
    {
    protected:
        GLuint texture_id;
        GLenum texture_type;
    public:
        Texture(GLenum texture_type)
        {
            glCreateTextures(texture_type, 1, &texture_id);
        }
        ~Texture()
        {
            glDeleteTextures(1, &texture_id)
        }
        void BindTo(GLuint unit)
        {
            glBindTextureUnit(unit, this->texture_id);
        }
        static void UnBindAt(GLuint unit)
        {
            glBindTextureUnit(unit, 0);
        }
    };
    
} // namespace Engine::Render

#endif //!TEXTURE_HPP_FILE