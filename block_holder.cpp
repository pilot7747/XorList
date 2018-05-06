//
//  block_holder.cpp
//  XorList
//
//  Created by Никита on 17.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#include "block_holder.h"

void blockHolder::add(void* p) {
    if (_start == nullptr) {
        _start = new block();
        _start->memory_block = p;
        _start->next = nullptr;
        _current = _start;
    } else {
        block* blck = new block();
        blck->memory_block = p;
        blck->next = nullptr;
        _current->next = blck;
        _current = blck;
    }
}

void blockHolder::delList(block* p) {
    if (p != nullptr) {
        if (p->next != nullptr) {
            delList(p->next);
        }
        delete p;
    }
}

blockHolder::~blockHolder() {
    delList(_start);
}

void blockHolder::free_blocks(block* p) {
    if (p != nullptr) {
        if (p->next != nullptr) {
            free_blocks(p->next);
        }
        ::operator delete(p->memory_block);
    }
}

void blockHolder::destruct() {
    free_blocks(_start);
}
