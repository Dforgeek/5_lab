#include <iostream>
#include "mallocator.h"
#include <vector>
#include <queue>
#include <list>
#include <map>

int main() {
    std::vector<long long, Mollocator<long long, 20000>> v(5);

    for (int i = 0; i < 2000; ++i) {
        v.push_back(i);
    }

    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << '\n';
    }

/*    std::map<int, int, std::less<>, Mollocator<int, 100>> l;

    for (int i=0; i<50; ++i){
        l.insert({i, i+5});
    }
    for (int i=0; i<50; ++i){
        std::cout<<l[i]<<'\n';
    }*/

    return 0;
}