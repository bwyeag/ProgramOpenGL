#include "ModelLoad.hpp"

namespace Engine::Load
{
    void loadModel(const string &path, const string &writepath)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            ERROR("LOADING", "模型加载错误或找不到文件")
            return;
        }

        MeshFileData data = MeshFileData();

        data.numNode = 1+scene->mRootNode->mNumChildren;
        data.numNodePtr = scene->mRootNode->mNumChildren;
        ata.numMeshPtr = scene->mRootNode->mNumMeshes;
        data.numMesh = scene->mRootNode->mNumMeshes;
        data.nodes.push_back({scene->mRootNode->mNumMeshes,
                              scene->mRootNode->mNumChildren,
                              0, 0});
        for (uint32_t i = 0; i < scene->mRootNode->mNumMeshes; i++)
        {
            data.meshs.push_back({0,0,0,0,nullptr,nullptr,nullptr});
            data.meshptrs.push_back({i,i+1});
        }
        data.meshptrs[data.meshptrs.size()-1].nextIndex = UINT32_MAX;
        
        for (uint32_t i = 0; i < scene->mRootNode->mNumChildren; i++)
        {
            data.nodes.push_back({0,0,0,0});
            data.nodeptrs.push_back({i+1,i+1});
        }
        data.nodeptrs[data.nodeptrs.size()-1].nextIndex = UINT32_MAX;
        
        for (uint32_t i = 0; i < scene->mRootNode->mNumChildren; i++)
        {
            processNode(&data.nodes[i+1], scene->mRootNode->mChildren[i], scene, data);
        }

        for (uint32_t i = 0; i < scene->mRootNode->mNumMeshes; i++)
        {
            processMesh(&data.meshs[i],scene->mRootNode->mMeshes[i],scene,data);
        }

        size_t writeoffset;
        std::ofstream modelfile(writepath,std::ios::trunc|std::ios::out|std::ios::binary);
        if (!modelfile.is_open())
        {
            return;
        }
        
        data.nodeOffset = sizeof(uint64_t)*5+sizeof(uint32_t)*4;
        data.nodeptrOffset = data.nodeOffset + data.numNode * sizeof(MeshNode);
        data.meshOffset = data.nodeptrOffset + data.numNodePtr * sizeof(NodePointer);
        data.meshptrOffset = data.meshOffset + data.numMesh * sizeof(MeshData);
        size_t writeoffset = data.meshptrOffset + data.numMeshPtr*sizeof(MeshPointer);

        modelfile.write(&data,sizeof(uint64_t)*5+sizeof(uint32_t)*4);
        modelfile.write(&data.nodes[0],data.nodes.size() * sizeof(MeshNode));
        modelfile.write(&data.nodeptrs[0],data.nodeptrs.size() * sizeof(NodePointer));
        modelfile.seekp(data.meshs.size() * sizeof(MeshData),std::ios::cur);
        modelfile.write(&data.meshptrs[0],data.meshptrs.size() * sizeof(MeshPointer));

        void* ptrtmp;
        for (MeshData& md : data.meshs)
        {
            ptrtmp = md.layout;
            md.layout = modelfile.tellp();
            modelfile.write(ptrtmp,md.layoutSize);
            free(ptrtmp);

            ptrtmp = md.vertexData;
            md.vertexData = modelfile.tellp();
            modelfile.write(ptrtmp,md.vertexSize*md.numVertex);
            free(ptrtmp);

            ptrtmp = md.indexData;
            md.indexData = modelfile.tellp();
            modelfile.write(ptrtmp,sizeof(uint32_t)*md.numIndex);
            free(ptrtmp);
        }

        modelfile.seekp(data.meshOffset,std::ios::beg);
        modelfile.write(&data.meshs[0],data.meshs.size() * sizeof(MeshData));
        
        modelfile.close();
        return;
    }
    void processNode(MeshNode* meshnode, aiNode *node, const aiScene *scene, MeshFileData &data)
    {
        uint32_t meshstart = static_cast<uint32_t>(data.meshs.size());
        uint32_t meshptrstart = static_cast<uint32_t>(data.meshptrs.size());
        meshnode->numMesh = node->mNumMeshes;
        meshnode->meshRoot = meshptrstart;
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            data.numMesh += node->mNumMeshes;
            data.numMeshPtr += node->mNumMeshes;
            data.meshs.push_back({0,0,0,0,nullptr,nullptr,nullptr});
            data.meshptrs.push_back({meshstart+i,meshptrstart+i+1});
        }
        data.meshptrs[data.meshptrs.size()-1].nextIndex = UINT32_MAX;

        uint32_t nodestart = static_cast<uint32_t>(data.nodes.size());
        uint32_t nodeptrstart = static_cast<uint32_t>(data.nodeptrs.size());
        meshnode->numNode = node->mNumChildren;
        meshnode->nodeRoot = nodeptrstart;
        for (uint32_t i = 0; i < node->mNumChildren; i++)
        {
            data.numNode += node->mNumChildren;
            data.numNodePtr += node->mNumChildren;
            data.nodes.push_back({0,0,0,0});
            data.nodeptrs.push_back({nodestart+i,nodeptrstart+i+1});
        }
        data.nodeptrs[data.nodeptrs.size()-1].nextIndex = UINT32_MAX;

        for (uint32_t i = 0; i < node->mNumChildren; i++)
        {
            processNode(&data.nodes[nodestart+i], node->mChildren[i], scene, data);
        }

        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            processMesh(&data.meshs[meshstart+i],node->mMeshes[i],scene,data);
        }
    }
    void processMesh(MeshData* meshdata, aiMesh *mesh, const aiScene *scene, MeshFileData &data)
    {
        meshdata->numVertex=mesh->mNumVertices;
        meshdata->numIndex=mesh->mFaces*3;
        auto layouts = new vector<Render::layout_element>();
        layouts->push_back(layout_element(GL_FLOAT,3,GL_FALSE));
        if (mesh->HasNormals())
        {
            layouts->push_back(layout_element(GL_FLOAT,3,GL_FALSE));
        }
        if (mesh->HasTangentsAndBitangents())
        {
            layouts->push_back(layout_element(GL_FLOAT,3,GL_FALSE));
            layouts->push_back(layout_element(GL_FLOAT,3,GL_FALSE));
        }
        if (mesh->GetNumUVChannels()>0)
        {
            for (uint32_t i = 0; i < mesh->GetNumUVChannels(); i++)
            {
                layouts->push_back(layout_element(GL_FLOAT,2,GL_TRUE));
            }
        }
        for (uint32_t i = 0; i < layouts.size(); i++)
        {
            meshdata->vertexSize+=(*layouts)[i].size;
            (*layouts)[i].setIndex(i);
        }
        
        meshdata.layoutSize = sizeof(Render::layout_element)*layouts->size();
        Render::layout_element* layout =
            (Render::layout_element*)malloc(meshdata.layoutSize);
        memcpy(layout,&layouts->[0],meshdata.layoutSize);
        delete(layouts);
        GLfloat* vertexdata = (GLfloat*)malloc(meshdata->numVertex*meshdata->vertexSize);
        uint32_t* indexdata = (uint32_t*)malloc(meshdata->numIndex*sizeof(uint32_t));

        meshdata->layout = layout;
        meshdata->vertexData = vertexdata;
        meshdata->indexData = indexdata;

        size_t size = meshdata->vertexSize / sizeof(GLfloat);

        GLfloat* datapos = vertexdata,datapos2 = vertexdata;
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // positions
            *(datapos+0) = mesh->mVertices[i].x;
            *(datapos+1) = mesh->mVertices[i].y;
            *(datapos+2) = mesh->mVertices[i].z;
            datapos2 += 3;
            // normals
            if (mesh->HasNormals())
            {
                *(datapos2+0) = mesh->mNormals[i].x;
                *(datapos2+1) = mesh->mNormals[i].y;
                *(datapos2+2) = mesh->mNormals[i].z;
                datapos2 += 3;
            }
            // tangent and bitangent
            if (mesh->HasTangentsAndBitangents())
            {
                // tangent
                *(datapos2+0) = mesh->mTangents[i].x;
                *(datapos2+1) = mesh->mTangents[i].y;
                *(datapos2+2) = mesh->mTangents[i].z;
                // bitangent
                *(datapos2+3) = mesh->mBitangents[i].x;
                *(datapos2+4) = mesh->mBitangents[i].y;
                *(datapos2+5) = mesh->mBitangents[i].z;
                datapos2 += 6;
            }
            // texture coordinates
            if(mesh->mTextureCoords[0] != nullptr)
            {
                for (uint32_t j = 0; j < mesh->GetNumUVChannels(); j++)
                {
                    *(datapos2+0) = mesh->mTextureCoords[j][i].x; 
                    *(datapos2+1) = mesh->mTextureCoords[j][i].y;
                    datapos2 += 2;
                }
            }

            datapos += size;
            datapos2 = datapos;
        }
        aiFace face;
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
            {
                *(indexdata) = face.mIndices[j];
                indexdata += 1;
            }
        }
    }
} // namespace Engine::Load