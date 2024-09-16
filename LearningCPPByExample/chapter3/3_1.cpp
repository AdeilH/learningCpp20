#include <iostream>
#include <limits>
#include <sstream>
#include <optional>
#include <functional>
#include <format>

unsigned some_const_number(){
    return 42;
}

// input stream can have problems have to be careful
unsigned input(){
    unsigned number;
    while (!(std::cin >> number)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number.\n";
    }
    return number;
}

std::optional<int> read_number_2(std::istream &in){
    int result{};
    if (in >> result){
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return {};
}

void guess_number_or_give_up(int number, std::function<std::string(int, int)> message){
    std::cout << "Guess the number \n";
    std::optional<int> guess;
    while(guess = read_number_2(std::cin)){
        if (guess.value() == number){
            std::cout << "Well Done. ";
            return;
        }
        std::cout << message(number, guess.value());
        std::cout << "\n";
    }
    std::cout << std::format("The number was {} \n", number);
}

void guess_number(unsigned number){
    std::cout << "Guess the Number\n";
    unsigned guess = input();
    while (guess != number){
        std::cout << guess << " is wrong. Try again \n";
        guess = input();
    }
    std::cout << "Well done. \n";
}

int main(){
    // guess_number(some_const_number());
    auto func = [] (int number, int guess) -> std::string{
        // return number > guess ? "Number is greater than guess" : "Number is less than guess" 
        return std::format("Your guess was too {} \n", (guess > number ? "big": "small"));
    
    }; 
    guess_number_or_give_up(some_const_number(), func);
}