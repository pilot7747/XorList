//
//  allocator.h
//  XorList
//
//  Created by Никита on 16.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#ifndef allocator_h
#define allocator_h
#include <functional>
#include <memory>
#include <cstddef>
#include <cassert>
#include <list>
#include "block_holder.cpp"

template <class T>
class StackAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    
    StackAllocator();
    ~StackAllocator();
    template <typename U>
    explicit StackAllocator(const StackAllocator<U>&);
    
    pointer allocate(size_t size);
    void deallocate(T* ptr, size_t size);
    
    template <typename U>
    void destroy(U* ptr);
    template<typename U, class... Args>
    void construct(U* ptr, Args&&... args);
    
    template<typename U>
    struct rebind { typedef StackAllocator<U> other; };
    
protected:
    std::size_t _free;
    std::size_t _used;
    void* _current;
    void create_new_block(size_t size);
    void* alloc_on_current(size_t size);
    blockHolder _blocks;
};

#endif /* allocator_h */
