#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <format>
#include <cassert>
#include <numeric>
#include <ranges>

std::vector<int> get_next_row(const std::vector<int> &last_row){
    std::vector next_row{1};
    if (last_row.empty()){
        return next_row;
    }
    for (size_t idx=0; idx+1 < last_row.size(); idx++){
        next_row.emplace_back(last_row[idx] + last_row[idx+1]);
    }
    next_row.emplace_back(1);
    return next_row;
}

auto generate_triangle(int rows) -> std::vector<std::vector<int>>{
    std::vector<int> data;
    std::vector<std::vector<int>> triangle;
    for (int row = 0; row < rows; row++){
        data = get_next_row(data);
        triangle.push_back(data);
    }
    return triangle;
}

// Perfect forwarding is basically calling an overload with rvalue

auto generate_triangle_perfect_forwarding(int rows) -> std::vector<std::vector<int>>{
    std::vector<std::vector<int>> triangle {{1}};
    for (int row = 0; row < rows; row++){
        triangle.push_back(get_next_row(triangle.back()));
    }
    return triangle;
}

template<typename T>
std::ostream& operator <<(std::ostream &s, const std::vector<std::vector<T>> &triangle){
    for (const auto& row: triangle){
        std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
        s << '\n';
    }
    return s; 
}

void show_vector(std::ostream &s, const std::vector<std::vector<int>> &triangle){
    size_t final_row_size = triangle.back().size();
    std::string spaces(final_row_size * 3, ' ');
    for (const auto &row: triangle){
        s << spaces;
        if (spaces.size() > 3){
            spaces.resize(spaces.size() - 3);
        }
        for (const auto &data: row){
            s << std::format("{: ^{}}", data, 6);
        }
        s << '\n';
    }
}

bool is_palindrome(const std::vector<int> &v){
    auto forward = v | std::ranges::views::take(v.size()/2);
    auto backward = v | std::ranges::views::reverse | std::ranges::views::take(v.size()/ 2);
    return std::ranges::equal(forward, backward);
}

// Check Properties assertions testin

void check_properties(const std::vector<std::vector<int>>& triangle){
    size_t row_number = 1;
    int expected_sum = 1;   
    for (auto const & row : triangle){
        assert(row.front() == 1 && row.back() == 1);
        assert(row.size() == row_number++);
        assert(std::accumulate(row.begin(), row.end(), 0) == expected_sum);
        expected_sum *= 2; 
        assert(std::ranges::all_of(row, [](auto x){return x >= 0;}));
        assert(is_palindrome(row));
    }
}

void difference_between_remove_if_views_do_while(){
    auto vec = std::vector<int>{0, 1, 2, 3, 4, 5};
    auto less_than_three = [](auto x){return x < 3;};
    auto new_end = std::remove_if(vec.begin(), vec.end(), less_than_three);
    std::cout << '\n';
    for (int n: vec){
        std::cout << n << ' ';
    }
    std::cout << '\n';

    for (auto it = vec.begin(); it != vec.end(); it++){
        std::cout << *it << ' ';
    }
    
    std::cout << '\n';
    auto vec2 = std::vector<int>{0, 1, 2, 3, 4, 5};
    for (int n: vec2 | std::ranges::views::drop_while(less_than_three)){
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
auto print_sierpinski_triangle(std::ostream &s, std::vector<std::vector<int>>& triangle){
    std::string spaces(triangle.back().size() , ' ');
    for (const auto &row: triangle){
        s << spaces;
        if (spaces.size()){
            spaces.resize(spaces.size() - 1);
        }
        auto odds = row | std::views::transform([](int x){ return x %2 ? '*':' ';});
        for (const auto &data: odds){
            s << data << ' ';
        }
        s << '\n';
    }
}

int main()
{
  auto triangle =  generate_triangle(16);
  show_vector(std::cout, triangle);
  check_properties(triangle);
  difference_between_remove_if_views_do_while();
    auto triangle2 =  generate_triangle(5);
  print_sierpinski_triangle(std::cout, triangle2);
}