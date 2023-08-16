cmake_minimum_required(VERSION 3.0.0)
project(DSMPP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(EXAMPLES main.cpp "c++20/source_location_example.hpp" "c++20/ranges_example.hpp")
target_include_directories(EXAMPLES PRIVATE ${CMAKE_SOURCE_DIR}/submodules/tlgenerator/include())


add_executable(order_book_tests "tests/order_book_tests.cpp")
target_link_libraries(order_book_tests PUBLIC Catch2::Catch2 Catch2::Catch2WithMain)
target_include_directories(order_book_tests PRIVATE "c++20")


include(CTest)
include(Catch)
catch_discover_tests(order_book_tests)
