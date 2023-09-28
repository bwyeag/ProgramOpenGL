#ifndef RENDER_SYSTEM_HPP_FILE
#define RENDER_SYSTEM_HPP_FILE
#include "glad/glad.h"
#include "type_load.hpp"
#include "ElementRender.hpp"
#include "ArrayRender.hpp"
#include "Light.hpp"

#include "Error.hpp"

#include <vector>
namespace Engine::Render
{
    vec3 GetUp(vec3 d)
    {
        if (d.x != 0.0f)
        {
            return vec3(-d.z / d.x, 0.0f, 1.0f);
        }
        else
        {
            return vec3(1.0f, 0.0f, 0.0f);
        }
    }
    struct init_size
    {
        size_t ele, arr, spot, point, dir;
        GLsizei tex_x, tex_y;
    } struct ele_render_data
    {
        bool isEnable;
        mat4 model;
        ElementRender *render;
        void Enable()
        {
            isEnable = true;
        }
        void Disable()
        {
            isEnable = false;
        }
    } struct arr_render_data
    {
        bool isEnable;
        mat4 model;
        ArrayRender *render;
        void Enable()
        {
            isEnable = true;
        }
        void Disable()
        {
            isEnable = false;
        }
    } class Renderer
    {
    private:
        vector<ele_render_data> ele_obj;
        vector<arr_render_data> arr_obj;

        vector<SpotLight> spot_lights;
        vector<PointLight> point_lights;
        vector<DirectLight> dir_lights;

        vector<mat4> spot_views;
        vector<mat4> point_views;
        vector<mat4> dir_views;

        mat4 spot_proj;

        mat4 view_mat;
        mat4 proj_mat;

        GLsizei tex_x, tex_y;

        GLuint depthMapFBO;
        GLuint sampler, cube_sampler;
        GLuint spot_depth, point_depth, dir_depth;

    public:
        mat4 &getView() { return this->view_mat; }
        mat4 &getProject() { return this->proj_mat; }
        size_t getObjCount() { return ele_obj.size() + arr_obj.size(); }
        arr_render_data *addArrRender(ArrayRender *render, const mat4 &model)
        {
            arr_obj.push_back({true, render, model});
            return &arr_obj[arr_obj.size() - 1];
        }
        ele_render_data *addArrRender(ElementRender *render, const mat4 &model)
        {
            ele_obj.push_back({true, render, model});
            return &ele_obj[ele_obj.size() - 1];
        }
        arr_render_data *getArrRenderAt(size_t index) { return &arr_obj[index]; }
        ele_render_data *getEleRenderAt(size_t index) { return &ele_obj[index]; }

        SpotLight *addSpotLight(const SpotLight &data)
        {
            spot_lights.push_back(data);
            spot_views.push_back(lookAt(data.position, data.position + data.direction), GetUp(data.direction));
            return spot_lights[spot_lights.size() - 1];
        }
        PointLight *addPointLight(const PointLight &data) { return point_lights[index]; }
        DirectLight *addDirectLight(const DirectLight &data) { return dir_lights[index]; }

        SpotLight &getSpotLightAt(size_t index) { return spot_lights[index]; }
        PointLight &getPointLightAt(size_t index) { return point_lights[index]; }
        DirectLight &getDirectLightAt(size_t index) { return dir_lights[index]; }
        void RenderObjs()
        {
        }

    public:
        Renderer(const init_size &init)
        {
            GLint array_max;
            glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &array_max);
            if (init.spot > array_max || init.point > array_max / 6 || init.dir > array_max)
            {
                ERROR("OpenGL", "请求的纹理数组层级超出OpenGL限制(各请求的数目:)")
                ERRORINFO(init.spot << init.point << init.dir)
            }
            ele_obj.reserve(init.ele);
            arr_obj.reserve(init.arr);
            spot_lights.reserve(init.spot);
            point_lights.reserve(init.point);
            dir_lights.reserve(init.dir);

            spot_views.reserve(init.spot);
            point_views.reserve(init.point);
            dir_views.reserve(init.dir);

            tex_x = init.tex_x;
            tex_y = init.tex_y;

            glCreateSamplers(1, &sampler);
            glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
            glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glSamplerParameterf(sampler, GL_TEXTURE_BORDER_COLOR, (GLfloat)1.0f);

            glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &spot_depth);
            glTextureStorage3D(spot_depth, 1, GL_R32F, tex_x, tex_y, init.spot);

            glCreateTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &point_depth);
            glTextureStorage3D(point_depth, 1, GL_R32F, tex_x, tex_y, init.point * 6);

            glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &dir_depth);
            glTextureStorage3D(dir_depth, 1, GL_R32F, tex_x, tex_y, init.dir);

            glCreateFramebuffers(1, &depthMapFBO);
        }
        Renderer(const Renderer &) = delete;
        void operator=(const Renderer &) = delete;
        Renderer(Renderer &&) = delete;
        void operator=(const Renderer &&) = delete;
        ~Renderer()
        {
        }
    };

} // namespace Engine::Render

#endif //! RENDER_SYSTEM_HPP_FILE