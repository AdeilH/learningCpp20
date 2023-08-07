#include "order_book.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Insertion into Order Book", "[get_orders_per_symbol]")
{
    OrderBook orderbook;
    REQUIRE(orderbook.get_orders_per_symbol("IBM.") == 0);
    orderbook.insert_to_book("IBM.", 100, 0, 200);
    REQUIRE(orderbook.get_orders_per_symbol("IBM.") == 1);
    orderbook.insert_to_book("IBM.", 100, 1, 200);
    orderbook.insert_to_book("IBM.", 100, 2, 200);
    REQUIRE(orderbook.get_orders_per_symbol("IBM.") == 3);
}