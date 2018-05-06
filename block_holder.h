//
//  block_holder.h
//  XorList
//
//  Created by Никита on 17.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#ifndef block_holder_h
#define block_holder_h

struct block {
    void* memory_block;
    block* next;
};

class blockHolder {
public:
    void add(void* p);
    void destruct();
    blockHolder() : _start(nullptr), _current(nullptr) {};
    ~blockHolder();
private:
    block* _start;
    block* _current;
    void delList(block* p);
    void free_blocks(block* p);
};

#endif /* block_holder_h */
