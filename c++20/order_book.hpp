#include <unordered_map>
#include <vector>
#include "source_location_example.hpp"
#include <ranges>
#include <string>
#include <stdint.h>
#include <algorithm>

class OrderBook
{
    typedef std::string Symbol;
    typedef uint64_t Price;
    typedef uint64_t Id;
    typedef uint64_t Size;

    struct Data
    {
        Price m_price;
        Id m_id; // Time of the order should be maintained against this Id outside of the order book
        Size m_size;
        Data(Price price, Id id, Size size) : m_price(price), m_id(id), m_size(size){};

        friend std::ostream &operator<<(std::ostream &os, const Data &d)
        {
            return os << "Id: " << d.m_id << " Price: " << d.m_price << " Size: " << d.m_size;
        }
    };

    void sort_by_price(const Symbol symbol)
    {
        print("Sorting by Price:" + symbol + " ");
        std::ranges::sort(m_orderbook.at(symbol), [](Data data_a, Data data_b)
                          { return data_a.m_price > data_b.m_price; });
    }
    void sort_by_size(const Symbol symbol)
    {
        print("Sorting by Size:" + symbol + " ");
        std::ranges::sort(m_orderbook.at(symbol), [](Data data_a, Data data_b)
                          { return data_a.m_size > data_b.m_size; });
    }

    std::unordered_map<Symbol, std::vector<Data>> m_orderbook;

public:
    void insert_to_book(const Symbol& symbol, const Price price, const Id id, const Size size)
    {
        print("Inserting to Book: ");
        [[likely]] if (m_orderbook.contains(symbol))
        {
            print("Inserting to Book Already Existing Symbol: ");
            m_orderbook.at(symbol).emplace_back(Data(price, id, size));
            sort_by_price(symbol);
        }
        else
        {
            print("Inserting to Book First Time Symbol: ");
            const std::vector<Data> data = {Data(price, id, size)};
            m_orderbook.emplace(symbol, data);
        }
    }

    void print_book(const Symbol& symbol)
    {
        print("Printing Book for symbol: " + symbol);
        [[likely]] if (m_orderbook.contains(symbol))
        {
            for (auto const data : m_orderbook[symbol])
            {
                std::cout << data << std::endl;
            }
        }
        else
        {
            print("Book for symbol " + symbol + " doesn't exist.");
        }
    }
};