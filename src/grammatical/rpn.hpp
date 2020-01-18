#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <list>

namespace grammatical {

    /// Reverse Polish Notation
    class RPN {
    private:
        const std::list<char> operators = {'^', '*', '/', '+', '-'};
        std::string postfix;
        std::stack<char> stack;

    public:
        RPN() = default;

        RPN(const RPN &rhs) = delete;

        RPN(RPN &&rvalue) noexcept = delete;

        RPN &operator=(const RPN &rhs) = delete;

        RPN &operator=(RPN &&rvalue) noexcept = delete;

        virtual ~RPN() = default;

        void convert(const std::string &infix);

        std::string getPostfix() const;


    private:
        void performStep(const char &symbol);

        static int getOperatorPrecedence(const char &symbol);

        bool isOperator(const char &symbol);

        void performOperatorStep(const char &symbol);

        void performClosingParenthesisStep();

        void performLastStep();

    };

}

#endif //RPN_HPP
