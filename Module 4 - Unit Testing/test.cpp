// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer 
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}
*/

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 5 entries
    add_entries(5);

    // verify collection size is 5
    ASSERT_EQ(collection->size(), 5);

}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanSize)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // verify max size is greater than or equal to size 0
    ASSERT_GE(collection->max_size(), collection->size());

    // add 1 entry
    add_entries(1);

    // verify max size is greater than or equal to size 1
    ASSERT_GE(collection->max_size(), collection->size());

    //clear collection 
    collection->clear();

    // add 5 entries
    add_entries(5);

    // verify max size is greater than or equal to size 5
    ASSERT_GE(collection->max_size(), collection->size());

    //clear collection
    collection->clear();

    //add 10 entries
    add_entries(10);

    // verify max size is greater than or equal to size 10
    ASSERT_GE(collection->max_size(), collection->size());

}

// Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanSize)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // verify capacity is greater than or equal to size 0
    ASSERT_GE(collection->capacity(), collection->size());

    // add 1 entry
    add_entries(1);

    // verify capacity is greater than or equal to size 1
    ASSERT_GE(collection->capacity(), collection->size());

    //clear collection 
    collection->clear();

    // add 5 entries
    add_entries(5);

    // verify capacity is greater than or equal to size 5
    ASSERT_GE(collection->capacity(), collection->size());

    //clear collection
    collection->clear();

    //add 10 entries
    add_entries(10);

    // verify capacity is greater than or equal to size 10
    ASSERT_GE(collection->capacity(), collection->size());
}

// Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesSize)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    //resize collection
    collection->resize(10);

    // verify collection is still empty
    ASSERT_FALSE(collection->empty());

    // if not empty, verify resize increased size
    ASSERT_EQ(collection->size(), 10);

}

// Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesSize)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 20 entries
    add_entries(20);

    // verify collection size is 20
    ASSERT_EQ(collection->size(), 20);

    // resize collection to 10 entries
    collection->resize(10);

    // verify collection size is now 10
    ASSERT_EQ(collection->size(), 10);
}

// Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesToZero)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 10 entries
    add_entries(10);

    // verify collection size is 10
    ASSERT_EQ(collection->size(), 10);

    // resize collection to 0 entries
    collection->resize(0);

    // verify collection size is now 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 10 entries
    add_entries(10);

    // verify collection size is 10
    ASSERT_EQ(collection->size(), 10);

    // clear collection
    collection->clear();

    // verify collection size is now 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseErasesCollection)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 10 entries
    add_entries(10);

    // verify collection size is 10
    ASSERT_EQ(collection->size(), 10);

    // erase collection from beginning to end
    collection->erase(collection->begin(), collection->end());

    // verify collection size is now 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // reserve 10 entries
    collection->reserve(10);

    // verify capacity is 10 now
    ASSERT_EQ(collection->capacity(), 10);

    // verify size is still 0
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // verify exception thrown with out of bound index call
    ASSERT_THROW(collection->at(1), std::out_of_range);

}

/* Create 2 of my own tests */

// Create test to verify assigning value at index changes value at given index
TEST_F(CollectionTest, AssignChangesValueAtIndex)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    // add 10 entries
    add_entries(10);

    // assign 20 at index 1
    collection->assign(collection->at(1), 20);

    // verify value at index 1 is 20
    ASSERT_EQ(collection->at(1), 20);

    // assign 15 at index 1
    collection->assign(collection->at(1), 15);

    // verify value at index 1 is now 15
    ASSERT_EQ(collection->at(1), 15);

}

// Create test to verify that std::length_error exception is thrown when max size exceeded
TEST_F(CollectionTest, LengthErrorExceptionThrown)
{
    // verify collection is empty
    ASSERT_TRUE(collection->empty());

    // if collection empty, size is 0
    ASSERT_EQ(collection->size(), 0);

    //verify exception thrown when max size exceeded
    ASSERT_THROW(collection->resize(collection->max_size() + 1), std::length_error);
}
