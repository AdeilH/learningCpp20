#include <stdint.h>
#include <algorithm>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "source_location_example.hpp"

typedef std::string Symbol;
typedef uint64_t Price;
typedef uint64_t Id;
typedef uint64_t Size;

class OrderBook {

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

  void sort_by_price(const Symbol symbol) {
    print("Sorting by Price:" + symbol + " ");
    std::ranges::sort(m_orderbook.at(symbol), [](Data data_a, Data data_b) {
      return data_a.m_price > data_b.m_price;
    });
  }

  void sort_by_size(const Symbol symbol) {
    print("Sorting by Size:" + symbol + " ");
    std::ranges::sort(m_orderbook.at(symbol), [](Data data_a, Data data_b) {
      return data_a.m_size > data_b.m_size;
    });
  }
  void sort_by_id(const Symbol symbol) {
    print("Sorting by Size:" + symbol + " ");
    std::ranges::sort(m_orderbook.at(symbol), [](Data data_a, Data data_b) {
      return data_a.m_id < data_b.m_id;
    });
  }

  [[nodiscard("Use Id")]] std::pair<bool, Id> search_by_id(const Symbol symbol,
                                                           const Id id) {
    print("Searchig id of: " + symbol + " id: " + std::to_string(id));
    sort_by_id(symbol);
    auto position = std::lower_bound(
        m_orderbook.at(symbol).begin(), m_orderbook.at(symbol).end(), id,
        [](const Data& data, Id id) { 
          std::cout << data << "  Id: " << id << std::endl; 
          return data.m_id < id; });
    if (position != m_orderbook.at(symbol).end()) {
      return std::make_pair<bool, Id>(
          true, position - m_orderbook.at(symbol).begin());
    }
    return std::make_pair<bool, Id>(false, 0u);
  }

  std::unordered_map<Symbol, std::vector<Data>> m_orderbook;

 public:
  void insert_to_book(const Symbol& symbol, const Price price, const Id id,
                      const Size size) {
    print("Inserting to Book: ");
    [[likely]] if (m_orderbook.contains(symbol)) {
      print("Inserting to Book Already Existing Symbol: ");
      m_orderbook.at(symbol).emplace_back(Data(price, id, size));
      sort_by_price(symbol);
    } else {
      print("Inserting to Book First Time Symbol: ");
      const std::vector<Data> data = {Data(price, id, size)};
      m_orderbook.emplace(symbol, data);
    }
  }

  [[nodiscard("Use the size returned Please")]] uint64_t get_orders_per_symbol(
      const Symbol& symbol) {
    [[likely]] if (m_orderbook.contains(symbol)) {
      return m_orderbook.at(symbol).size();
    }
    return 0;
  }

  void print_book(const Symbol& symbol) {
    print("Printing Book for symbol: " + symbol);
    [[likely]] if (m_orderbook.contains(symbol)) {
      for (auto const data : m_orderbook[symbol]) {
        std::cout << data << std::endl;
      }
    } else {
      print("Book for symbol " + symbol + " doesn't exist.");
    }
  }

  [[nodiscard("Returns Top Ask Please Use")]] Data getTopAsk(
      const Symbol& symbol) {
    [[likely]] if (m_orderbook.contains(symbol)) {
      return m_orderbook.at(symbol).at(m_orderbook.at(symbol).size() - 1);
    }
    return Data();
  }

  [[nodiscard("Returns Top Bid Please Use")]] Data getTopBid(
      const Symbol& symbol) {
    [[likely]] if (m_orderbook.contains(symbol)) {
      return m_orderbook.at(symbol).at(0);
    }
    return Data();
  }

  void removeOrder(const Symbol symbol, const Id id) {
    [[likely]] if (m_orderbook.contains(symbol)) {
      auto z = search_by_id(symbol, id);
      if (z.first) {
        m_orderbook.at(symbol).erase(m_orderbook.at(symbol).begin() + z.second);
      } else {
        std::cout << "Doesn't Exist." << std::endl;
      }
    }
    sort_by_price(symbol);
  }
};