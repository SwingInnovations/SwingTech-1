#ifndef SWINGTECH1_STLIST_H
#define SWINGTECH1_STLIST_H

#include <memory>

#include "../../../Math/STCore.h"

template<typename T>
class STList{
public:
    /**
     * Internal Class.
     */
    struct Node {
        Node() {

        }

        explicit Node(T data) {
            this->data = data;
        }

        T data;
        std::shared_ptr<Node> Next;
    };


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
        m_Size = 0;
    }

    /**
     * Checks if list is empty.
     * @return True if list is empty, otherwise false;
     */
    bool isEmpty()const{ return Head.get() == nullptr; }

    /**
     * Adds to beginning of the list
     * @param data
     */
    void addFirst(T data){
        auto node = std::make_shared<Node>(data);
        if(Head.get() == nullptr){
            Head = Tail = node;
            ++m_Size;
            return;
        }
        node->Next = Head;
        Head = node;
        m_Size++;
    }

    /**
     * Adds data to end of list.
     * @param data
     */
    void addLast(T data){
        auto node = std::make_shared<Node>(data);
        if(Head == nullptr){
            Head = Tail = node;
            ++m_Size;
            return;
        }
        Tail->Next = node;
        Tail = node;
        ++m_Size;
    }

    /**
     * Clears the Linked List
     */
    void clear(){
        m_Size = 0;
        while(Head.get() != nullptr){
            removeLast();
        }
    }

    /**
     * Removes first node
     * @return Data from first Node.
     */
    T removeFirst(){
        if(Head.get() == nullptr) return nullptr;
        T data = Head->data;
        auto tmp = Head;
        Head = Head->Next;
        delete tmp;
        m_Size--;
        return data;
    }

    /**
     * Removes last Node and returns data.
     * @return Data from last node.
     */
    T removeLast(){
        if(Head.get() == nullptr || Tail.get() == nullptr) return nullptr;
        auto cur = Head;
        std::shared_ptr<Node> prev;
        while(cur->Next.get() != nullptr){
            prev = cur;
            cur = cur->Next;
        }
        Tail = prev;
        prev->Next.reset();
        m_Size--;
        return prev->data;
    }

    T operator[](stUint index){
        if(index < size()){
            auto counter = Head;
            stUint c = 0;
            while(c < index){
                counter = counter->Next;
                c++;
            }
            return counter->data;
        }
        return nullptr;
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
    stUint m_Size;
    std::shared_ptr<Node> Head;
    std::shared_ptr<Node> Tail;
};

#endif //SWINGTECH1_STLIST_H
