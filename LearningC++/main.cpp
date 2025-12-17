#include <iostream>
#include "LinkList.h"
#include "LinkListNoTemp.h"
using namespace std;

void testAddStack() {
    std::cout << "\n### Test 1: Stack Behavior (FIFO) ###" << std::endl;
    LinkList<int> myStack;

    // PUSH
    myStack.add(myStack.end(), 10);
    myStack.add(myStack.end(), 20);
    myStack.add(myStack.end(), 30);
    std::cout << "Added 10 -> 20 -> 30" << endl;

    // POP
    std::cout << "Stack Pop: " << myStack.remove(myStack.back()) << std::endl;
    std::cout << "Stack Pop: " << myStack.remove(myStack.back()) << std::endl;
}   
void testAddQueue() {
    std::cout << "\n### Test 2: Queue Behavior (FIFO) ###" << std::endl;
    LinkList<int> myQueue;
    myQueue.add(myQueue.end(), 100);
    myQueue.add(myQueue.end(), 200);
    myQueue.add(myQueue.end(), 300);
    try {
        std::cout << "Queue Dequeue: " << myQueue.remove(myQueue.begin()) << std::endl;
        std::cout << "Queue Dequeue: " << myQueue.remove(myQueue.begin()) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error during Dequeue: " << e.what() << std::endl;
    }
}

void testAddStackNoTemp() {
    std::cout << "\n### Test 3: Stack Behavior ### NO TEMP" << std::endl;
    LinkListNoTemp myStack;
    std::cout << "Added 10 -> 20 -> 30" << endl;
    // PUSH
    myStack.add(myStack.end(), 10);
    myStack.add(myStack.end(), 20);
    myStack.add(myStack.end(), 30);

    // POP
    std::cout << "Stack Pop: " << myStack.remove(myStack.back()) << std::endl;
    std::cout << "Stack Pop: " << myStack.remove(myStack.back()) << std::endl;
}
void testAddQueueNoTemp() {
    std::cout << "\n### Test 4: Queue Behavior (FIFO) NO TEMP###" << std::endl;
    LinkListNoTemp myQueue;
    myQueue.add(myQueue.end(), 100);
    myQueue.add(myQueue.end(), 200);
    myQueue.add(myQueue.end(), 300);
    try {
        std::cout << "Queue Dequeue: " << myQueue.remove(myQueue.begin()) << std::endl;
        std::cout << "Queue Dequeue: " << myQueue.remove(myQueue.begin()) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error during Dequeue: " << e.what() << std::endl;
    }
}
void populateList(LinkList<int>& list, int size) {
    for (int i = 0; i < size; i++) {
        list.add(list.end(), i);
    }
}

void printHeader(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void testIntegerList() {
    printHeader("Testing <int> Template");

    LinkList<int> numbers;

    // 1. Test ADD
    std::cout << "Adding 10, 20, 30..." << std::endl;
    numbers.add(numbers.end(), 10);
    numbers.add(numbers.end(), 20);
    numbers.add(numbers.end(), 30);
    numbers.print_list();

    // 2. Test REMOVE (Back/Stack style)
    // We expect 30 to be removed first
    int removedVal = numbers.remove(numbers.back());
    std::cout << "Removed: " << removedVal << " (Expected: 30)" << std::endl;

    removedVal = numbers.remove(numbers.back());
    std::cout << "Removed: " << removedVal << " (Expected: 20)" << std::endl;

    numbers.print_list();
}

void testStringList() {
    printHeader("Testing <std::string> Template");

    LinkList<std::string> words;

    std::cout << "Adding 'Hello', 'World', 'C++'..." << std::endl;
    words.add(words.end(), "Hello");
    words.add(words.end(), "World");
    words.add(words.end(), "C++");
    words.print_list();
    std::string removedWord = words.remove(words.back());
    std::cout << "Removed: " << removedWord << " (Expected: C++)" << std::endl;

    words.print_list();
}

void testEmptyRemove() {
    printHeader("Testing Exceptions (Remove from Empty)");
    LinkList<int> list;

    try {
        list.remove(list.back());
    }
    catch (const std::exception& e) {
        std::cout << "SUCCESS: Caught expected error: " << e.what() << std::endl;
    }
}


void testDefaultConstructor() {
    std::cout << "\n### Test 1: Default Constructor ###" << std::endl;
    {
        LinkList<int> list1;
        if (list1.getSize() == 0) {
            std::cout << "PASS: Default constructor initialized list to empty state." << std::endl;
        }
        else {
            std::cout << "FAIL: Default constructor size is incorrect." << std::endl;
        }
    }
    std::cout << "RESULT: List 1 safely destroyed." << std::endl;
}

void testCopyConstructor() {
    LinkList<int> list;
    populateList(list, 3);
    LinkList list2 = list;
    if (list2.getSize() == 3) {
        std::cout << "Passed: Inital deep copy was sucessful" << std::endl;
    }
    list.remove(list.back());
    if (list2.getSize() == 3) {
        std::cout << "Passed: Copy was deep as modification to the original list did not change deep copied list" << std::endl;
    }
}

void testMoveConstructor() {
    LinkList<int> list;
    populateList(list, 4);
    LinkList list2 = std::move(list);
    if (list2.getSize() == 4) {
        std::cout << "Passed: Inital move was sucessful" << std::endl;
    }
    if (list.getSize() == 0) {
        std::cout << "Passed: original list was destroyed in the move";
    }
}

void test_print_list() {
    std::cout << "\n========== TEST: LinkList::print_list() ==========" << std::endl;

    // --- Test 1: Empty List ---
    LinkList<int> emptyList;
    std::cout << std::endl << "\n--- Test 1: Empty List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 0): END" << std::endl;
    std::cout << "Actual Output:   ";
    emptyList.print_list();
    LinkList<int> fullList;
    populateList(fullList, 3); 
    std::cout << std::endl << "\n--- Test 2: Multi-Element List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 3): [10] -> [20] -> [30] -> END" << std::endl;
    std::cout << "Actual Output:   ";
    fullList.print_list();
    LinkList<int> singleList;
    singleList.add(singleList.begin(), 99);
    std::cout << std::endl << "\n--- Test 3: Single Element List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 1): [99] -> END" << std::endl;
    std::cout << "Actual Output:   ";
    singleList.print_list();
    std::cout << std::endl << "==================================================" << std::endl;
}
int main() {
    int x = 10;
    if (x == 10) {
        std::cout << "Hello World" << endl;
    }
    LinkList<int> list1;
    LinkList<int>* list2 = new LinkList<int>();
    list1.add(list1.back(), 20);
    list1.add(list1.back(), 30);
    list1.add(list1.back(), 40);
    LinkList list3 = list1;
    testAddStack();
    testAddQueue();
    testAddStackNoTemp();
    testAddQueueNoTemp();
    testDefaultConstructor();
    testCopyConstructor();
    testMoveConstructor();
    test_print_list();
    testEmptyRemove();
    testIntegerList();
    testStringList();
}