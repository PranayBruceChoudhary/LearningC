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
	LinkList() noexcept;
	LinkList(LinkList& other);
	LinkList(LinkList&& other) noexcept; // no new memory allocation
	~LinkList();
	class iterator {
    private:
        Node* current;
    public:
        using value_type = T;
        iterator(Node* p = nullptr) {
            current = p;
        }
        T& operator*() const;
        iterator& operator++() noexcept;
        iterator& operator--() noexcept;
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        friend class LinkList;
    };
    // Operations
    void add(LinkList::iterator position, const T& value);
    T remove(LinkList::iterator position);
    iterator begin();
    iterator end();
    iterator back();
    void print_list();
    size_t getSize();
	// Reverse Iterator
    class reverse_iterator {
    private:
        Node* current;
    public:
        using value_type = T;
        reverse_iterator(Node* p = nullptr) {
			current = p;
        }
        T& operator*() const;
		reverse_iterator& operator++() noexcept;
        reverse_iterator& operator--() noexcept;
        bool operator==(const reverse_iterator& other) const;
        bool operator!=(const reverse_iterator& other) const;
		friend class LinkList;
    };
	// Reverse Operations
    reverse_iterator rbegin();
    reverse_iterator rend();
	reverse_iterator rback();
    void reverse();

};
#include "LinkList.tpp"


