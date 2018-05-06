//
//  XorList.cpp
//  XorList
//
//  Created by Nikita Pavlichenko on 29.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#pragma once
#include "XorList.h"

template<class T>
Node<T>* Xor(Node<T>* a, Node<T>* b) {
    return reinterpret_cast<Node<T>*>(reinterpret_cast<long long>(a) ^ reinterpret_cast<long long>(b));
};

template<class T>
Node<T>* next(Node<T>* a, Node<T>* b) {
    return Xor(a, b->pointer);
}

template<class T>
Node<T>* prev(Node<T>* a, Node<T>* b) {
    return Xor(a->pointer, b);
}


template<class T, class allocator>
XorList<T, allocator>::XorList(const allocator& alloc) : _alloc(alloc), _begin(nullptr), _end(nullptr), _size(0) {}

template<class T, class allocator>
XorList<T, allocator>::XorList(size_t count, const T& value, const allocator& alloc) : _alloc(alloc), _begin(nullptr), _end(nullptr), _size(0) {
    for (size_t i = 0; i < count; ++i) {
        this->push_back(value);
    }
}

template<class T, class allocator>
XorList<T, allocator>::XorList(const XorList<T, allocator>& list) {
    for (auto it = list.begin(); it != list.end(); it++) {
        this->push_back(*it);
    }
}

template<class T, class allocator>
XorList<T, allocator>::XorList(XorList<T, allocator>&& list) noexcept : _alloc(list._alloc), _begin(list._begin), _end(list._end), _size(list._size) {
    list._begin = nullptr;
    list._end = nullptr;
}

template<class T, class allocator>
XorList<T, allocator>::~XorList() {
    Node<T>* p1 = nullptr;
    Node<T>* p2 = _begin;
    while (p2 != nullptr) {
        Node<T>* tmp = next(p1, p2);
        p1 = p2;
        _alloc.deallocate(p1, 1);
        p2 = tmp;
    }
}

template<class T, class allocator>
void XorList<T, allocator>::push_back(const T& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = val;
    obj->pointer = nullptr;
    if (_end != nullptr) {
        _end->pointer = Xor(_end->pointer, obj);
        obj->pointer = _end;
        _end = obj;
    } else {
        _begin = _end = obj;
    }
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::push_back(T&& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = std::move(val);
    obj->pointer = nullptr;
    if (_end != nullptr) {
        _end->pointer = Xor(_end->pointer, obj);
        obj->pointer = _end;
        _end = obj;
    } else {
        _begin = obj;
        _end = _begin;
    }
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::push_front(const T& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = val;
    obj->pointer = nullptr;
    if (_begin != nullptr) {
        _begin->pointer = Xor(_begin->pointer, obj);
        obj->pointer = _begin;
        _begin = obj;
    } else {
        _begin = obj;
        _end = _begin;
    }
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::push_front(T&& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = std::move(val);
    obj->pointer = nullptr;
    if (_begin != nullptr) {
        _begin->pointer = Xor(_begin->pointer, obj);
        obj->pointer = _begin;
        _begin = obj;
    } else {
        _begin = obj;
        _end = _begin;
    }
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::insert_before(iterator& it, T&& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = std::move(val);
    obj->pointer = Xor(it._first, it._second);
    it._second->pointer = Xor(Xor(it._second->pointer, obj), it._first);
    it._first->pointer = Xor(Xor(it._first->pointer, obj), it._second);
    it._first = obj;
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::insert_after(iterator& it, T&& val) {
    ++it;
    insert_before(it, std::forward<T>(val));
    --it;
}

template<class T, class allocator>
void XorList<T, allocator>::insert_before(iterator& it, const T& val) {
    Node<T>* obj = _alloc.allocate(1);
    obj->value = val;
    obj->pointer = Xor(it._first, it._second);
    it._second->pointer = Xor(Xor(it._second->pointer, obj), it._first);
    it._first->pointer = Xor(Xor(it._first->pointer, obj), it._second);
    it._first = obj;
    ++_size;
}

template<class T, class allocator>
void XorList<T, allocator>::insert_after(iterator& it, const T& val) {
    ++it;
    insert_before(it, val);
    --it;
}

template<class T, class allocator>
XorListIterator<T, allocator> XorList<T, allocator>::begin() const{
    XorListIterator<T, allocator> tmp;
    tmp._first = nullptr;
    tmp._second = _begin;
    return tmp;
}

template<class T, class allocator>
XorListIterator<T, allocator> XorList<T, allocator>::end() const{
    XorListIterator<T, allocator> tmp;
    tmp._first = _end;
    tmp._second = nullptr;
    return tmp;
}

template<class T, class allocator>
size_t XorList<T, allocator>::size() const {
    return _size;
}

template<class T, class allocator>
void XorList<T, allocator>::clear() {
    Node<T>* p1 = nullptr;
    Node<T>* p2 = _begin;
    while (p2 != nullptr) {
        Node<T>* tmp = next(p1, p2);
        p1 = p2;
        _alloc.deallocate(p1, 1);
        p2 = tmp;
    }
}

template<class T, class allocator>
void XorList<T, allocator>::erase(iterator it) {
    Node<T>* nextNode = next(it._first, it._second);
    if (nextNode != nullptr) {
        nextNode->pointer = Xor(Xor(nextNode->pointer, it._second), it._first);
    } else {
        _end = it._first;
    }
    
    if (it._first != nullptr) {
        it._first->pointer = Xor(Xor(it._first->pointer, it._second), nextNode);
    } else {
        _begin = nextNode;
    }
    
    _alloc.destroy(it._second);
    _alloc.deallocate(it._second, 1);
    --_size;
}

template<class T, class allocator>
void XorList<T, allocator>::pop_front() {
    erase(begin());
}

template<class T, class allocator>
void XorList<T, allocator>::pop_back() {
    auto it = end();
    --it;
    erase(it);
}

template <class T, class allocator>
bool XorListIterator<T, allocator>::operator==(const XorListIterator<T, allocator>& other) const {
    return _first == other._first && _second == other._second;
}

template <class T, class allocator>
bool XorListIterator<T, allocator>::operator!=(const XorListIterator<T, allocator>& other) const {
    return !(*this == other);
}

template <class T, class allocator>
XorListIterator<T, allocator>& XorListIterator<T, allocator>::operator++() {
    Node<T>* tmp = next(_first, _second);
    _first = _second;
    _second = tmp;
    return *this;
}

template <class T, class allocator>
XorListIterator<T, allocator> XorListIterator<T, allocator>::operator++(int) {
    auto tmp = *this;
    operator++();
    return tmp;
}

template <class T, class allocator>
XorListIterator<T, allocator>& XorListIterator<T, allocator>::operator--() {
    Node<T>* tmp = prev(_first, _second);
    _second = _first;
    _first = tmp;
    return *this;
}

template <class T, class allocator>
XorListIterator<T, allocator> XorListIterator<T, allocator>::operator--(int) {
    auto tmp = *this;
    operator--();
    return tmp;
}

template <class T, class allocator>
T& XorListIterator<T, allocator>::operator*() {
    return _second->value;
}

template <class T, class allocator>
T* XorListIterator<T, allocator>::operator->() {
    return &(_second->value);
}
