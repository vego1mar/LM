#include "rpn.hpp"
#include "../helpers/strings.hpp"
#include <algorithm>

using helpers::Strings;


namespace grammatical {

    void RPN::convert(const std::string &infix) {
        postfix.clear();

        if (infix.empty()) {
            return;
        }

        for (const auto &symbol : infix) {
            doInfixToPostfixStep(symbol);
        }

        doInfixToPostfixLastStep();
    }

    std::string RPN::getPostfix() const {
        auto str = Strings::trim(postfix);
        str = Strings::replace(str, "  ", " ");
        return str;
    }

    void RPN::doInfixToPostfixStep(const char &symbol) {
        if (std::isdigit(symbol)) {
            postfix += ' ';
            postfix += symbol;
            postfix += ' ';
            return;
        }

        if (isOperator(symbol)) {
            doInfixToPostfixOperatorStep(symbol);
            return;
        }

        if (symbol == '(') {
            stack.push(symbol);
            return;
        }

        if (symbol == ')') {
            doInfixToPostfixClosingParenthesisStep();
        }
    }

    std::list<char> RPN::getHigherPriorityOperators(const char &symbol) {
        if (symbol == '*' || symbol == '/') {
            return std::list<char>{'^'};
        }

        if (symbol == '+' || symbol == '-') {
            return std::list<char>{'^', '*', '/'};
        }

        return std::list<char>();
    }

    bool RPN::isOperator(const char &symbol) {
        return std::find(operators.begin(), operators.end(), symbol) != operators.end();
    }

    void RPN::doInfixToPostfixOperatorStep(const char &symbol) {
        const auto prioritizedOperators = getHigherPriorityOperators(symbol);

        while (!stack.empty()) {
            bool isOperatorOnTop = isOperator(stack.top());

            if (isOperatorOnTop) {
                postfix += ' ';
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
                continue;
            }

            break;
        }

        stack.push(symbol);
    }

    void RPN::doInfixToPostfixClosingParenthesisStep() {
        while (!stack.empty()) {
            if (stack.top() == '(') {
                break;
            }

            if (isOperator(stack.top())) {
                postfix += ' ';
                postfix += stack.top();
                postfix += ' ';
            }

            stack.pop();
        }

        stack.pop();
    }

    void RPN::doInfixToPostfixLastStep() {
        while (!stack.empty()) {
            if (isOperator(stack.top())) {
                postfix += ' ';
                postfix += stack.top();
                postfix += ' ';
            }

            stack.pop();
        }
    }

}
