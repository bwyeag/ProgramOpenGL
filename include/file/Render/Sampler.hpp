#ifndef SAMPLER_HPP_FILE
#define SAMPLER_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "Error.hpp"

namespace Sampler
{
    class Sampler
    {
    private:
        GLuint sampler_id;
    public:
        Sampler()
        {
            glCreateSamplers(1,&sampler_id);
        }
        ~Sampler()
        {
            glDeleteSamplers(1,&sampler_id);
        }
    };
    
} // namespace Sampler

#endif //!SAMPLER_HPP_FILE