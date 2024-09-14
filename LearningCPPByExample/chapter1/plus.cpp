#include <iostream>
#include <functional>
template <typename T,typename U>
auto simple_plus(const T lhs,const U rhs) -> decltype(lhs + rhs){
    return lhs + rhs; 
}

auto main() -> int {
    std::cout << std::plus<int>{}(1, 1.23) << std::endl;
    std::cout << std::plus<>{}(1, 1.23) << std::endl;
    return 0;
}