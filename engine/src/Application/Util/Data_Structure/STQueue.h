#ifndef SWINGTECH1_STQUEUE_H
#define SWINGTECH1_STQUEUE_H

#include "../../../Math/STCore.h"
#include "STList.h"

template<typename T>
/**
 * Standard Queue Data class
 * @tparam T Data Type
 */
class STQueue{
public:
    /**
     * Adds data to front
     * @param data
     */
    void push(T data){
        list.addFirst(data);
    }

    /**
     * Removes data from the Front
     * @return
     */
    T pop(){
        return list.removeFirst();
    }

    typename STList<T>::iterator begin(){ return list.begin(); }
    typename STList<T>::iterator end(){ return list.end(); }

    /**
     * Clears Queue
     */
    void  clear(){ list.clear(); }
    /**
     *
     * @return
     */
    stUint size()const{ return list.size(); }

    /**
     *
     * @return
     */
    bool isEmpty()const{ return list.isEmpty(); }
protected:
    STList<T> list;
};

#endif //SWINGTECH1_STQUEUE_H
