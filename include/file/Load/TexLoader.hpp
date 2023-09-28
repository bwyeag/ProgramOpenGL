#ifndef TEXLOADER_HPP_FILE
#define TEXLOADER_HPP_FILE

#include "Texture2D.hpp"
#include "type_load.hpp"
#include "LoadType.hpp"
#include "Error.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine::Load
{
    inline void texture_load(const string &path, image_data &output)
    {
        output.ptr = stbi_load(path.c_str(), &output.width, &output.height, &output.channels, 0);
        if (output.ptr == nullptr)
        {
            ERROR("LOADING", "图像文件打开错误")
            ERRORINFO("路径：" << path);
        }
    }
    inline void texture_load_end(image_data &input)
    {
        stbi_image_free(input.ptr);
        input.ptr = nullptr;
    }
} // namespace Engine::Load

#endif //! TEXLOADER_HPP_FILE