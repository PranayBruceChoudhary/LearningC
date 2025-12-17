#pragma once
#include <stdexcept>
template <typename T>
class LinkList
{
private:
	struct Node {
	    T data;
	    Node* next;
	    Node* prev;
    };
	Node* head;
	Node* tail;
	size_t size;
public:
	LinkList();
	LinkList(LinkList& other);
	LinkList(LinkList&& other) noexcept;
	~LinkList();
    size_t getSize();
	class iterator {
    private:
        Node* current;
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        iterator(Node* p = nullptr) {
            current = p;
        }
        reference operator*() const;
        iterator& operator++();
        iterator& operator--();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        friend class LinkList;
    };
    void add(LinkList::iterator position, const T& value);
    T remove(LinkList::iterator position);
    iterator begin();
    iterator end();
    iterator back();
    void print_list();
};
#include "LinkList.tpp"


