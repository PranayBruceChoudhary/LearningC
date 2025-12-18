#include <iostream>
	template <typename T>
	LinkList<T>::LinkList() noexcept {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	template <typename T>
	LinkList<T>::LinkList(LinkList& other) {
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;

		Node* current = other.head; 

		while (current != nullptr) {
			Node* newNode = new Node();
			newNode->data = current->data;
			newNode->next = nullptr;

			if (this->head == nullptr) {
				this->head = newNode;
				newNode->prev = nullptr;
			}
			else {
				tail->next = newNode;
				newNode->prev = tail;
			}
			this->tail = newNode;
			this->size++;
			current = current->next;
		}
	}
	template <typename T>
	LinkList<T>::LinkList(LinkList&& other) noexcept {
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	template <typename T>
	LinkList<T>::~LinkList() {
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
	template <typename T>
	size_t LinkList<T>::getSize() {
		return this->size;
	}
	template <typename T>
	LinkList<T>::iterator LinkList<T>::begin() {
		return iterator(head);
	}
	template <typename T>
	LinkList<T>::iterator LinkList<T>::end() {
		return iterator(nullptr);
	}
	template <typename T>
	LinkList<T>::iterator LinkList<T>::back() {
		return iterator(tail);
	}
	template <typename T>
	T& LinkList<T>::iterator::operator*() const {
		if (!current) {
			throw std::out_of_range("Attempt to dereference a null iterator (LinkList::end()).");
		}
		return current->data;
	}
	template <typename T>
	LinkList<T>::iterator& LinkList<T>::iterator::operator++() { // works only for prefix ++it ?
		if (current) {
			current = current->next;
		}
		return *this;
	}
	template <typename T>
	LinkList<T>::iterator& LinkList<T>::iterator::operator--() {
		if (current) {
			current = current->prev;
		}
		return *this;
	}
	template <typename T>
	bool LinkList<T>::iterator::operator==(const iterator& other) const {
		if (other.current == nullptr) {
			return current == other.current;
		}
		return other.current->data == current->data;
	}
	template <typename T>
	bool LinkList<T>::iterator::operator!=(const iterator& other) const {
		if (other.current == nullptr) {
			return current != other.current;
		}
		else {
			return other.current->data != current->data;
		}
	}
	template <typename T>
	void LinkList<T>::add(iterator position, const T& value) {
		Node* newNode = new Node{ value, nullptr, nullptr };
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}

		else if (position.current == nullptr) {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		else {
			Node* nextNode = position.current;
			Node* prevNode = nextNode->prev;
			newNode->next = nextNode;
			newNode->prev = prevNode;
			nextNode->prev = newNode;
			if (prevNode != nullptr) {
				prevNode->next = newNode;
			}
			else {
				head = newNode;
			}
		}
		size++;
	}
	template <typename T>
	T LinkList<T>::remove(iterator position) {
		if (position.current == nullptr || size == 0) {
			throw std::out_of_range("Error: current is nullptr or size is 0");
		}
		Node* toDelete = position.current;
		T data = toDelete->data;
		Node* nextNode = toDelete->next;
		Node* prevNode = toDelete->prev;
		if (toDelete == tail && toDelete != head) {
			tail = prevNode;
			tail->next = nullptr;			
		}

		else if (toDelete == head && toDelete != tail) {
			head = nextNode;
			head->prev = nullptr;
		}
		else if (toDelete == tail && toDelete == head) {
			
		}
		else {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}
		size--;

		delete toDelete;
		return data;
	}
	template <typename T>
	void LinkList<T>::print_list(){
		std::cout << "List Contents (Size: " << this->size << "): ";
		for (LinkList::iterator it = this->begin(); it != this->end(); ++it) {
			std::cout << "[" << *it << "] -> ";
		}
	}