/*
CS 302 Assignment 1

Name: Keith Beauvais, 5005338658, CS 302 Assignment 1
*/
#include <iostream> 
#include <fstream>

template <typename type>
class LL{
    
    struct node{
        type data;
        node * prev;
        node * next;
    };

    public:
        class iterator{
            public:
                friend class LL;
                iterator();
                iterator(node* ptr);
                type operator*() const;
                const iterator& operator++(int);
                const iterator& operator--(int);
                bool operator== (const iterator& rhs) const;
                bool operator!= (const iterator& rhs) const;
            private:
                node * current;
        };

    LL();
    LL(const LL<type>& copy);
    const LL<type>& operator=(const LL <type>& rhs);
    ~LL();
    void tailInsert(const type& item);
    iterator begin() const;
    iterator end() const;
    void swapNodes(iterator&it1, iterator&it2);
    
    private:
        node * head;
        node * tail;
        void deleteLhs();

};

/* iterator() - constructor that sets the current ptr to NULL.

return value - n/a
*/
template <typename type> 
LL<type>::iterator::iterator(){
    current = NULL;
}

/* iterator(node * ptr) - parameterized constructor that passes in a pointer and sets it to current pointer

return value - n/a
*/
template <typename type> 
LL<type>::iterator::iterator(node * ptr){
    current = ptr;
}

/* 
operator*() - overloads the iterator’s derefence operator, returns
current->data

return value - n/a
*/
template <typename type> 
type LL<type>::iterator::operator*() const{
    
    return current -> data;

}

/* 
operator++(int) - moves the iterator over one node to the right

return value - n/a
*/
template <typename type> 
const typename LL<type>::iterator& LL<type>::iterator::operator++(int){
    
    current = current -> next;
    return *this;
    
}

template <typename type> 
const typename LL<type>::iterator& LL<type>::iterator::operator--(int){
    
    current = current -> prev;
    return *this;
    
}

/* 
operator==(const iterator& rhs) - returns true if this iterator and rhs iterator 
point to the same node, returns false otherwise

return value - Either true or false 
*/
template <typename type> 
bool LL<type>::iterator::operator==(const iterator& rhs) const{
    
    if(this->current == rhs.current){
        return true;
    }
    else{
        return false;
    }

}

/* 
operator!=(const iterator& rhs) - returns true if this iterator and the rhs iterator
do not point to the same node, returns false otherwise

return value - Either true or false 
*/
template <typename type> 
bool LL<type>::iterator::operator!=(const iterator& rhs) const{
    
    if(this->current != rhs.current){
        return true;
    }
    else{
        return false;
    }
}

/* 
LL() - default constructor, sets head and tail to NULL

return value - n/a
*/
template <typename type> 
LL<type>::LL(){
    head = NULL;
    tail = NULL;
}

/* 
LL(const LL<type>& copy) - deep copy constructor, performs a deep copy of the copy
linked list into the this linked list

return value - n/a
*/
template <typename type> 
LL<type>::LL(const LL<type>& copy){
    
    if(copy.head == NULL){
      return; 
    }

    else{
        node * temp;
        temp = new node;
        this -> head = temp;
        temp -> data= copy.head -> data; 
        temp -> next = NULL;
        temp -> prev = NULL;
        node * i1, *i2;
        i1 = copy.head;
        i2 = temp;
        i1 = i1-> next;

        while(i1 != NULL){
            i2 -> next = new node;
            i2 = i2 -> next;
            i2 -> data = i1 -> data;
            i1 = i1 -> next;
            i2 -> next= NULL;
        }
        return; 
    }
    
}

/* 
operator=(const LL<type>& rhs)- deep copy assignment operator,
performs a deep copy of the rhs object into the this object, remember to check for a self assignment,
deallocate the this linked list before performing the actual deep copy, and at the end return *this

return value - *this
*/
template <typename type> 
const LL<type>& LL<type>::operator=(const LL<type> &rhs){
    
    deleteLhs();
    if(rhs.head == NULL){
        this -> head = NULL;
        return *this;
    }
    else{
        node * temp;
        temp = new node;
        this -> head = temp;
        temp -> data= rhs.head -> data; 
        temp -> next = NULL;
        temp -> prev = NULL;
        node * i1, *i2;
        i1 = rhs.head;
        i2 = temp;
        i1 = i1-> next;

        while(i1 != NULL){
            i2 -> next = new node;
            i2 = i2 -> next;
            i2 -> data = i1 -> data;
            i1 = i1 -> next;
            i2 -> next= NULL;
        }
        return *this; 
    }
    
}

/* 
~LL()- estructor, deallocates the entire linked list

return value - n/a
*/
template <typename type> 
LL<type>::~LL(){
    
    if(head == NULL && tail ==NULL){
        head = NULL;
        tail = NULL;
        delete head;
    }
    else{
        while(head != NULL && tail!=NULL){
            node * del;
            del = head;
            head = head -> next;
            del -> next = NULL;
            delete del;
        }
    }
}
/*
tailInsert(const type& item) - performs a tail insert, item will be contained in
the data field of the new tail node

return value - n/a
*/
template <typename type> 
void LL<type>::tailInsert(const type& item){

    node * ptr = NULL;
    ptr = new node;

    if(head == NULL && tail == NULL){
        head = ptr;
        tail = ptr;
        ptr -> data = item;
        head -> next = NULL;
        head -> prev = NULL;
    }

    else{
        ptr -> next = tail;
        ptr-> next = NULL;
        ptr-> prev = tail;
        ptr -> data = item;
        tail -> next = ptr;
        if(tail == NULL){
            head = ptr;
        }
        tail=ptr;
    }
   
}

/*
begin() const  - returns an iterator object whose cur-
rent is set to the head pointer

return value - head pointer
*/
template <typename type> 
typename LL<type>::iterator LL<type>::begin() const{

    return iterator(head);

}

/*
end() const  - returns an iterator object whose current
is set to the tail pointer

return value - tail pointer
*/
template <typename type> 
typename LL<type>::iterator LL<type>::end() const{

    return iterator(tail);

}

/*
swapNodes(iterator& it1, iterator& it2) - swaps the location of the nodes referenced by it1 and it2.
Handles edge cases for tail and head along with middle swaps 

return value - n/a
*/
template <typename type> 
void LL<type>::swapNodes(iterator&it1, iterator& it2){

    node *tmp, *tmp2;

    if(it1.current == NULL || it2.current == NULL){
        return;
    }

    if(this->head == it1.current){

        
        // head case
        tmp = it2.current->next;
        it2.current-> next = it1.current;
        it1.current -> next = tmp;
        tmp -> prev = it1.current; 
        it1.current -> prev = it2.current;
        it2.current -> prev = NULL;
        this->head = it2.current;
        it2.current = tmp -> prev;
        it1.current = head;
        return;
        
    }
    
    tmp = this->head;
    tmp2 = it2.current -> next;
    while(tmp -> next != it1.current){
        tmp = tmp ->next;
    } 
    // tail case
    if(tail == it2.current){
        
        it2.current -> next = it1.current;
        tmp -> next = it2.current;
        it2.current ->prev = tmp;
        it1.current ->prev = it2.current;
        this->tail = it1.current;
        it1.current = tmp -> next;
        it2.current = this->tail;
        this->tail -> next = NULL;
    
        return;
    }
    else{
        //moving tmp pointers into place tmp will be to the left of i1 anf tmp2 will be to the right of i2
        //middle case
        it2.current-> next = tmp -> next;
        it1.current->next = tmp2;
        tmp -> next = it2.current;
        tmp2->prev = it1.current;
        it2.current-> prev = tmp;
        it1.current -> prev = it2.current;
        it2.current = tmp2 ->prev;
        it1.current= tmp-> next;
  
       return;
    }  
}

/*
deleteLhs() - used in operator=(const LL<type> &rhs) to deallocate linked lists for 
deep copy.

return value - n/a
*/
template <typename type> 
void LL<type>:: deleteLhs(){

    if(head == NULL && tail ==NULL){
        head = NULL;
        tail = NULL;
        delete head;
    }
    else{
        while(head != NULL && tail!=NULL){
            node * del;
            del = head;
            head = head -> next;
            del -> next = NULL;
            delete del;
        }
    }
}