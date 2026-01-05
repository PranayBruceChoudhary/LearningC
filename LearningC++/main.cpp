#include <iostream>
#include "LinkList.h"
#include "LinkListNoTemp.h"
#include "BinarySearchTree.h"
#include <vector>
#include "Map.h"
using namespace std;

void populateList(LinkList<int>& list, int size) {
    for (int i = 0; i < size; i++) {
        list.add(list.end(), i);
    }
}

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
    std::cout << std::endl << "Removed: " << removedWord << " (Expected: C++)" << std::endl;

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
    // TODO:Check values were copied as well
    LinkList<int> list;
    populateList(list, 4);
    LinkList list2 = list;
    if (list2.getSize() == 4) {
        std::cout << "Passed: Inital deep copy was sucessful" << std::endl;
    }
	int num1 = list.remove(list.back());
	int num2 = list.remove(list.back());
	int num3 = list.remove(list.back());
	if (num1 == 2 && num2  == 1 && num3  == 0) {
        std::cout << "Passed: Values were copied correctly" << std::endl;
    }
    if (list2.getSize() == 4) {
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
template <typename T>
void check(T value, T expected, const std::string& testName) {
    if (value == expected) {
        std::cout << "[PASS] " << testName << std::endl;
    }
    else {
        std::cout << "[FAIL] " << testName << " (Expected: " << expected << ", Got: " << value << ")" << std::endl;
    }
}

void check_bool(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << std::endl;
    }
    else {
        std::cout << "[FAIL] " << testName << std::endl;
    }
}

// ----------------------------------------------------------------------
// Test Cases
// ----------------------------------------------------------------------

void test_initialization_and_traversal() {
    std::cout << "\n--- Running test_initialization_and_traversal ---" << std::endl;
    LinkList<int> list;
    list.add(list.end(), 10);
    list.add(list.end(), 20);
    list.add(list.end(),30);
    auto it = list.rbegin();
    try {
        check(*it, 30, "rbegin() points to last element (30)");
    }
    catch (...) {
        check_bool(false, "rbegin() threw unexpected exception");
    }
    ++it;
    check(*it, 20, "Iterator moved to previous element (20)");
    ++it;
    check(*it, 10, "Iterator moved to head element (10)");
    ++it;
    bool isEnd = (it == list.rend());
    check_bool(isEnd, "Iterator reached rend() after traversing all elements");
}

void test_bidirectional_movement() {
    LinkList<int> list;
    list.add(list.end(), 100);
    list.add(list.end(), 200);

    auto it = list.rbegin(); 
    check(*it, 200, "Start at 200");

    ++it; 
    check(*it, 100, "Advanced to 100");

    --it;
    check(*it, 200, "Decremented iterator back to 200");
}

void test_equality_by_value() {
    std::cout << "\n--- Running test_equality_by_value ---" << std::endl;
    LinkList<int> list;
    list.add(list.end(), 5); 
    list.add(list.end(), 9);
    list.add(list.end(), 5); 

    auto itTail = list.rbegin();
    auto itHead = list.rback();
    check_bool(itTail == itHead, "Iterators with same data value are considered equal");

    ++itTail; // Points to 9
    check_bool(itTail != itHead, "Iterators with different data are not equal");
}

void test_out_of_range_exception() {
    std::cout << "\n--- Running test_out_of_range_exception ---" << std::endl;
    LinkList<int> list;
    list.add(list.end(), 1);

    auto it = list.rend();

    bool caught = false;
    try {
        int val = *it;// Should throw 
        (void)val;
    }
    catch (const std::out_of_range& e) {
        caught = true;
        std::cout << "   (Caught expected exception: " << e.what() << ")" << std::endl;
    }
    catch (...) {
        std::cout << "   (Caught wrong exception type)" << std::endl;
    }

    check_bool(caught, "Dereferencing rend() throws std::out_of_range");
}

void test_print_list() {
    std::cout << "\n========== TEST: LinkList::print_list() ==========" << std::endl;

    LinkList<int> emptyList;
    std::cout << std::endl << "\n--- Test 1: Empty List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 0): " << std::endl;
    std::cout << "Actual Output:   ";
    emptyList.print_list();
    LinkList<int> fullList;
    populateList(fullList, 3); 
    std::cout << std::endl << "\n--- Test 2: Multi-Element List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 3): [0] -> [1] -> [2] -> " << std::endl;
    std::cout << "Actual Output:   ";
    fullList.print_list();
    LinkList<int> singleList;
    singleList.add(singleList.begin(), 99);
    std::cout << std::endl << "\n--- Test 3: Single Element List ---" << std::endl;
    std::cout << "Expected Output: List Contents (Size: 1): [99] -> " << std::endl;
    std::cout << "Actual Output:   ";
    singleList.print_list();
    std::cout << std::endl << "==================================================" << std::endl;
}

void testIteratorIncrement() {
        std::cout << "\n### Test Iterator Lvalue and Rvalue ###" << std::endl;
    LinkList<int> myList;
    myList.add(myList.end(), 1);
    myList.add(myList.end(), 2);
    myList.add(myList.end(), 3);
    LinkList<int>::iterator it = myList.begin();
    auto value = ++it;
    std::cout << "Lvalue Iterator points to: " << *value << " | Expected: 2" << std::endl;
	*(++it) = 42;
    std::cout << "Rvalue Iterator points to: " << *(it)  << " | Expected: 42" << std::endl;

}

void testReverse() {
	LinkList<int> myList;
    myList.add(myList.end(), 1);
    myList.add(myList.end(), 2);
    myList.add(myList.end(), 3);
    std::cout << "\n### Test Reverse Function ###" << std::endl;
    std::cout << "Original List: ";
    myList.print_list();
    myList.reverse();
    std::cout << "\nReversed List: ";
	myList.print_list();
    LinkList<int> list2;
    list2.add(list2.end(), 1);
    list2.add(list2.end(), 2);
    list2.add(list2.end(), 3);
    list2.add(list2.end(), 4);
    list2.add(list2.end(), 5);
	list2.add(list2.end(), 6);
    std::cout << "\n### Test Reverse Function with expanded values ###" << std::endl;
    std::cout << "Original List: ";
    list2.print_list();
    list2.reverse();
    std::cout << "\nReversed List: ";
    list2.print_list();
	LinkList<int> list3;
    std::cout << "\n### Test Reverse Function on Empty List ###" << std::endl;
    std::cout << "Original List: ";
    list3.print_list();
    list3.reverse();
    std::cout << "\nReversed List: ";
	list3.print_list();
}

void testBinarySearchTreeAdd() {
	BinarySearchTree bst;
	bst.Add(50);
	bst.Add(30);
	bst.Add(70);
    bst.Add(80);
	bst.Add(40);

}

void testInOrderTraversal() {
    BinarySearchTree bst;
    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(80);
    bst.Add(40);
    std::vector<int> inorder = bst.inOrder();
    std::cout << "\n### Test Binary Search Tree Inorder Traversal ###" << std::endl;
    std::cout << "Inorder Traversal: ";
    for (int val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void testBSTCopyConstructor() {
	BinarySearchTree bst;
	bst.Add(50);
	bst.Add(30);
	bst.Add(70);
	BinarySearchTree bst2 = bst;
    std::vector<int> inorder = bst.inOrder();
    std::vector<int> inorder2 = bst.inOrder();
    std::cout << "\n### Test Binary Search Tree Copy Constructor Traversal ###" << std::endl;
    std::cout << "Original Tree: ";
    for (int val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Copied Tree: ";
    for (int val : inorder2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void testDeserializeTree() {
	std::vector<int> data = { 7, 5, 10};
	BinarySearchTree bst;
	bst.deserialize(data);
	std::cout << "\n### Test Binary Search Tree Deserialization ###" << std::endl;
	bst.printPreOrder();
    data = { 7, 3, 5, 10 };
    bst.deserialize(data);
    std::cout << "\n### Test Binary Search Tree Deserialization Slightly Bigger###" << std::endl;
    bst.printPreOrder();
	data = { 12, 8, 5, 4, 6, 10, 9, 11, 17, 15, 14, 16, 19, 18, 20 };
	bst.deserialize(data);
	std::cout << "\n### Test Binary Search Tree Deserialization Much Bigger###" << std::endl;
	bst.printPreOrder();
}

void testingLambdaPreorder() {
    BinarySearchTree bst;
    bst.Add(50);
    bst.Add(30);
    bst.Add(90);
    bst.Add(70);
    bst.Add(10);
    cout << endl;
    // --- CASE 1: Printing directly ---
    std::cout << "Printing Pre-Order: ";
    bst.preOrderTraversal([](int data) {
        std::cout << data << " ";
        });
    std::cout << std::endl;

    // --- CASE 2: Saving to a list (Serialization) ---
    std::vector<int> serializedValues;
    bst.preOrderTraversal([&serializedValues](int data) {
        serializedValues.push_back(data);
        });

    std::cout << "Vector size is now: " << serializedValues.size() << std::endl;
    std::cout << std::endl;
}

void testPrintPostOrder() {
	BinarySearchTree bst;
    bst.Add(7);
	bst.Add(3);
    bst.Add(9);
	bst.PrintPostOrder();
    BinarySearchTree bst2;
    bst2.Add(7);
    bst2.Add(4);
    bst2.Add(2);
    bst2.Add(11);
    bst2.Add(9);
    bst2.PrintPostOrder();
	BinarySearchTree bst3;
    bst3.Add(8);
	bst3.Add(6);
    bst3.Add(4);
    bst3.Add(7);
	bst3.Add(10);
    bst3.Add(9);
    bst3.Add(11);
    bst3.PrintPostOrder();
}

void testPostOrderLambdas() {
  BinarySearchTree bst;
    bst.Add(50);
    bst.Add(30);
    bst.Add(90);
    bst.Add(70);
    bst.Add(10);
    cout << endl;
    std::cout << "Printing Post-Order: ";
    bst.PostOrderTraversal([](int data) {
        std::cout << data << " ";
        });
    std::cout << std::endl;
    std::vector<int> serializedValues;
    bst.PostOrderTraversal([&serializedValues](int data) {
        serializedValues.push_back(data);
        });
    std::cout << "Vector size is now: " << serializedValues.size() << std::endl;
	for (auto val : serializedValues) {
        std::cout << val << " ";
    }
	std::cout << std::endl;
}

void testDeserializeTreePostOrder() {
    std::vector<int> data = { 5, 10, 7 };
    BinarySearchTree bst;
    bst.deserializePostOrder(data);
    std::cout << "\n### Test Binary Search Tree Deserialization Post Order ###" << std::endl;
    bst.PrintPostOrder();
    data = { 5, 3, 7, 10 };
    bst.deserializePostOrder(data);
    std::cout << "\n### Test Binary Search Tree Deserialization Post Order Slightly Bigger###" << std::endl;
    bst.PrintPostOrder();
    data = {4, 6, 5, 9, 11, 10, 8, 14, 16, 15, 18, 20, 19, 17, 12 };
    bst.deserializePostOrder(data);
    std::cout << "\n### Test Binary Search Tree Deserialization Post Order Much Bigger###" << std::endl;
    bst.PrintPostOrder();
}

void testBalance() {
    BinarySearchTree bst;
	bst.addBalanced(10);
	bst.addBalanced(20);
	bst.addBalanced(30);
    BinarySearchTree bst2;
    bst2.Add(20);
    bst2.Add(10);
    bst2.Add(30);
    if (bst.compareTrees(bst2, bst)) {
        std::cout << "\nPassed: Tree was balanced correctly" << std::endl;
	}
	BinarySearchTree bst3;
	bst3.addBalanced(50);
	bst3.addBalanced(40);
	bst3.addBalanced(30);
    if (bst.compareTrees(bst2, bst3)) {
        std::cout << "\nPassed: Second Tree was balanced correctly" << std::endl;
	}
    bst.addBalanced(40);
    bst.addBalanced(50);
    BinarySearchTree bst4;
	bst4.Add(20);
	bst4.Add(10);
	bst4.Add(40);
	bst4.Add(30);
	bst4.Add(50);
	if (bst.compareTrees(bst, bst4)) {
        std::cout << "\nPassed: Trees are equal after adding extra node -- right heavy" << std::endl;
    }
    bst3.addBalanced(20);
    bst3.addBalanced(10);
	BinarySearchTree bst5;
    bst5.Add(40);
    bst5.Add(50);
    bst5.Add(20);
    bst5.Add(30);
    bst5.Add(10);
    if (bst.compareTrees(bst3, bst5)) {
        std::cout << "\nPassed: Trees are equal after adding extra node -- left heavy" << std::endl;
    }
}

void testAstarSearch() {
    Map astar;
    vector<std::tuple<int, int>> mountains = { {0,2}, {1,1} };
    astar.populateBoard(3, mountains);
    std::vector<std::tuple<int, int>> values = astar.aStarSearch(0, 0, 2, 2);
    std::cout << "----------------------------" << std::endl;
    astar.populateBoard(3, mountains);
    std::vector<std::tuple<int, int>> values2 = astar.aStarSearch(0, 0, 1, 2);
    std::cout << "----------------------------" << std::endl;
    Map astar2;
    vector<std::tuple<int, int>> mountains2 = { {0,3}, {2,0}, {2,2}, {2,3}, {3,4}, {4,2} };
	astar2.populateBoard(5, mountains2);
    std::vector<std::tuple<int, int>> values3 = astar2.aStarSearch(0, 0, 4, 4);
    std::cout << "----------------------------" << std::endl;
    vector<std::tuple<int, int>> mountains3 = { {0,3}, {2,0}, {2,2}, {2,3}, {3,2}, { 3,4 }, {4,2} };
    astar2.populateBoard(5, mountains3);
    std::vector<std::tuple<int, int>> values4 = astar2.aStarSearch(0, 0, 4, 4);
    std::cout << "----------------------------" << std::endl;
    Map astar3;
    vector<std::tuple<int, int>> mountains4 = { {2,2}, {2,3}, {2,4}, {3,2}, {3,4}, { 4,2 },{4, 4}};
	astar3.populateBoard(7, mountains4);
	std::vector<std::tuple<int, int>> values5 = astar3.aStarSearch(0, 0, 3, 3);
}

void testAstarSearchParentStyle() {
    Map astar;
	std::cout << "\n### Test A* Search Parent Style ###" << std::endl;
    vector<std::tuple<int, int>> mountains = { {0,2}, {1,1} };
    astar.populateBoard(3, mountains);
    std::vector<std::tuple<int, int>> values = astar.aStarSearchParentStyle(0, 0, 2, 2, false, 0);
    std::cout << "----------------------------" << std::endl;
    astar.populateBoard(3, mountains);
    std::vector<std::tuple<int, int>> values2 = astar.aStarSearchParentStyle(0, 0, 1, 2, false, 0);
	std::cout << "----------------------------" << std::endl;
    /*Astar astar2;
    vector<std::tuple<int, int>> mountains2 = { {0,3}, {2,0}, {2,2}, {2,3}, {3,4}, {4,2} };
    astar2.populateBoard(5, mountains2);
    std::vector<std::tuple<int, int>> values3 = astar2.aStarSearchParentStyle(0, 0, 4, 4);
    std::cout << "----------------------------" << std::endl;
    vector<std::tuple<int, int>> mountains3 = { {0,3}, {2,0}, {2,2}, {2,3}, {3,2}, { 3,4 }, {4,2} };
    astar2.populateBoard(5, mountains3);
    std::vector<std::tuple<int, int>> values4 = astar2.aStarSearchParentStyle(0, 0, 4, 4);
    std::cout << "----------------------------" << std::endl;
    Astar astar3;
    vector<std::tuple<int, int>> mountains4 = { {2,2}, {2,3}, {2,4}, {3,2}, {3,4}, { 4,2 },{4, 4} };
    astar3.populateBoard(7, mountains4);
    std::vector<std::tuple<int, int>> values5 = astar3.aStarSearchParentStyle(0, 0, 3, 3);*/

}

void arg(int x) {
    x += 2;
    return;
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
    testEmptyRemove();
    testIntegerList();
    testStringList();
    test_print_list();
    testIteratorIncrement();
    test_initialization_and_traversal();
    test_bidirectional_movement();
    test_equality_by_value();
    test_out_of_range_exception();
    testReverse();
    testBinarySearchTreeAdd();
	testInOrderTraversal();
    testBSTCopyConstructor();
    testDeserializeTree();
    testingLambdaPreorder();
    testPrintPostOrder();
    testPostOrderLambdas();
    testDeserializeTreePostOrder();
    testBalance();
	testAstarSearch();
    testAstarSearchParentStyle();
}