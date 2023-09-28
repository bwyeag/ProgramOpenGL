#ifndef MODEL_LOAD_HPP_FILE
#define MODEL_LOAD_HPP_FILE

#include "glad/glad.h"
#include "type_load.hpp"
#include "Error.hpp"
#include "layout_element.hpp"
#include "LoadType.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "assimp/Importer.hpp "
#include "assimp/scene.h "
#include "assimp/postprocess.h "

namespace Engine::Load
{
    void loadModel(const string &path, const string &writepath);
    void processNode(MeshNode* meshnode, aiNode *node, const aiScene *scene, MeshFileData &data);
    void processMesh(MeshData* meshdata, aiMesh *mesh, const aiScene *scene, MeshFileData &data);
} // namespace Engine::Load

#endif //! MODEL_LOAD_HPP_FILE