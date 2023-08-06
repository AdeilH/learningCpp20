#ifndef SOURCE_LOCATION_EXAMPLE_HPP
#define SOURCE_LOCATION_EXAMPLE_HPP

#include <format>
#include <source_location>
#include <string_view>
#include <iostream>

// Writing a print to screen function using format and source_location

void print(std::string_view message, const std::source_location& location = std::source_location::current())
{
    std::cout << std::format("{}:{}:{}: {}\n",
        location.file_name(),
        location.line(),
        location.column(),
        message);
}

#endif
