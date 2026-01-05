#include "BinarySearchTree.h"
#include <vector>
#include <iostream>
#include <map>
#include <limits>
BinarySearchTree::BinarySearchTree() {
	head = nullptr;
}
BinarySearchTree::BinarySearchTree(BinarySearchTree& other) noexcept {
	if (other.head == nullptr) {
		head = nullptr;
	}
	else {
		head = copyTree(other.head);
	}
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept {
	head = other.head;
	other.head = nullptr;
}

BinarySearchTree::Node* BinarySearchTree::copyTree(Node* other) {
	if (other == nullptr) {
		return nullptr;
	}
	Node* newNode = new Node{ other->data, nullptr, nullptr };
	newNode->left = copyTree(other->left);
	newNode->right = copyTree(other->right);
	return newNode;
}

BinarySearchTree::Node* BinarySearchTree::AddPrivate(Node* node, int value) {
	if(node == nullptr) {
		node = new Node{value, nullptr, nullptr};
		return node;
	}
	if (value > node->data) {
		node->right = AddPrivate(node->right, value);
	}
	else {
		node->left = AddPrivate(node->left, value);
	}
	return node;
}
void BinarySearchTree::Add(int value) {
	head = AddPrivate(head, value);
}


std::vector<int> BinarySearchTree::inOrderPrivate(Node* node) {
if (node == nullptr) {
		return {};
	}
	std::vector<int> leftSide = inOrderPrivate(node->left);
	leftSide.push_back(node->data);
	std::vector<int> rightSide = inOrderPrivate(node->right);
	leftSide.insert(leftSide.end(), rightSide.begin(), rightSide.end());
	return leftSide;
}

std::vector<int> BinarySearchTree::inOrder() {
	return inOrderPrivate(head);
}

void BinarySearchTree::printTree() {
	std::vector<int> inorder = inOrder();
	for (auto val : inorder) {
		std::cout << val << " ";
	}
}

BinarySearchTree::Node* BinarySearchTree::deserializePrivate(std::vector<int>& values, int& index, int limit) {
	if (index >= values.size() || values[index] > limit) {
		return nullptr;
	}
	Node* node = new Node{ values[index], nullptr, nullptr };
	index++;
	node->left = deserializePrivate(values, index, node->data);
	node->right = deserializePrivate(values, index, limit);
	return node;
}

void BinarySearchTree::deserialize(std::vector<int>& values) {
	int index = 0;
	 head = deserializePrivate(values, index, std::numeric_limits<int>::max());
}

void BinarySearchTree::preOrderPrivate(Node* node, std::function<void(int)> action) {
	if (node == nullptr) return;

	action(node->data);               
	preOrderPrivate(node->left, action);  
	preOrderPrivate(node->right, action); 
}

void BinarySearchTree::preOrderTraversal(std::function<void(int)> action) {
	preOrderPrivate(head, action);
}

void BinarySearchTree::printPreOrder() {
	preOrderTraversal([](int val) {
		std::cout << val << " ";
	});
	std::cout << std::endl;
}

std::vector<int> BinarySearchTree::serializePreOrder() {
	std::vector<int> values;
	preOrderTraversal([&values](int val) {
		values.push_back(val);
	});

	return values;
}
void BinarySearchTree::PrintPostOrder() {
	printPostOrderPrivate(head);
	std::cout << std::endl;
}


void BinarySearchTree::printPostOrderPrivate(Node* node) {
	if (node == nullptr) return;
	printPostOrderPrivate(node->left);  
	printPostOrderPrivate(node->right); 
	std::cout << node->data << " ";               
}

void BinarySearchTree::PostOrderTraversalPrivate(Node* node, std::function<void(int)> action) {
	if (node == nullptr) return;
	PostOrderTraversalPrivate(node->left, action);  
	PostOrderTraversalPrivate(node->right, action); 
	action(node->data);               
}

void BinarySearchTree::PostOrderTraversal(std::function<void(int)> action) {
	PostOrderTraversalPrivate(head, action);
}

BinarySearchTree::Node* BinarySearchTree::deseralizeTreePostOrderPrivate(std::vector<int>& values, size_t& index, int minLimit) {
	if (index < 0 || values[index] < minLimit) {
		return nullptr;
	}
	Node* node = new Node{ values[index], nullptr, nullptr };
	if (index != 0) {
		index--;
		node->right = deseralizeTreePostOrderPrivate(values, index, node->data);
		node->left = deseralizeTreePostOrderPrivate(values, index, minLimit);
	}
	return node;
}

void BinarySearchTree::deserializePostOrder(std::vector<int>& values) {
	size_t index = values.size() - 1;
	head = deseralizeTreePostOrderPrivate(values, index, std::numeric_limits<int>::min());
}

int BinarySearchTree::getHeight(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	return std::max(leftHeight, rightHeight) + 1;
}

int BinarySearchTree::getBalance(Node* node) {
	if (node == nullptr) return 0;
	return getHeight(node->left) - getHeight(node->right);
}

BinarySearchTree::Node* BinarySearchTree::rotateRight(Node* root) {
	Node* left = root->left;
	Node* Temp = left->right;
	left->right = root;
	root->left = Temp;
	return left;              
}

BinarySearchTree::Node* BinarySearchTree::rotateLeft(Node* root) {
	Node* right = root->right;
	Node* Temp = right->left;
	right->left = root;
	root->right = Temp;
	return right;            
}

BinarySearchTree::Node* BinarySearchTree::addBalancedPrivate(Node* node, int value) {
	if (node == nullptr) {
		node = new Node{ value, nullptr, nullptr };
		return node;
	}
	if (value > node->data) {
		node->right = addBalancedPrivate(node->right, value);
	}
	else {
		node->left = addBalancedPrivate(node->left, value);
	}
	int balance = getBalance(node);
	if (balance > 1) {
		return rotateRight(node);
	}
	else if (balance < -1) {
		return rotateLeft(node);
	}
	return node;
}

BinarySearchTree::Node* BinarySearchTree::addBalanced(int value) {
	head = addBalancedPrivate(head, value);
	return head;
}

bool BinarySearchTree::compareTreesPrivate(Node* node1, Node* node2) {
	if (node1 == nullptr && node2 == nullptr) {
		return true;
	}
	if (node1 == nullptr || node2 == nullptr) {
		return false;
	}
	if (node1->data != node2->data) {
		return false;
	}
	return compareTreesPrivate(node1->left, node2->left) && compareTreesPrivate(node1->right, node2->right);
}

bool BinarySearchTree::compareTrees(BinarySearchTree node1, BinarySearchTree node2) {
	return compareTreesPrivate(node1.head, node2.head);
}