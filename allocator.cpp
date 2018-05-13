//
//  allocator.cpp
//  XorList
//
//  Created by Никита on 16.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//
#pragma once
#include "allocator.h"
#include <cmath>

static constexpr size_t _BLOCK_DEFAULT_SIZE = 4096;

template<typename T>
StackAllocator<T>::StackAllocator() : _free(0), _used(0), _current(nullptr) {}

template<typename T>
StackAllocator<T>::~StackAllocator() {
    _current = nullptr;
    _blocks.destruct();
}

template<typename T>
void StackAllocator<T>::create_new_block(size_t size) {
    auto div_rounded_up = [](const auto& A, const auto& B) {return A % B ? A / B + 1 : A / B;};
    _used = std::max(size_t(1), div_rounded_up(size, _BLOCK_DEFAULT_SIZE)) * _BLOCK_DEFAULT_SIZE;
    _free = _used;
    _current = ::operator new(size);
    _blocks.add(_current);
}

template<typename T>
void* StackAllocator<T>::alloc_on_current(size_t size) {
    _free -= size;
    auto next = [](void* ptr, size_t size){return static_cast<void*>(static_cast<char*>(ptr) + size);};
    void* p = _current;
    _current = next(_current, size);
    return p;
}

template<typename T>
T* StackAllocator<T>::allocate(size_t size) {
    size_t allcSize = size * sizeof(T);
    std::align(alignof(T), allcSize, _current, _free);
    if (allcSize > _free) {
        create_new_block(allcSize);
    }
    return static_cast<T*>(alloc_on_current(allcSize));
}

template <typename T>
template <typename U>
void StackAllocator<T>::destroy(U* p) {
    p->~U();
}

template <typename T>
void StackAllocator<T>::deallocate(T* p, size_t size) {}

template <typename T>
template <typename U>
StackAllocator<T>::StackAllocator(const StackAllocator<U>&) {
    _free = 0;
    _used = 0;
    _current = nullptr;
}

template <typename T>
template<typename U, class... Args>
void StackAllocator<T>::construct(U* ptr, Args&&... args ) {
    ::new((void*)ptr) U(std::forward<Args>(args)...);
};

