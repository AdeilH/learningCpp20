#ifndef COROUTINE_EXAMPLE_HPP
#define COROUTINE_EXAMPLE_HPP

#include <coroutine>
#include <random> 
#include <tl/generator.hpp>
#include "order_book.hpp"

namespace example {
    // populating with random prices for symbol within range 
    // this can then be used to add in order book

    // A function that returns a number between two numbers
    


    // this is a generator function
    tl::generator<uint64_t> range(uint64_t low, uint64_t high) {
        std::random_device rd;
        std::mt19937 gen(rd());
        // can use a different distribution
        std::uniform_int_distribution<> dis(low, high);
        while (true) {
            uint64_t i = dis(gen); // cannot bind error
            co_yield i;
        }
    }

    std::vector<uint64_t> get_price_vector(uint64_t num_of_orders, uint64_t low, uint64_t high){
        std::vector<uint64_t> prices;
        uint64_t count = 1;
        for (auto const &price : range(low, high)) {
            prices.push_back(price);
            std::cout << price << std::endl; 
            if(++count > num_of_orders) break;
        }
        return prices;
    }
    
}

#endif /* COROUTINE_EXAMPLE_HPP */
#