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
        iterator& operator++();
        iterator& operator--();
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
};
#include "LinkList.tpp"


