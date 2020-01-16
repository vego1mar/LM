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

        std::string convert(const std::string &infix);

        std::string getPostfix() const;


    private:
        void doInfixToPostfixStep(const char &symbol);

        static std::list<char> getHigherPriorityOperators(const char &symbol);

        bool isOperator(const char &symbol);

        void doInfixToPostfixOperatorStep(const char &symbol);

        void doInfixToPostfixClosingParenthesisStep();

        void doInfixToPostfixLastStep();

    };

}

#endif //RPN_HPP
