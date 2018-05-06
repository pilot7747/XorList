//
//  XorList.h
//  XorList
//
//  Created by Никита on 24.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#ifndef XorList_h
#define XorList_h

//#include "allocator.cpp"

template<class T, class allocator>
class XorListIterator;

//Node of list
template<class T>
struct Node {
    T value;
    Node<T>* pointer = nullptr;
    template <typename U>
    explicit Node(U&& val): value(std::forward<U>(val)){}
};


template<class T, class allocator = std::allocator<T>>
class XorList {
public:
    //iterator's typedef
    typedef XorListIterator<T, allocator> iterator;
    
    explicit XorList(const allocator& alloc = allocator());
    XorList(size_t count, const T& value = T(), const allocator& alloc = allocator());
    XorList(const XorList<T, allocator>&);
    XorList(XorList<T, allocator>&&) noexcept;
    ~XorList();
    
    size_t size() const;
    void clear();
    
    //lvalue-reference methods
    void push_back(const T& val);
    void push_front(const T& val);
    void insert_before(iterator&, const T& val);
    void insert_after(iterator&, const T& val);
    void erase(iterator it);
    
    //rvalue-reference methods
    void push_back(T&& val);
    void push_front(T&& val);
    void insert_before(iterator&, T&& val);
    void insert_after(iterator&, T&& val);
    
    //pops
    void pop_back();
    void pop_front();
    
    //iterators
    iterator begin() const;
    iterator end() const;
private:
    Node<T>* _begin;
    Node<T>* _end;
    size_t _size;
    typename allocator::template rebind<Node<T>>::other _alloc;
};

template <typename T, class allocator>
class XorListIterator : std::iterator<std::bidirectional_iterator_tag, T> {
public:
    friend class XorList<T, allocator>;
    
    typedef T ValueType;
    
    XorListIterator<T, allocator>& operator++();
    XorListIterator<T, allocator> operator++(int);
    XorListIterator<T, allocator>& operator--();
    XorListIterator<T, allocator> operator--(int);
    ValueType& operator*();
    ValueType* operator->();
    
    bool operator==(const XorListIterator<T, allocator>&) const;
    bool operator!=(const XorListIterator<T, allocator>&) const;
    
private:
    Node<T>* _first = nullptr;
    Node<T>* _second = nullptr;
};
#endif /* XorList_h */
