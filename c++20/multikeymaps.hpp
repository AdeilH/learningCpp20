#ifndef MULTIKEYMAPS
#define MULTIKEYMAPS
#include <cstdint>
#include <iterator>
#include <variant>
#include <unordered_map>

template <typename Key1, typename Key2, typename Data>
class multikeyMaps {
  Key1 key1;
  Key2 key2;
  Data data;
  std::unordered_map<Key1, data> key1Map;
  std::unordered_map<Key2, data> key2Map; 

 public:
  void insert(Key1, Key2, Data);
  void remove(std::variant<decltype(Key1), decltype(Key2)> key);
  Data get(std::variant<decltype(Key1), decltype(Key2)> key);
  bool contains(std::variant<decltype(Key1), decltype(Key2)> key);
  size_t size();
};

#endif /*MultiKeyMaps*/
