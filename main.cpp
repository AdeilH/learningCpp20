#include <iostream>
#include "c++20/order_book.hpp"
#include "c++20/source_location_example.hpp"
#include "c++20/coroutine_example.hpp"
int main(int, char**) {
  OrderBook askbook;
  askbook.insert_to_book("IBM.", 200, 8, 100);
  askbook.insert_to_book("IBM.", 100, 9, 100);
  askbook.insert_to_book("IBM.", 500, 10, 100);
  askbook.insert_to_book("IBM.", 300, 11, 100);
  askbook.print_book("IBM.");
  askbook.removeOrder("IBM.", 9);
  askbook.print_book("IBM.");
  // this can be used to populate order book randomly with prices and incremental ids 
  // something needs to be sorted about the size
  example::get_price_vector(10, 1, 100);
}
