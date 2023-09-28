#ifndef TRANSFORM_HPP_FILE
#define TRANSFORM_HPP_FILE
#include "type_load.hpp"
// 未完成 <2023/8/19/13:21>

namespace Engine
{
    struct Transform
    {
        vec3 position;
        vec3 scale;
        quat rotate;

        void setRotate(quat q)
        {
            this->rotate = q;
        }
        void setRotate(vec3 e)
        {
            this->rotate = quat(e);
        }
        void addRotate(quat q)
        {
            this->rotate = q * this->rotate;
        }
        void addRotate(vec3 e)
        {
            this->rotate = quat(e) * this->rotate;
        }
    };

} // namespace Engine

#endif //! TRANSFORM_HPP_FILE