#include <iostream>
#include "mallocator.h"
#include <vector>

int main(){
    std::vector<long long, Mollocator<long long,200>> v;

    for (int i=0; i<100; ++i){
        v.push_back(i);
    }

    for (long long i : v){
        std::cout << i<<'\n';
    }
    return 0;
}