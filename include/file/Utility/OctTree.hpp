#ifndef OCTTREE_HPP_FILE
#define OCTTREE_HPP_FILE
#include "type_load.hpp"
#include "EnclosureBox.hpp"
#include "ObjectPool.hpp"
#include <new>
#define TREE_MAX 512.0f

namespace Engine
{
    template<typename Type, size_t N = 32>
    class OctTree
    {
    private:
        enum NodeType
        {
            Leaf = 0xFFU,Node = 0x00U
        };
        /// @brief 八叉树节点
        struct node
        {
            /// @brief 节点的父节点
            node* father;
            /// @brief 节点数据
            /// @details 最高一个字节如果为0xFF,则为叶节点,为0x00则为干节点
            ///          第一个字节为节点数量
            uint64_t code;
            /// @brief 八个卦限方向上的子节点
            union
            {
                object* objptr;
                node* nodeptr;
            }children[8];
            /// @brief 包围盒
            axis_collision box;
        public:
            inline node(node* f = nullptr, NodeType t = NodeType::Node, const axis_collision& c = {{-TREE_MAX,-TREE_MAX,-TREE_MAX},{TREE_MAX,TREE_MAX,TREE_MAX}})
                :father(f),code(t==NodeType::Node?0x0000000000000000UL,0xFF00000000000000UL),box(c) {}

            inline bool isLeaf() const
            {
                return ((this->code & 0xFF00000000000000UL) == 0xFF00000000000000UL);
            }
            inline bool isNode() const
            {
                return ((this->code & 0xFF00000000000000UL) == 0x0000000000000000UL);
            }
            inline bool isFull() const
            {
                return (this->getChildCount() > 7);
            }
            inline uint8_t getChildCount() const
            {
                return static_cast<uint8_t>(this->code & 0x00000000000000FFUL);
            }
            inline void setToNode()
            {
                code &= 0x00FFFFFFFFFFFFFFUL;
                return;
            }
            inline void setToLeaf()
            {
                code |= 0xFF00000000000000UL;
                return;
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

        };
    public:
        /// @brief 八叉数物件
        struct object
        {
            node* father;
            axis_collision box;
            Type data;
        };
    private:
        ObjectPool<node, N> nodeData;
        ObjectPool<object, N> objData;
        node* nodeRoot;
    public:
        OctTree(size_t init_blocks) : nodeData(init_blocks), objData(init_blocks)
        {
            nodeRoot = new(node_data.allocate()) node();
        }

        object* AddObject(const axis_collision& ac)
        {
            if (IntersectTest(ac,nodeRoot->box))
            {
                
            }
            else
            {
                ERROR("OctTree","物体未处于树中")
            }
        }
    };
} // namespace Engine

#endif //!OCTTREE_HPP_FILE