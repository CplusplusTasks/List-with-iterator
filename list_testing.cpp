#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <list>
#include <gtest/gtest.h>

#include "list_.h"

TEST(correctness, splice)
{
    std::list<int> a, b;
    list a2, b2;
    for (int i = -1; i > -50000; i--) {
        int k = rand();
        int l = rand();

        b.push_back(k);
        b2.push_back(k);

        a2.push_back(l);
        a.push_back(l);
    }

    a.splice(a.begin(), b, b.begin(), b.end());
    a2.splice(a2.begin(), b2, b2.begin(), b2.end());

    std::list<int>::iterator it = a.begin();
    list::iterator it2 = a2.begin();

    while (it != a.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }

    it = b.begin();
    it2 = b2.begin();
    while (it != b.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }
    
    b.splice(b.begin(), a, ++++a.begin(), --a.end());
    b2.splice(b2.begin(), a2, ++++a2.begin(), --a2.end());

    it = a.begin();
    it2 = a2.begin();

    while (it != a.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }

    it = b.begin();
    it2 = b2.begin();
    while (it != b.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }

    EXPECT_EQ(a.empty(), a2.empty());
}

TEST(correctness, insert_erase) {
    std::list<int> a;
    list b;

    a.push_back(1);
    a.insert(a.begin(), 9);
    a.insert(a.end(), 0);

    b.push_back(1);
    b.insert(b.begin(), 9);
    b.insert(b.end(), 0);
    for (int i = 0, j = 10000; i < 10000; i++, j--) {
        int k = rand();
        int l = rand();
        a.insert(++a.begin(), k);
        a.insert(--a.end(), l);
        a.insert(a.begin(), k);

        b.insert(++b.begin(), k);
        b.insert(--b.end(), l);
        b.insert(b.begin(), k);
    }

    for (int j = 100; j < 200; j++) {
        a.erase(++++++++a.begin());
        b.erase(++++++++b.begin());

        a.erase(----a.end());
        b.erase(----b.end());
    }

    std::list<int>::iterator it = a.begin();
    list::iterator it2 = b.begin();

    while (it != a.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }
    EXPECT_EQ(a.empty(), b.empty());
}

TEST(correctness, push) {
    std::list<int> a;
    list b;
    for (int i = 0, j = 10000; i < 10000; i++, j--) {
        a.push_back(i);
        a.push_front(j);

        b.push_back(i);
        b.push_front(j);
    }

    std::list<int>::iterator it = a.begin();
    list::iterator it2 = b.begin();

    while (it != a.end()) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }
    EXPECT_EQ(a.empty(), b.empty());
}
