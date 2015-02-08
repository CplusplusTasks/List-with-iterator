#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iosfwd>

struct node;
struct list {
public:
    ~list();
    struct const_iterator;
    struct iterator; 
    list();
    list(list const& other);
    list& operator=(list const&);
    bool empty() const;
    void push_back(int);
    void pop_back(); //INV : !list.empty()

    void push_front(int);
    void pop_front(); //INV : !list.empty()

    int& back();
    int const& back() const;

    int& front();
    int const& front() const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    void insert(iterator pos, int value);
    void erase(iterator pos);
    void splice(iterator pos, list& other, iterator first, iterator last);

private:
    node *fake, *ptr;
    friend struct node;
};

struct list::const_iterator {
public:
    int const& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);

    const_iterator& operator--();
    const_iterator operator--(int);
    friend bool operator==(const_iterator const& a, const_iterator const& b);
private: 
    node* cur;

    const_iterator(node* other);
    
friend class list;
};

struct list::iterator {
public:
    int& operator*() const;
    iterator& operator++();
    iterator operator++(int);

    iterator& operator--();
    iterator operator--(int);
    friend bool operator==(iterator const& a, iterator const& b);
private: 
    node* cur;

    iterator(node* other);

    
friend class list;
};

bool operator==(list::iterator const& a, list::iterator const& b);

#endif

