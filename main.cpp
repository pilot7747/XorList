//
//  main.cpp
//  XorList
//
//  Created by Никита on 16.04.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "allocator.cpp"
#include "Stopwatch.h"
#include <string>
#include "XorList.cpp"
#include "testing.cpp"
#include <gtest/gtest.h>

enum class OpType {push_b, push_f, pop_b, pop_f};


std::vector<operation> ops;




int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    /*XorList<int, StackAllocator<int>> xlist;
    xlist.push_back(1);
    xlist.push_back(2);
    xlist.push_back(3);
    xlist.push_back(4);
    xlist.push_back(5);
    auto it = xlist.begin();
    it++;
    xlist.insert_after(it, 0);
    for (auto i = xlist.begin(); i != xlist.end(); i++) {
        std::cout << *i << std::endl;
    }*/
    
    
    /*srand(0);
    int sz = 0;
    for (int i = 0; i < 10; ++i) {
        operation op;
        int tmpOp = rand() %  6;
        if (tmpOp == 0)/usr/local/Cellar/glfw/3.2.1/lib/libglfw.dylib
            op.type = OpType::pop_b;
        else if (tmpOp == 1)
            op.type = OpType::pop_f;
        else if (tmpOp >= 4)
            op.type = OpType::push_f;
        else
            op.type = OpType::push_b;
        if (!((op.type == OpType::pop_f || op.type == OpType::pop_b) && sz == 0)) {
            ops.push_back(op);
        }
        if (op.type == OpType::pop_f || op.type == OpType::pop_b) {
            ++sz;
        } else {
            --sz;
        }
    }
    std::list<int> lst;
    std::list<int, StackAllocator<int>> myList;
    Stopwatch sw;
    sw.start();
    for (auto& op : ops) {
        if (op.type == OpType::pop_f) {
            lst.pop_front();
        }
        if (op.type == OpType::pop_b) {
            lst.pop_back();
        }
        if (op.type == OpType::push_b) {
            lst.push_back(1);
        }
        if (op.type == OpType::push_f) {
            lst.push_front(1);
        }
    }
    std::cout << sw.circle() << std::endl;
    for (auto& op : ops) {
        if (op.type == OpType::pop_f) {
            myList.pop_front();
        }
        if (op.type == OpType::pop_b) {
            myList.pop_back();
        }
        if (op.type == OpType::push_b) {
            myList.push_back(1);
        }
        if (op.type == OpType::push_f) {
            myList.push_front(1);
        }
    }
    std::cout << sw.circle() << std::endl;
    
    for (auto& a : lst) {
        std::cout << a << ' ';
    }
    for (auto& a : myList) {
        std::cout << a << ' ';
    }
    std::string s = "ಊಊಊಊಊಊಊಊಊ";
    std::cout << (int)(s[0]);
    std::cout << s;*/
}
