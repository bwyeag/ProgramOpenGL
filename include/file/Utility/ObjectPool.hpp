#ifndef OBJECTPOOL_HPP_FILE
#define OBJECTPOOL_HPP_FILE
#include <vector>
#include <algorithm>
#include <cstdint>
#include <new>
#include <iostream>

#define ERROR(type,info) std::cerr << "[ERROR][" << type << "]file:" << __FILE__ << ";line:" << __LINE__ << "|info:" << info << std::endl;

using std::vector;
using std::max;

namespace Engine
{
    template<typename Type, size_t blockSize>
    class ObjectPool
    {
    private:
        struct obj_block
        {
            union block
            {
                Type* ptr;
                Type obj;
            } data[blockSize];
        };

        std::vector<obj_block*> blockPointers;
        Type* nullobjRoot;
        Type* nullobjBack;
    public:
        ObjectPool(size_t init_blocks)
        {
            init_blocks = max(init_blocks,(size_t)1);
            obj_block* ptr;
            blockPointers.resize(init_blocks);
            size_t i,j;
            for (i = 0; i < init_blocks; i++)
            {
                ptr = new obj_block();
                if (ptr == nullptr)
                {
                    ERROR("MEMORY","内存耗尽!")
                }
                blockPointers[i] = ptr;
            }
            std::sort(blockPointers.begin(),blockPointers.end(),std::greater<obj_block*>());

            Type** tmp, **last = &nullobjRoot;
            for (i = 0; i < init_blocks; i++)
            {
                ptr = blockPointers[i];
                for (j = 0; j < blockSize; j++)
                {
                    tmp = &(ptr->data[j].ptr);
                    *last = (Type*)tmp;
                    last = tmp;
                }
            }
            *last = nullptr;
            nullobjBack = (Type*)last;
        }
        Type* allocate()
        {
            if (nullobjRoot == nullobjBack)
            {
                alloc_block();
                return allocate();
            }
            else
            {
                Type* r = nullobjRoot;
                nullobjRoot = *(Type**)nullobjRoot;
                return r;
            }
        }
        void alloc_block()
        {
            obj_block* ptr = new obj_block();
            if (ptr == nullptr)
            {
                ERROR("MEMORY","内存耗尽!")
            }
            blockPointers.push_back(ptr);
            std::sort(blockPointers.begin(),blockPointers.end(),std::greater<obj_block*>());

            *(Type**)nullobjBack = (Type*)&(ptr->data[0].ptr);
            Type** tmp, **last = &(ptr->data[0].ptr);
            for (size_t j = 1; j < blockSize; j++)
            {
                tmp = &(ptr->data[j].ptr);
                *last = (Type*)tmp;
                last = tmp;
            }
            *last = nullptr;
            nullobjBack = (Type*)last;
        }
        void deallocate(Type* obj)
        {
            *(Type**)nullobjBack = obj;
            *(Type**)obj = nullptr;
            nullobjBack = obj;
        }
        ~ObjectPool()
        {
            for (size_t i = 0; i < blockPointers.size(); i++)
            {
                delete blockPointers[i];
            }
            nullobjRoot = nullptr;
        }
    };
} // namespace Engine

#endif //!OBJECTPOOL_HPP_FILE