#ifndef SWINGTECH1_STLIST_H
#define SWINGTECH1_STLIST_H

#include "../../../Math/STCore.h"

template<typename T>
class STList{
public:
    struct Node{
        Node(T data){
            this->data = data;
        }
        T data;
        Node* next = nullptr;
    };

    /**
     *
     */
    class iterator : public std::iterator<std::output_iterator_tag, T>{
    public:
        explicit iterator(STList<T> &list, stUint startIndex): m_list(list) {
            m_index = startIndex;
        }

        bool operator!=(const iterator& rhs)const{
            return m_index != rhs.m_index;
        }

        T operator*()const{
            return m_list[m_index];
        }

        iterator & operator++(){
            m_index++;
            return *this;
        }
        iterator & operator++(int value){
            m_index += value;
            return *this;
        }
    private:
        stUint m_index;
        STList<T>& m_list;
    };

    /**
     * Constructor
     */
    STList(){
        head = NULL;
        tail = NULL;
        m_Size = 0;
    }

    /**
     * Checks if list is empty.
     * @return True if list is empty, otherwise false;
     */
    bool isEmpty()const{ return head != NULL; }

    /**
     * Adds to beginning of the list
     * @param data
     */
    void addFirst(T data){
        auto node = new Node(data);
        if(head == nullptr){
            head = tail = node;
            ++m_Size;
            return;
        }
        node->next = head;
        head = node;
        ++m_Size;
    }

    /**
     * Adds data to end of list.
     * @param data
     */
    void addLast(T data){
        auto node = new Node(data);
        if(head == nullptr){
            head = tail = node;
            ++m_Size;
            return;
        }
        tail->next = node;
        tail = node;
        ++m_Size;
    }

    /**
     * Clears the Linked List
     */
    void clear(){
        while(head != nullptr){
            removeLast();
            m_Size--;
        }
    }

    /**
     * Removes first node
     * @return Data from first Node.
     */
    T removeFirst(){
        if(head == nullptr)
            return  NULL;
        T data = head->data;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        m_Size--;
        return data;
    }

    /**
     * Removes last Node and returns data.
     * @return Data from last node.
     */
    T removeLast(){
        if(head == nullptr || tail == nullptr) return false;
        Node* cur = head;
        Node* prev = nullptr;
        while(cur->next != nullptr){
            prev = cur;
            cur = cur->next;
        }
        tail = prev;
        prev->next = nullptr;
        delete cur;
        m_Size--;
        return prev->data;
    }

    T operator[](stUint index){
        if(index < size()){
            Node* counter = head;
            stUint c = 0;
            while(c < index){
                counter = counter->next;
                c++;
            }
            return counter->data;
        }
        return NULL;
    }

    /**
     * Size of list
     * @return Size of list;
     */
    stUint size()const{ return m_Size; }

    /**
     * Start iterator
     * @return iterator starting point
     */
    iterator begin(){
        return iterator(*this, 0);
    }

    /**
     * End iterator
     * @return iterator ending point.
     */
    iterator end(){
        return iterator(*this, size());
    }

private:
    stUint m_Size{};
    Node* head = nullptr;
    Node* tail = nullptr;
};

#endif //SWINGTECH1_STLIST_H
