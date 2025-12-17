#include "LinkListNoTemp.h"
#include <iostream>

LinkListNoTemp::LinkListNoTemp() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

LinkListNoTemp::LinkListNoTemp(LinkListNoTemp& other) {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;

	Node* current = other.head;
	Node* lastNewNode = nullptr;

	while (current != nullptr) {
		Node* newNode = new Node;
		newNode->data = current->data;
		newNode->next = nullptr;

		if (this->head == nullptr) {
			this->head = newNode;
			newNode->prev = nullptr;
		}
		else {
			lastNewNode->next = newNode;
			newNode->prev = lastNewNode;
		}
		this->tail = newNode;
		lastNewNode = newNode;
		this->size++;
		current = current->next;
	}
}

LinkListNoTemp::LinkListNoTemp(LinkListNoTemp&& other) noexcept {
	head = other.head;
	tail = other.tail;
	size = other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

LinkListNoTemp::~LinkListNoTemp() {
	Node* current = head;
	while (current != nullptr) {
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	size = 0;
}

size_t LinkListNoTemp::getSize() {
	return this->size;
}

LinkListNoTemp::iterator LinkListNoTemp::begin() {
	return iterator(head);
}

LinkListNoTemp::iterator LinkListNoTemp::end() {
	return iterator(nullptr);
}

LinkListNoTemp::iterator LinkListNoTemp::back() {
	return iterator(tail);
}

LinkListNoTemp::iterator::reference LinkListNoTemp::iterator::operator*() const {
	if (!current) {
		throw std::out_of_range("Attempt to dereference a null iterator (LinkListNoTemp::end()).");
	}
	return current->data;
}

LinkListNoTemp::iterator& LinkListNoTemp::iterator::operator++() {
	if (current) {
		current = current->next;
	}
	return *this;
}

LinkListNoTemp::iterator& LinkListNoTemp::iterator::operator--() {
	if (current) {
		current = current->prev;
	}
	return *this;
}

bool LinkListNoTemp::iterator::operator==(const iterator& other) const {
	return current == other.current;
}

bool LinkListNoTemp::iterator::operator!=(const iterator& other) const {
	return current != other.current;
}

void LinkListNoTemp::add(iterator position, const int& value) {
	Node* newNode = new Node{ value, nullptr, nullptr };
	size++;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		return;
	}

	if (position.current == nullptr) {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		return;
	}
}

int LinkListNoTemp::remove(iterator position) {
	if (position.current == nullptr || size == 0) {
		throw std::out_of_range("Error: current is nullptr or size is 0");
	}
	Node* toDelete = position.current;
	int data = toDelete->data;
	Node* nextNode = toDelete->next;
	Node* prevNode = toDelete->prev;
	if (toDelete == tail) {
		tail = prevNode;
		tail->next = nullptr;
		//tail->prev = prevNode->prev;
	}

	if (toDelete == head) {
		head = nextNode;
		head->prev = nullptr;
	}
	size--;

	delete toDelete;
	return data;
}

void LinkListNoTemp::print_list() {
	std::cout << "List Contents (Size: " << this->size << "): ";
	for (LinkListNoTemp::iterator it = this->begin(); it != this->end(); ++it) {
		std::cout << "[" << *it << "] -> ";
	}
}
