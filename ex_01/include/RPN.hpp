#include <iostream>
#include <string>
#include <stack>

class RPN {
    public:
        /* Constructors & Destructor*/
        RPN();
        RPN(const std::string& input);
        RPN(const RPN& other);
        ~RPN();
        const RPN& operator=(const RPN& rhs);

    private:
        std::stack<int> operands_;
};