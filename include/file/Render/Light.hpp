#ifndef LIGHT_HPP_FILE
#define LIGHT_HPP_FILE
#include "type_load.hpp"

namespace Engine::Render
{
    struct PointLight       //点光源
    {
        bool isEnabled;     //是否启用
        vec3 position;      //位置
        vec3 ambient;       //环境光分量
        vec3 color;         //光源颜色
        float strength;     //强度
        float attenuation;  //光照衰减
    }
    struct DirectLight      //方向光
    {
        bool isEnabled;     //是否启用
        vec3 direction;     //方向
        vec3 ambient;       //环境光分量
        vec3 color;         //光源颜色
        float strength;     //强度
    }
    struct SpotLight        //聚光灯
    {
        bool isEnabled;     //是否启用
        vec3 position;      //位置
        vec3 direction;     //方向
        vec3 ambient;       //环境光分量
        vec3 color;         //光源颜色
        float strength;     //强度
        float attendistance;//光照衰减值(的平方)
        float attenuation;  //光照衰减
        float outerangle;   //外切光角(的余弦值)
        float innerangle;   //内切光角(的余弦值)
    }
} // namespace Engine::Render
#endif //!LIGHT_HPP_FILE