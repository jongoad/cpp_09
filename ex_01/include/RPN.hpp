#include <iostream>
#include <string>
#include <stack>
#include <ctype.h>
#include <stdlib.h>

class RPN {
    public:
        /* Constructors & Destructor*/
        RPN();
        RPN(const std::string& input);
        RPN(const RPN& other);
        ~RPN();

        const RPN& operator=(const RPN& rhs);


        /* Public Member Functions */
        bool parseInput(const std::string& input);
        void calculate(void);

    private:
        std::stack<int> reverse_;
        std::stack<int> operands_;
        std::stack<char> operators_;
};

/*
 

*/