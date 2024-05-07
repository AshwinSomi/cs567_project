#ifndef CIRCULAR_LL_H
#define CIRCULAR_LL_H

struct Node {
    int data;
    Node* next;
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList();
    ~CircularLinkedList();

    void insertAtBeginning(int value);
    void insertAtEnd(int value);
    void insertAtIndex(int value, int index);
    void insertAfterValue(int value, int afterValue);

    void deleteAtBeginning();
    void deleteAtEnd();
    void deleteAtIndex(int index);
    void deleteByValue(int value);

    bool isEmpty();
    int getSize();
    Node* getHead();
    int search(int value);
    void reverse();

    void display();

    void split(CircularLinkedList& list1, CircularLinkedList& list2);
    Node* mergeSorted(CircularLinkedList& list);
    void sort();
};

#endif
