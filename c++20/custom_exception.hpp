#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP
#include <exception>
#include <string>    

class ExceptionMessage : public std::exception {
    private:
    std::string message;

    public:
    ExceptionMessage(std::string msg) : message(msg) {}
    std::string what () {
        return message;
    }
};

#endif /* CUSTOM_EXCEPTION_HPP */
