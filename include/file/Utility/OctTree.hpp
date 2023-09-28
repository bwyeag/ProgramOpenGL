#ifndef OCTTREE_HPP_FILE
#define OCTTREE_HPP_FILE
#include "type_load.hpp"
#include "EnclosureBox.hpp"
#include "ObjectPool.hpp"
#define TREE_VECTOR_MIN_COUNT 16
#define TREE_MAX 512.0f

namespace Engine
{
    /// @brief 八叉数物件
    template<typename Type>
    struct object
    {
        node<Type>* father;
        axis_collision box;
        Type data;
    };
    
    /// @brief 八叉树节点
    template<typename Type>
    struct node
    {
        /// @brief 节点的父节点
        node<Type>* father;
        /// @brief 节点数据
        /// @details 最高一个字节如果为0xFF,则为叶节点,为0x00则为干节点
        ///          第一个字节为节点数量
        uint64_t code;
        /// @brief 八个卦限方向上的子节点
        union
        {
            object<Type>* objptr;
            node<Type>* nodeptr;
        }children[8];
        /// @brief 包围盒
        axis_collision box;

        inline bool isLeaf() const
        {
            return ((this->code & 0xFF00000000000000) == 0xFF00000000000000);
        }
        inline bool isNode() const
        {
            return ((this->code & 0xFF00000000000000) == 0x0000000000000000);
        }
        inline bool isFull() const
        {
            return (this->getChildCount() > 7);
        }
        inline uint8_t getChildCount() const
        {
            return static_cast<uint8_t>(this->code & 0x00000000000000FF);
        }
        inline void addChild(uint64_t child)
        {
#ifdef _DEBUG
            if (this->isFull())
            {
                return;
            }
#endif
            this->children[this->getChildCount()] = child;
            this->code++;
            return;
        }

        inline void setNullNext(uint64_t next)
        {
            // this->father = 0;
            // this->children[0] = 0;
            // this->children[1] = 0;
            // this->children[2] = 0;
            // this->children[3] = 0;
            // this->children[4] = 0;
            // this->children[5] = 0;
            // this->children[6] = 0;
            // this->children[7] = 0;
            // this->box.max.x = 0.0f;
            // this->box.min.x = 0.0f;
            // this->box.max.y = 0.0f;
            // this->box.min.y = 0.0f;            
            // this->box.max.z = 0.0f;
            // this->box.min.z = 0.0f;

            this->code = next;
        }
        inline uint64_t getNullNext() const
        {
            return this->code;
        }
    };

    template<typename Type, size_t N = 32>
    class OctTree
    {
    private:
        ObjectPool<node<Type>, N> node_data;
        ObjectPool<object<Type>, N> obj_data;
        node<Type>* node_root;
    public:
        OctTree(size_t init_blocks) : node_data(init_blocks), obj_data(init_blocks)
        {
            node_root = node_data.allocate()
        }
    };
} // namespace Engine

#endif //!OCTTREE_HPP_FILE