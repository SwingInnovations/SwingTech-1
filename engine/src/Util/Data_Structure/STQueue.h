#ifndef SWINGTECH1_STQUEUE_H
#define SWINGTECH1_STQUEUE_H

#include "../../Math/STCore.h"
#include "STList.h"

template<typename T>
class STQueue{
public:
    void push(T data){
        list.addFirst(data);
    }

    T pop(){
        return list.removeFirst();
    }

    typename STList<T>::iterator begin(){ return list.begin(); }
    typename STList<T>::iterator end(){ return list.end(); }

    void  clear(){ list.clear(); }
    stUint size()const{ return list.size(); }
protected:
    STList<T> list;
};

#endif //SWINGTECH1_STQUEUE_H
