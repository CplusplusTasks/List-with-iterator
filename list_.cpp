#include "list_.h"

struct node {
    node *next, *prev;
    int key;

    node();
    node(int);
    node(node const* other); 
};

node::node() :
    next(0),
    prev(0),
    key(0) {}

node::node(int x) :
    next(0),
    prev(0),
    key(x) 
{} 

list::list() 
    :fake(new node), 
    ptr(fake) {}
 
list::const_iterator::const_iterator(node* other) :
    cur(other) {}

list::iterator::iterator(node* other) :
    cur(other) {}

list::~list() {
    while (ptr != fake)  {
        node* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    delete fake;
}

list::list(list const& other)
{
    fake = new node;
    ptr = fake; 
    try {
        for (node const* beg = other.ptr; beg != other.fake; beg = beg->next) {
            push_back(beg->key);
        }
    } catch(...) {
        for (node const* beg = ptr; beg != fake;) {
            node const* temp = beg;
            beg = beg->next;
            delete temp;
        }
        delete fake;
        throw;
    }
}

list& list::operator=(list const& other) {
    list temp(other);

    for (node const* beg = other.ptr; beg != other.fake; beg = beg->next) {
        push_back(beg->key);
    }

    return *this;
}

void list::push_front(int x) {
    try {
        node* temp = new node(x);
        if (ptr != fake) {
            ptr->prev = temp;
            temp->next = ptr;
            fake->next = temp;
            temp->prev = fake;
        } else {
            fake->prev = temp;
            fake->next = temp;

            temp->next = fake;
            temp->prev = fake;
        }

        ptr= temp;
    } catch(...) {
        throw;     
    }
}

void list::push_back(int x) {
    try {
        node* temp = new node(x);
        temp->next = fake;

        if (ptr != fake) {
            temp->prev = fake->prev;
            fake->prev->next = temp;
            fake->prev = temp;
        } else {
            fake->prev = temp;
            fake->next = temp;

            temp->prev = fake;
            ptr= temp;
        }

    } catch(...) {
        throw;     
    }
}

int& list::front() {
    return ptr->key;
}

int& list::back() {
    return fake->prev->key;
}

int const& list::back() const {
    return fake->prev->key;
}

int const& list::front() const {
    return ptr->key;
}

bool list::empty() const {
    return (ptr == fake);
}

void list::pop_back() { //INV : !list.empty()
    assert(ptr != 0);
    node* temp = fake->prev;

    fake->prev = fake->prev->prev;
    fake->prev->prev->next = fake;
    delete temp;
}

void list::pop_front() { //INV : !list.empty()
    assert(ptr != 0);
    node* temp = ptr;
    ptr = ptr->next;
    delete temp;
}

int const& list::const_iterator::operator*() const {
    return cur->key;
}

list::const_iterator& list::const_iterator::operator++() {
    cur = cur->next;
    return *this; 
}

list::const_iterator list::const_iterator::operator++(int) {
    const_iterator temp = *this;
    cur = cur->next;
    return temp;
}

list::const_iterator& list::const_iterator::operator--() {
    cur = cur->prev;
    return *this;
}

list::const_iterator list::const_iterator::operator--(int) {
    const_iterator temp = *this;
    cur = cur->prev;
    return temp;
}

list::iterator list::end() {
    return list::iterator(fake);
}

list::iterator list::begin() {
    return list::iterator(ptr);
}

int& list::iterator::operator*() const {
    return cur->key;
}

list::iterator& list::iterator::operator++() {
    cur = cur->next;
    return *this; 
}

void list::insert(iterator pos, int value) {
    try {
        node* temp = new node(value);

        temp->next = pos.cur;
        temp->prev = pos.cur->prev;

        pos.cur->prev->next = temp;
        pos.cur->prev = temp;
        while (ptr->prev != fake) ptr = ptr->prev;

    } catch(...) {
        throw;     
    }
}

bool operator==(list::iterator const& a, list::iterator const& b) {
   return a.cur == b.cur; 
}
 
void list::splice(iterator pos, list& other, iterator first, iterator last) {
    list::iterator nw(last.cur->prev);
    
    first.cur->prev->next = last.cur;
    last.cur->prev = first.cur->prev;

    first.cur->prev = pos.cur->prev;
    pos.cur->prev->next = first.cur;

    pos.cur->prev = nw.cur;
    nw.cur->next = pos.cur;

    if (pos.cur == ptr) {
        ptr = first.cur;
    }

    if (first.cur == other.ptr) {
        other.ptr = last.cur;
    }
}

list::iterator list::iterator::operator++(int) {
    iterator temp = *this;
    cur = cur->next;
    return temp;
}

list::iterator& list::iterator::operator--() {
    cur = cur->prev;
    return *this;
}

list::iterator list::iterator::operator--(int) {
    iterator temp = *this;
    cur = cur->prev;
    return temp;
}

void list::erase(iterator pos) {
    assert(pos.cur != fake);
    pos.cur->next->prev = pos.cur->prev;
    pos.cur->prev->next = pos.cur->next;
    if (pos.cur == ptr) ptr = ptr->next;
    delete pos.cur;
}

