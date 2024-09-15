#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <format>

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
int main()
{
  auto triangle =  generate_triangle(16);
  show_vector(std::cout, triangle);
}