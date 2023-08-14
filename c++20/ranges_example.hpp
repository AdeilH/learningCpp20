#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>
#include "source_location_example.hpp"

// Ranges Combining Views Example

namespace v2 {
typedef std::string Symbol;
typedef uint64_t Price;
typedef uint64_t Id;
typedef uint64_t Size;

using symbolMap = std::unordered_map<std::string, std::vector<Data&>>;
using IdMap = std::unordered_map<Id, Data&>;





struct Data {
  Price m_price;
  Id m_id;  // Time of the order should be maintained against this Id outside of the order book
  Size m_size;
  Data(Price price, Id id, Size size)
      : m_price(price), m_id(id), m_size(size){};
  Data() : m_price(0), m_id(0), m_size(0){};

  friend std::ostream& operator<<(std::ostream& os, const Data& d) {
    return os << "Id: " << d.m_id << " Price: " << d.m_price
              << " Size: " << d.m_size;
  }
};

void sort_by_price(const Symbol symbol, symbolMap orderbook) {
  print("Sorting by Price:" + symbol + " ");
  std::ranges::sort(orderbook.at(symbol), [](Data data_a, Data data_b) {
    return data_a.m_price > data_b.m_price;
  });
}

void sort_by_size(const Symbol symbol, symbolMap orderbook) {
  print("Sorting by Size:" + symbol + " ");
  std::ranges::sort(orderbook.at(symbol), [](v2::Data data_a, v2::Data data_b) {
    return data_a.m_size > data_b.m_size;
  });
}
}  // namespace v2