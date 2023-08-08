#include <iostream>
#include "c++20/source_location_example.hpp"
#include "c++20/order_book.hpp"

int main(int, char**){
    OrderBook askbook; 
    askbook.insert_to_book("IBM.", 200, 10, 100);
    askbook.insert_to_book("IBM.", 100, 10, 100);
    askbook.insert_to_book("IBM.", 500, 10, 100);
    askbook.insert_to_book("IBM.", 300, 11, 100);
    askbook.print_book("IBM.");
}
