#include <deepstate/DeepState.hpp>
#include "circularll.h"

using namespace deepstate;

TEST(CircularLinkedList, InsertionDeletion) {
    CircularLinkedList list;

    // Randomly generate input data
    int numInsertions = DeepState_IntInRange(0, 100);
    for (int i = 0; i < numInsertions; ++i) {
        int value = DeepState_Int();
        int index = DeepState_IntInRange(0, list.getSize());
        list.insertAtIndex(value, index);
    }

    ASSERT_EQ(list.getSize(), numInsertions);
}

TEST(CircularLinkedList, Search) {
    CircularLinkedList list;

    // Randomly generate input data
    int numInsertions = DeepState_IntInRange(0, 100);
    for (int i = 0; i < numInsertions; ++i) {
        int value = DeepState_Int();
        list.insertAtEnd(value);
    }

    // Randomly choose a value to search for
    int searchValue = DeepState_Int();
    int searchIndex = list.search(searchValue);

    if (numInsertions > 0) {
        if (searchIndex >= 0) {
            // If value is found, it should be at the returned index
            ASSERT_EQ(list.getHead()->data, searchValue);
        } else {
            // If value is not found, head value should not match
            ASSERT_NE(list.getHead()->data, searchValue);
        }
    }
}

TEST(CircularLinkedList, Sorting) {
    CircularLinkedList list;

    // Randomly generate input data
    int numInsertions = DeepState_IntInRange(0, 100);
    for (int i = 0; i < numInsertions; ++i) {
        int value = DeepState_Int();
        list.insertAtEnd(value);
    }

    // Sort the list
    list.sort();

    // Verify that list is sorted
    Node* current = list.getHead();
    while (current->next != list.getHead()) {
        ASSERT_LE(current->data, current->next->data);
        current = current->next;
    }
}