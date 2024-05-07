#include <iostream>
#include "circularll.h"

CircularLinkedList::CircularLinkedList() {
    head = nullptr;
}

CircularLinkedList::~CircularLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
        if (current == head)
            break;
    }
    head = nullptr;
}

void CircularLinkedList::insertAtBeginning(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
}

void CircularLinkedList::insertAtEnd(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
}

void CircularLinkedList::insertAfterValue(int value, int afterValue) {
    Node* newNode = new Node;
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        return;
    }
    Node* temp = head;
    while (temp->next != head && temp->data != afterValue) {
        temp = temp->next;
    }
    if (temp->data != afterValue) {
        std::cout << "Value not found\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void CircularLinkedList::insertAtIndex(int value, int index) {
    if (index < 0) {
        std::cout << "Invalid index\n";
        return;
    }
    if (index == 0) {
        insertAtBeginning(value);
        return;
    }
    Node* newNode = new Node;
    newNode->data = value;
    Node* temp = head;
    for (int i = 0; i < index - 1; ++i) {
        temp = temp->next;
        if (temp == head) {
            std::cout << "Index out of bounds\n";
            delete newNode;
            return;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

bool CircularLinkedList::isEmpty() {
    return head == nullptr;
}

int CircularLinkedList::getSize() {
    if (isEmpty())
        return 0;
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    return count;
}

Node* CircularLinkedList::getHead() {
    return head;
}

int CircularLinkedList::search(int value) {
    int index = 0;
    Node* temp = head;
    do {
        if (temp->data == value)
            return index;
        index++;
        temp = temp->next;
    } while (temp != head);
    return -1; // Not found
}

void CircularLinkedList::reverse() {
    if (head == nullptr || head->next == head)
        return;
    Node* prev = nullptr;
    Node* current = head;
    Node* next;
    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != head);
    head->next = prev;
    head = prev;
}

void CircularLinkedList::display() {
    if (head == nullptr) {
        std::cout << "List is empty\n";
        return;
    }
    Node* temp = head;
    do {
        std::cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    std::cout << std::endl;
}

void CircularLinkedList::split(CircularLinkedList& list1, CircularLinkedList& list2) {
    if (isEmpty()) {
        std::cout << "Cannot split empty list\n";
        return;
    }
    if (head->next == head) {
        list1.insertAtEnd(head->data);
        return;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast->next->next == head)
        fast = fast->next;
    list1.head = head;
    list2.head = slow->next;
    fast->next = slow->next;
    slow->next = head;
}

Node* CircularLinkedList::mergeSorted(CircularLinkedList& list) {
    CircularLinkedList mergedList;
    Node* a = head;
    Node* b = list.head;
    while (a != nullptr && b != nullptr) {
        if (a->data <= b->data) {
            mergedList.insertAtEnd(a->data);
            a = a->next;
        } else {
            mergedList.insertAtEnd(b->data);
            b = b->next;
        }
        if (a == head || b == list.head)
            break;
    }
    // std::cout << "1" << std::endl;
    while (a != head) {
        mergedList.insertAtEnd(a->data);
        a = a->next;
    }
    // std::cout << "1" << std::endl;
    while (b != list.head) {
        mergedList.insertAtEnd(b->data);
        b = b->next;
    }
    // std::cout << "1" << std::endl;
    head = mergedList.head;
    return mergedList.head;
}

void CircularLinkedList::sort() {
    if (head == nullptr || head->next == head)
        return;
    Node* current = head;
    do {
        Node* index = current->next;
        while (index != head) {
            if (current->data > index->data) {
                int temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    } while (current->next != head);
}

int main() {
    CircularLinkedList list;

    // Insertion
    list.insertAtBeginning(5);
    list.insertAtBeginning(3);
    list.insertAtEnd(7);
    list.insertAfterValue(5, 3); // Insert 5 after 3
    list.insertAtIndex(4, 3); // Insert 4 at index 3
    std::cout << "Initial List: ";
    list.display(); // Should display: 3 5 4 5 7

    // Other operations
    std::cout << "Size of the list: " << list.getSize() << std::endl; // Should display: 1
    std::cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl; // Should display: No
    std::cout << "Search value 5 at index: " << list.search(5) << std::endl; // Should display: -1 (not found)
    std::cout << "Search value 7 at index: " << list.search(7) << std::endl; // Should display: 0

    // Splitting
    CircularLinkedList list1, list2;
    list.split(list1, list2);
    std::cout << "List 1: ";
    list1.display(); // Should display: 5
    std::cout << "List 2: ";
    list2.display(); // Should display: Empty list

    // Merge sorted
    CircularLinkedList sortedList1, sortedList2;
    sortedList1.insertAtBeginning(2);
    sortedList1.insertAtBeginning(4);
    sortedList2.insertAtBeginning(3);
    sortedList2.insertAtBeginning(5);
    Node* merged = sortedList1.mergeSorted(sortedList2);
    std::cout << "Merged sorted list: ";
    // sortedList1.display(); // Should display: 2 3 4 5
    while(merged != nullptr) 
    {
        std::cout << merged->data << " ";
        merged = merged->next;
    }
    std::cout << std::endl;


    // Sorting
    list1.insertAtBeginning(6);
    list1.insertAtBeginning(1);
    list1.sort();
    std::cout << "Sorted list: ";
    list1.display(); // Should display: 1 2 3 4 5 6

    return 0;
}
