#include <format>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <random>
#include <sstream>
#include <cassert> 
unsigned some_const_number() {
  return 42;
}


constexpr bool is_prime(int n) {
    if (n == 2 || n ==3){
        return true;
    }
    if (n <=1 || n%2 == 0|| n % 3 == 0){
        return false;
    }
    for (int i = 5; i*i <= n; ++i){
        if (n%i == 0){
            return false;
        }
    }
    return true;
}

void check_is_prime(){
    static_assert(is_prime(2));
    static_assert(!is_prime(4));
    static_assert(is_prime(7));
}
unsigned non_const_number() {
  std::uniform_int_distribution<int> dist(1, 99999);
  std::random_device rd;
  std::mt19937_64 engine(rd());
  int n{};
  while(!is_prime(n)){
    n = dist(engine);
  }
  return n;
}

std::string check_which_digits_correct(int number, int guess){
    auto ns = std::format("{:0>5}", (number));
    auto gs = std::format("{:0>5}", (guess));
    std::string matches(5, '.');

    for(size_t i = 0, stop = gs.length(); i < stop; ++i){
        char guess_char = gs[i];
        if (i < ns.length() && guess_char == ns[i]){
            matches[i] = '*';
            ns[i] = '*';
        }
    }

    for(size_t i = 0, stop = gs.length(); i < stop; ++i){
        char guess_char = gs[i];
        if (i < ns.length() && matches[i] != '*'){
            if (size_t idx = ns.find(guess_char, 0);
            idx != std::string::npos){
                matches[i] = '^';
                ns[idx] = '^';
            }
        }
    }

    return matches;

}

auto check_correct(){
    assert(check_which_digits_correct(12345, 54132) == "^^^^^");
}

// input stream can have problems have to be careful
unsigned input() {
  unsigned number;
  while (!(std::cin >> number)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a number.\n";
  }
  return number;
}

std::optional<int> read_number_2(std::istream& in) {
  int result{};
  if (in >> result) {
    return result;
  }
  in.clear();
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return {};
}

void guess_number_or_give_up(int number, auto message) {
  std::cout << "Guess the number \n";
  std::optional<int> guess;
  while (guess = read_number_2(std::cin)) {
    if (guess.value() == number) {
      std::cout << "Well Done. ";
      return;
    }
    std::cout << message(number, guess.value());
    std::cout << "\n";
  }
  std::cout << std::format("The number was {} \n", number);
}

void guess_number(unsigned number) {
  std::cout << "Guess the Number\n";
  unsigned guess = input();
  while (guess != number) {
    std::cout << guess << " is wrong. Try again \n";
    guess = input();
  }
  std::cout << "Well done. \n";
}

int main() {
    check_correct();
  // guess_number(some_const_number());
  auto func = [](int number, int guess) -> std::string {
    // return number > guess ? "Number is greater than guess" : "Number is less than guess"
    return std::format("Your guess was too {}",
                       (guess > number ? "big" : "small"));
  };

  auto func_prime = [](int number, int guess) -> std::string {
    return std::format("{}", check_which_digits_correct(number, guess));
  };
  guess_number_or_give_up(non_const_number(), func_prime);
}