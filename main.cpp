#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <list>

#include "MyAllocator.h"
#include "MyContainer.h"

template<typename Key, typename Value, typename Comp, typename Alloc>
std::ostream& operator<<(std::ostream& os, std::map<Key, Value, Comp, Alloc> const& m)
{
   os << "{ ";
   for(auto const& p: m)
        os << "(" << p.first << ": " << p.second << ") ";
   return os << "}\n";
}

int main(int, char**) {
    std::map<int, int> plain_map;
    int prev_factorial = 1;
    for (int i=1; i<10; i++)
    {
        prev_factorial *= i;
        plain_map.emplace(i, prev_factorial);

    }
    //std::cout << plain_map;
/*
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> custom_map;
    prev_factorial = 1;
    for (int i=1; i<4; i++)
    {
        prev_factorial *= i;
        custom_map.emplace(i, prev_factorial);
    }
    std::cout << custom_map;
*/
    //MyContainer<int> tmp;
    MyContainer<int, MyAllocator<int, 10>> tmp;
    for (int i=0; i<10; i++) {
        tmp.push_back(i);
    }
    print(tmp);
    return 0;
}