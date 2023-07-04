#include "../include/RPN.hpp"

#define VALID_CHARS " 0123456789-+*/"

/* Constructors & Destructor */
RPN::RPN() {
};

RPN::RPN(const std::string& input) {
    //Check for invalid chars
    if (input.find_first_not_of(VALID_CHARS) != std::string::npos) {
        std::cerr << "Error" << std::endl;
        return;
    }

    //Parse and solve at the same time using a stack
    for (std::string::const_iterator it = input.begin(); it != input.end(); ++it) {
        if (*it == ' ') {
            continue;
        } else if ( *it == '-' || *it == '+' || *it == '*' || *it == '/') {
            if (operands_.size() < 2) {
                std::cerr << "Error" << std::endl;
            }
            int a = operands_.top();
            operands_.pop();
            int b = operands_.top();
            operands_.pop();

            switch (*it) {
            case '-':
                operands_.push(a - b);
                break;
            case '+':
                operands_.push(a + b);
                break;
            case '*':
                operands_.push(a * b);
                break;
            case '/':
                operands_.push(a / b);
                break;
            default:
                break;
            }
        } else {
            operands_.push(*it - '0');
        }
    }
    std::cout << operands_.top() << std::endl;
};

RPN::RPN(const RPN& other) {
    *this = other;
};

RPN::~RPN() {
};

const RPN& RPN::operator=(const RPN& rhs) {
    operands_ = rhs.operands_;
    return *this;
};