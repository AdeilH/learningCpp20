#include <iostream>
#include "c++20/source_location_example.hpp"
#include "c++20/order_book.hpp"

int main(int, char**){
    std::cout << "Hello, from DSMPP!\n";
    OrderBook askbook; 
    askbook.insert_to_book("IBM.", 200, 10, 100);
    askbook.insert_to_book("IBM.", 200, 11, 100);
    askbook.print_book("IBM.");
    print("Hello");
}
