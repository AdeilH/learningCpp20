#ifndef ORDER_BOOKV2
#define ORDER_BOOKV2

#include "ranges_example.hpp"

namespace v2 {

class order_book {

  class container {
    symbolMap m_symbolMap;
    IdMap m_idMap;

   public:
    bool insert_to_map(const Symbol symbol, Data data) {
      print("Inserting to Book: ");
      [[likely]] if (m_symbolMap.contains(symbol)) {
        print("Inserting to Book Already Existing Symbol: ");
        m_symbolMap.at(symbol).emplace_back(data);
        v2::sort_by_price(symbol, m_symbolMap);
        return true;
      } else {
        print("Inserting to Book First Time Symbol: ");
        auto insert1 = m_symbolMap.emplace(symbol, data);
        auto insert2 = m_idMap.emplace(data.m_id, data);
        return insert1 && insert2; 
      }
      return false;
    }
  };
};
}  // namespace v2

#endif /* ORDER_BOOKV2 */
