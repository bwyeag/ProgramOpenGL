#ifndef ENCLOSUREBOX_HPP_FILE
#define ENCLOSUREBOX_HPP_FILE
#include "type_load.hpp"

namespace Engine
{
    /// @brief 球包围盒结构
    struct shpere_collision
    {
        vec3 pos;
        float radius;
    };
    /// @brief 轴对齐包围盒结构
    struct axis_collision
    {
        vec3 min_pos;
        vec3 max_pos;
    };
} // namespace Engine
#endif //!ENCLOSUREBOX_HPP_FILE