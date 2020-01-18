#include "rpn.hpp"
#include "../helpers/strings.hpp"
#include <algorithm>

using helpers::Strings;


namespace grammatical {

    void RPN::convert(const std::string &infix) {
        postfix.clear();
        stack = std::stack<char>();

        if (infix.empty()) {
            return;
        }

        for (const auto &symbol : infix) {
            performStep(symbol);
        }

        performLastStep();
    }

    std::string RPN::getPostfix() const {
        auto str = Strings::trim(postfix);
        str = Strings::replace(str, "  ", " ");
        return str;
    }

    void RPN::performStep(const char &symbol) {
        if (std::isdigit(symbol)) {
            postfix += ' ';
            postfix += symbol;
            postfix += ' ';
            return;
        }

        if (isOperator(symbol)) {
            performOperatorStep(symbol);
            return;
        }

        if (symbol == '(') {
            stack.push(symbol);
            return;
        }

        if (symbol == ')') {
            performClosingParenthesisStep();
        }
    }

    int RPN::getOperatorPrecedence(const char &symbol) {
        if (symbol == '^') {
            return 3;
        }

        if (symbol == '*' || symbol == '/') {
            return 2;
        }

        if (symbol == '+' || symbol == '-') {
            return 1;
        }

        return -1;
    }

    bool RPN::isOperator(const char &symbol) {
        return std::find(operators.begin(), operators.end(), symbol) != operators.end();
    }

    void RPN::performOperatorStep(const char &symbol) {
        while (!stack.empty()) {
            bool isOperatorOnTop = isOperator(stack.top());
            bool isHigherOrTheSamePrecedence = getOperatorPrecedence(stack.top()) >= getOperatorPrecedence(symbol);

            if (isOperatorOnTop && isHigherOrTheSamePrecedence) {
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

    void RPN::performClosingParenthesisStep() {
        while (!stack.empty()) {
            if (stack.top() == '(') {
                stack.pop();
                break;
            }

            if (isOperator(stack.top())) {
                postfix += ' ';
                postfix += stack.top();
                postfix += ' ';
            }

            stack.pop();
        }
    }

    void RPN::performLastStep() {
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
