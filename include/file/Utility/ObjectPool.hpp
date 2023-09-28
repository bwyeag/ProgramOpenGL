#ifndef OBJECTPOOL_HPP_FILE
#define OBJECTPOOL_HPP_FILE
#include <vector>
#include <algorithm>
#include <cstdint>
#include <new>
#include "ERROR.hpp"
using std::vector;
using std::max;

namespace Engine
{
    template<typename Type, size_t N>
    struct obj_block
    {
        union block
        {
            Type* ptr;
            Type obj;
        } data[N];
    };

    template<typename Type, size_t N = 32>
    class ObjectPool
    {
    private:
        std::vector<obj_block<Type,N>*> blockPointers;
        Type* nullobjRoot;
        Type* nullobjBack;
    public:
        ObjectPool(size_t init_blocks)
        {
            init_blocks = max(init_blocks,1UL);
            obj_block<Type,N>* ptr;
            size_t i,j;
            for (i = 0; i < init_blocks; i++)
            {
                ptr = new obj_block<Type,N>();
                if (ptr == nullptr)
                {
                    ERROR("MEMORY","内存耗尽!")
                }
                blockPointers.push_back(ptr);
            }
            std::sort(blockPointers.begin(),blockPointers.back());
            Type** tmp, last = &nullobjRoot;
            for (i = 0; i < init_blocks; i++)
            {
                ptr = blockPointers[i];
                for (j = 0; j < N; j++)
                {
                    tmp = &ptr->data[j].ptr;
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
            obj_block<Type,N>* ptr = new obj_block<Type,N>();
            if (ptr == nullptr)
            {
                ERROR("MEMORY","内存耗尽!")
            }
            blockPointers.push_back(ptr);
            std::sort(blockPointers.begin(),blockPointers.back());
            Type** tmp, last = &nullobjBack;
            for (j = 0; j < N; j++)
            {
                tmp = &ptr->data[j].ptr;
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