#pragma once
#include <vector>
#include <functional> 

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
    };
    Node* head;
    Node* AddPrivate(Node* node, int value);
    std::vector<int> inOrderPrivate(Node* node);
    Node* copyTree(Node* other);
    Node* deserializePrivate(std::vector<int>& values, int& index, int limit);
    void preOrderPrivate(Node* node, std::function<void(int)> action);
	void printPostOrderPrivate(Node* node);
	void PostOrderTraversalPrivate(Node* node, std::function<void(int)> action);
	Node* deseralizeTreePostOrderPrivate(std::vector<int>& values, size_t& index, int minLimit);
	Node* addBalancedPrivate(Node* node, int value);
	bool compareTreesPrivate(Node* node1, Node* node2);
public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree& other) noexcept;
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    void Add(int value);
    std::vector<int> inOrder();
	void printTree();
	void deserialize(std::vector<int>& values);
	void printPreOrder();
    void preOrderTraversal(std::function<void(int)> action);
    std::vector<int> serializePreOrder();
    void PrintPostOrder();
    void PostOrderTraversal(std::function<void(int)> action);
    void deserializePostOrder(std::vector<int>& values);
    int getHeight(Node* node);
    // Match the implementation: balanceTree returns a Node* (rebalances subtree and returns new root)
    int getBalance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
	bool compareTrees(BinarySearchTree node1, BinarySearchTree node2);
	Node* addBalanced(int value);
};