#include <iostream>

#include "../src/Util/Data_Structure/STList.h"
#include "../src/Util/Data_Structure/STQueue.h"

int main(int argc, char** argv){
    STQueue<int> queue;
    for(stUint i = 0; i < 4; i++){
        queue.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }

    for(auto i : queue){
        std::cout << "Popped: " << i << std::endl;
    }

}