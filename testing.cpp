//
//  testing.cpp
//  XorList
//
//  Created by Никита on 06.05.2018.
//  Copyright © 2018 Nikita Pavlichenko. All rights reserved.
//

#pragma once
#include "testing.hpp"
#include "XorList.cpp"
#include "allocator.cpp"
#include "Stopwatch.h"
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include <list>
enum class operation {
    push_back, push_front, pop_back, pop_front, insert_before, insert_after, size
};

struct times {
    double list = 0, xorList = 0;
};

void checkLists(const XorList<int, StackAllocator<int>>& xlist, const std::list<int>& list) {
    std::vector<int> first, second;
    ASSERT_EQ(xlist.size(), list.size());
    for (auto it = xlist.begin(); it != xlist.end(); it++) {
        first.push_back(*it);
    }
    for (auto it = list.begin(); it != list.end(); it++) {
        second.push_back(*it);
    }
    ASSERT_EQ(first.size(), second.size());
    for (int i = 0; i < first.size(); ++i) {
        ASSERT_EQ(first[i], second[i]);
    }
}

void doOps(const std::vector<std::pair<operation, int>> ops, XorList<int, StackAllocator<int>>& xlist, std::list<int>& list) {
    Stopwatch stopwatch;
    stopwatch.start();
    times t;
    std::vector<int> results;
    for (const auto& op : ops) {
        switch (op.first) {
            case operation::push_back:
                xlist.push_back(op.second);
                list.push_back(op.second);
                break;
            case operation::push_front:
                xlist.push_front(op.second);
                list.push_front(op.second);
                break;
            case operation::pop_back:
                xlist.pop_back();
                list.pop_back();
                break;
            case operation::pop_front:
                xlist.pop_front();
                list.pop_front();
                break;
            default:
                break;
        }
        checkLists(xlist, list);
    }
}

class simpleTests : public ::testing::Test {
protected:
    void SetUp() {
        xlist.clear();
        list.clear();
    }
    void TearDown() {
        xlist.clear();
        list.clear();
    }
    XorList<int, StackAllocator<int>> xlist;
    std::list<int> list;
};

TEST_F(simpleTests, simplePushing1) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_back, 1));
    ops.push_back(make_pair(operation::push_back, 2));
    ops.push_back(make_pair(operation::push_back, 3));
    ops.push_back(make_pair(operation::push_back, 4));
    ops.push_back(make_pair(operation::push_back, 5));
    doOps(ops, xlist, list);
}

TEST_F(simpleTests, simplePushing2) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_front, 1));
    ops.push_back(make_pair(operation::push_front, 2));
    ops.push_back(make_pair(operation::push_front, 3));
    ops.push_back(make_pair(operation::push_front, 4));
    ops.push_back(make_pair(operation::push_front, 5));
    doOps(ops, xlist, list);
}

TEST_F(simpleTests, simplePushing3) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_front, 1));
    ops.push_back(make_pair(operation::push_back, 2));
    ops.push_back(make_pair(operation::push_front, 3));
    ops.push_back(make_pair(operation::push_back, 4));
    ops.push_back(make_pair(operation::push_front, 5));
    doOps(ops, xlist, list);
}

TEST_F(simpleTests, simplePoping1) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_back, 1));
    ops.push_back(make_pair(operation::push_back, 2));
    ops.push_back(make_pair(operation::push_back, 3));
    ops.push_back(make_pair(operation::push_back, 4));
    ops.push_back(make_pair(operation::push_back, 5));
    
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    doOps(ops, xlist, list);
}

TEST_F(simpleTests, simplePoping2) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_back, 1));
    ops.push_back(make_pair(operation::push_back, 2));
    ops.push_back(make_pair(operation::push_back, 3));
    ops.push_back(make_pair(operation::push_back, 4));
    ops.push_back(make_pair(operation::push_back, 5));
    
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    doOps(ops, xlist, list);
}

TEST_F(simpleTests, simplePoping3) {
    using std::make_pair;
    std::vector<std::pair<operation, int>> ops;
    ops.push_back(make_pair(operation::push_back, 1));
    ops.push_back(make_pair(operation::push_back, 2));
    ops.push_back(make_pair(operation::push_back, 3));
    ops.push_back(make_pair(operation::push_back, 4));
    ops.push_back(make_pair(operation::push_back, 5));
    
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    ops.push_back(make_pair(operation::pop_back, 0));
    ops.push_back(make_pair(operation::pop_front, 0));
    doOps(ops, xlist, list);
}
