#pragma once
class LinkListNoTemp
{
private:
	struct Node {
		int data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	size_t size;
public:
public:
    LinkListNoTemp();
    LinkListNoTemp(LinkListNoTemp& other);
    LinkListNoTemp(LinkListNoTemp&& other) noexcept;
    ~LinkListNoTemp();
    size_t getSize();
    class iterator {
    private:
        Node* current;
    public:
        using value_type = int;
        using pointer = int*;
        using reference = int&;
        iterator(Node* p = nullptr) {
            current = p;
        }
        reference operator*() const;
        iterator& operator++();
        iterator& operator--();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        friend class LinkListNoTemp;
    };
    void add(LinkListNoTemp::iterator position, const int& value);
    int remove(LinkListNoTemp::iterator position);
    iterator begin();
    iterator end();
    iterator back();
    void print_list();
};

