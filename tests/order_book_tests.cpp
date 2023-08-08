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

TEST_CASE("Insertion into Order Book", "[TopAsk]")
{
    OrderBook orderbook;
    orderbook.insert_to_book("IBM.", 100, 0, 200);
    orderbook.insert_to_book("IBM.", 200, 1, 200);
    orderbook.insert_to_book("IBM.", 300, 2, 200);
    auto z = orderbook.getTopAsk("IBM.");
    orderbook.print_book("IBM.");
    REQUIRE(z.m_size == 200);
    REQUIRE(z.m_price == 100);
    REQUIRE(z.m_id == 0);
}


TEST_CASE("Insertion into Order Book", "[TopBid]")
{
    OrderBook orderbook;
    orderbook.insert_to_book("IBM.", 100, 0, 200);
    orderbook.insert_to_book("IBM.", 200, 1, 200);
    orderbook.insert_to_book("IBM.", 300, 2, 200);
    auto z = orderbook.getTopBid("IBM.");
    REQUIRE(z.m_size == 200);
    REQUIRE(z.m_price == 300);
    REQUIRE(z.m_id == 2);
}