#ifndef LOAD_TYPE_HPP_FILE
#define LOAD_TYPE_HPP_FILE

#include "type_load.hpp"
#include "layout_element.hpp"
#include <vector>
#include <cstdint>

namespace Engine::Load
{
    struct image_data
    {
        int width, height, channels;
        void *ptr;
    };

    /// @brief 网格节点对象
    struct MeshNode
    {
        /// @brief 节点网格数量
        uint32_t numMesh;
        /// @brief 节点次节点数量
        uint32_t numNode;
        /// @brief 网格指针索引
        uint32_t meshRoot;       
        /// @brief 次节点指针索引
        uint32_t nodeRoot;

    };
    struct NodePointer
    {
        uint32_t nodeIndex;
        uint32_t nextIndex;
    };
    struct MeshPointer
    {
        uint32_t meshIndex;
        uint32_t nextIndex;
    };
    struct MeshData
    {
        uint32_t numVertex,numIndex,vertexSize,layoutSize;
        Render::layout_element* layout;
        void* vertexData;
        uint32_t* indexData;
    };
    
    struct MeshFileData
    {
        uint64_t code = 0xF2023F02;
        uint64_t nodeOffset, nodeptrOffset, meshOffset, meshptrOffset;
        uint32_t numNode, numNodePtr, numMesh, numMeshPtr; 
        vector<MeshNode> nodes;
        vector<NodePointer> nodeptrs;
        vector<MeshData> meshs;        
        vector<MeshPointer> meshptrs;        
    };


} // namespace Engine::Load

#endif //! LOAD_TYPE_HPP_FILE