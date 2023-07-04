#include "../include/RPN.hpp"

#define VALID_CHARS " 0123456789-+*/"
#define OPERATORS "+-*/"

/* Constructors & Destructor */
RPN::RPN() {
};

RPN::RPN(const std::string& input) {
    if (!parseInput(input)) {
        std::cerr << "Error" << std::endl;
        return;
    }
    calculate();
};

RPN::RPN(const RPN& other) {
    *this = other;
};

RPN::~RPN() {

};

const RPN& RPN::operator=(const RPN& rhs) {
    operands_ = rhs.operands_;
    operators_ = rhs.operators_;
    return *this;
};

/* Public Member Functions */

bool RPN::parseInput(const std::string& input) {
    //Check for invalid chars
    if (input.find_first_not_of(VALID_CHARS) != std::string::npos) {
        std::cerr << "Invalid characters" << std::endl;
        return false;
    }

    size_t len = input.size();
    size_t i = 0;
    int res;
    for (; i < len; i++) {
        res = 0;
        //Skip whitespace
        if (input[i] == ' ') {
            continue;
        }
        //Add negative number
        else if (input[i] == '-' && i + 1 < len && isdigit(input[i + 1])) {
            i++;
            while (i < len && isdigit(input[i])) {
                res = (res * 10) + (input[i] - '0');
                i++;
            }
            if (res > 9) {
                std::cerr << "Value less than -9" << std::endl;
                return false;
            }
            operands_.push(-res);
        }
        //Add positive number
        else if (isdigit(input[i])) {
            while (i < len && isdigit(input[i])) {
                res = (res * 10) + (input[i] - '0');
                i++;
            }
            if (res > 9) {
                std::cerr << "Value greater than 9" << std::endl;
                return false;
            }
            operands_.push(res);
        }
        //Add operator
        else if (input[i] == '-' || input[i] == '+' || input[i] == '*' || input[i] == '/'){
            if (i + 1 < len && input[i + 1] != ' ') {
                std::cerr << "Operator error" << std::endl;
                return false;
            }
            operators_.push(input[i]);
        }
    }
    return true;
};

void RPN::calculate(void) {
    int a, b;
    int res;
    char op;
    while (!operators_.empty()) {
        //Pull top two values from operands stack
        b = operands_.top();
        operands_.pop();
        a = operands_.top();
        operands_.pop();

        //Pull top operator from operators stack
        op = operators_.top();
        operators_.pop();

        switch (op) {
        case '-':
            res = a - b;
            break;
        case '+':
            res = a + b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
        default:
            break;
        }

        //Push result back onto operands stack
        operands_.push(res);
    }
    std::cout << operands_.top() << std::endl;
};

