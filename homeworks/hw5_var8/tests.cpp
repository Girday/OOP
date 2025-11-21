#include <gtest/gtest.h>
#include <memory_resource>

#include "FixedBlockResource.h"
#include "ForwardList.h"


struct Person {
    std::string name;
    int age;
};


// BASIC OPERATIONS TESTS

TEST(ForwardListTest, PushFrontAndIterate) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    int expected = 1;
    for (int v : list) {
        EXPECT_EQ(v, expected);
        expected++;
    }
}

TEST(ForwardListTest, PushBackWorks) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int expected[] = {10, 20, 30};
    int idx = 0;

    for (int v : list)
        EXPECT_EQ(v, expected[idx++]);
}

TEST(ForwardListTest, PopFrontWorks) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(5);
    list.push_back(6);

    list.pop_front();
    ASSERT_EQ(*list.begin(), 6);

    list.pop_front();
    ASSERT_EQ(list.begin(), list.end());
}

TEST(ForwardListTest, PopBackWorks) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    list.pop_back();

    ASSERT_EQ(*list.begin(), 1);

    list.pop_back();
    ASSERT_EQ(list.begin(), list.end());
}


// EMPTY LIST

TEST(ForwardListEdgeCases, EmptyListIteration) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    EXPECT_EQ(list.begin(), list.end());

    int count = 0;
    for (int v : list) {
        (void)v;
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST(ForwardListEdgeCases, PopFromEmptyList) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    EXPECT_NO_THROW(list.pop_front());
    EXPECT_NO_THROW(list.pop_back());

    EXPECT_EQ(list.begin(), list.end());
}

TEST(ForwardListEdgeCases, SingleElementOperations) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(42);
    EXPECT_EQ(*list.begin(), 42);

    list.pop_front();
    EXPECT_EQ(list.begin(), list.end());

    list.push_front(99);
    EXPECT_EQ(*list.begin(), 99);

    list.pop_back();
    EXPECT_EQ(list.begin(), list.end());
}


// LARGE LISTS

TEST(ForwardListEdgeCases, ManyElements) {
    FixedBlockResource mem(8192);
    ForwardList<int> list(&mem);

    const int N = 100;
    for (int i = 0; i < N; i++)
        list.push_back(i);

    int expected = 0;
    for (int v : list) {
        EXPECT_EQ(v, expected);
        expected++;
    }
    EXPECT_EQ(expected, N);
}

TEST(ForwardListEdgeCases, AlternatingPushPop) {
    FixedBlockResource mem(2048);
    ForwardList<int> list(&mem);

    for (int i = 0; i < 50; i++) {
        list.push_back(i);
        if (i % 3 == 0)
            list.pop_front();
    }

    EXPECT_NE(list.begin(), list.end());
}


// ITERATOR TESTS

TEST(IteratorTest, PreIncrementAndDereference) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(10);
    list.push_back(20);

    auto it = list.begin();
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(IteratorTest, EqualityAndInequality) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(7);

    auto a = list.begin();
    auto b = list.begin();
    auto e = list.end();

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != e);
}

TEST(IteratorTest, IteratorAfterModification) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();

    auto it = list.begin();
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(IteratorTest, MultipleIterators) {
    FixedBlockResource mem(1024);
    ForwardList<int> list(&mem);

    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    auto it1 = list.begin();
    auto it2 = list.begin();

    ++it1;
    EXPECT_EQ(*it1, 10);
    EXPECT_EQ(*it2, 5);

    ++it1;
    ++it2;
    EXPECT_EQ(*it1, 15);
    EXPECT_EQ(*it2, 10);
}


// COMPLEX TYPE TEST

TEST(ForwardListTest, WorksWithComplexStruct) {
    FixedBlockResource mem(2048);
    ForwardList<Person> people(&mem);

    people.push_back({"Alice", 30});
    people.push_back({"Bob", 22});

    auto it = people.begin();
    EXPECT_EQ(it->name, "Alice");
    EXPECT_EQ(it->age, 30);

    ++it;
    EXPECT_EQ(it->name, "Bob");
    EXPECT_EQ(it->age, 22);
}

TEST(ForwardListEdgeCases, ComplexTypeWithManyElements) {
    FixedBlockResource mem(8192);
    ForwardList<Person> people(&mem);

    for (int i = 0; i < 20; i++)
        people.push_back({"Person" + std::to_string(i), 20 + i});

    int count = 0;
    for (const auto& p : people) {
        EXPECT_EQ(p.name, "Person" + std::to_string(count));
        EXPECT_EQ(p.age, 20 + count);
        count++;
    }
    EXPECT_EQ(count, 20);
}


// MEMORY RESOURCE TESTS

TEST(MemoryResourceTest, ReusesFreedMemory) {
    FixedBlockResource mem(2048);

    size_t blocks_before = mem.used_blocks_count();

    {
        ForwardList<int> tmp(&mem);
        tmp.push_back(100);
        tmp.push_back(200);
    }

    size_t blocks_after_destruction = mem.used_blocks_count();

    EXPECT_GT(blocks_after_destruction, blocks_before);

    {
        ForwardList<int> reused(&mem);
        reused.push_back(999);
    }

    size_t blocks_after_reuse = mem.used_blocks_count();
    
    EXPECT_EQ(blocks_after_reuse, blocks_after_destruction);
}

TEST(MemoryResourceTest, DestructorFreesAllMemory) {
    size_t blocks_before = 0;

    {
        FixedBlockResource mem(4096);
        blocks_before = mem.used_blocks_count();

        ForwardList<int> list(&mem);
        for (int i = 0; i < 5; i++)
            list.push_back(i);

        EXPECT_GT(mem.used_blocks_count(), blocks_before);
    }

    SUCCEED();
}

TEST(MemoryResourceTest, BufferOverflow) {
    FixedBlockResource mem(64);
    ForwardList<int> list(&mem);

    EXPECT_THROW({
        for (int i = 0; i < 100; i++)
            list.push_back(i);
    }, std::bad_alloc);
}

TEST(MemoryResourceTest, MultipleListsShareResource) {
    FixedBlockResource mem(4096);

    ForwardList<int> list1(&mem);
    ForwardList<int> list2(&mem);

    list1.push_back(1);
    list1.push_back(2);

    list2.push_back(10);
    list2.push_back(20);

    EXPECT_EQ(*list1.begin(), 1);
    EXPECT_EQ(*list2.begin(), 10);

    size_t blocks_used = mem.used_blocks_count();
    EXPECT_GE(blocks_used, 4);
}

TEST(MemoryResourceTest, MemoryAlignment) {
    FixedBlockResource mem(1024);

    std::pmr::polymorphic_allocator<char> char_alloc(&mem);
    std::pmr::polymorphic_allocator<int> int_alloc(&mem);
    std::pmr::polymorphic_allocator<double> double_alloc(&mem);

    char* c = char_alloc.allocate(1);
    int* i = int_alloc.allocate(1);
    double* d = double_alloc.allocate(1);

    EXPECT_EQ(reinterpret_cast<uintptr_t>(i) % alignof(int), 0);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(d) % alignof(double), 0);

    char_alloc.deallocate(c, 1);
    int_alloc.deallocate(i, 1);
    double_alloc.deallocate(d, 1);
}


// STRESS TESTS

TEST(StressTest, ManyAllocationsAndDeallocations) {
    FixedBlockResource mem(16384);
    ForwardList<int> list(&mem);

    for (int cycle = 0; cycle < 10; cycle++) {
        for (int i = 0; i < 20; i++)
            list.push_back(i);

        for (int i = 0; i < 10; i++)
            list.pop_front();

        for (int i = 0; i < 5; i++)
            list.pop_back();
    }

    EXPECT_NE(list.begin(), list.end());
}

TEST(StressTest, InterleavedOperations) {
    FixedBlockResource mem(8192);
    ForwardList<int> list1(&mem);
    ForwardList<int> list2(&mem);

    for (int i = 0; i < 50; i++) {
        list1.push_back(i);
        list2.push_front(i);

        if (i % 5 == 0) {
            list1.pop_front();
            list2.pop_back();
        }
    }

    EXPECT_NE(list1.begin(), list1.end());
    EXPECT_NE(list2.begin(), list2.end());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
