#ifndef TEXTURE3D_HPP_FILE
#define TEXTURE3D_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "Texture.hpp"

namespace Engine::Render
{
    class Texture3D : public Texture
    {
    private:
        GLsizei mipmap_level;
        GLenum data_type;
        GLsizei data_width, data_height, data_depth;

    public:
        Texture3D(GLsizei mipmap, GLenum type, GLsizei width, GLsizei height, GLsizei depth)
            : Texture(GL_TEXTURE_3D), mipmap_level(mipmap), data_type(type), data_width(width), data_height(height), data_depth(depth)
        {
            glTextureStorage3D(this->texture_id, this->mipmap_level, this->data_type, this->data_width, this->data_height, this->data_depth);
        }
        ~Texture3D();
    };
} // namespace Engine::Render
#endif //!TEXTURE3D_HPP_FILE