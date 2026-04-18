// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int get_priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool is_opr(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack1;
    std::string result;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];

        if (c == ' ') {
            continue;
        }

        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack1.push(c);
        } else if (c == ')') {
            while (!stack1.is_empty() && stack1.top() != '(') {
                result += stack1.pop();
                result += ' ';
            }
            if (!stack1.is_empty() && stack1.top() == '(') {
                stack1.pop();
            }
        } else if (is_opr(c)) {
            while (!stack1.is_empty() && stack1.top() != '(' &&
                get_priority(stack1.top()) >= get_priority(c)) {
                result += stack1.pop();
                result += ' ';
            }
            stack1.push(c);
        }
    }
    while (!stack1.is_empty()) {
        result += stack1.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack2;

    for (size_t i = 0; i < post.length(); ++i) {
        if (post[i] == ' ') continue;

        if (isdigit(post[i])) {
            int number = 0;
            while (i < post.length() && isdigit(post[i])) {
                number = number * 10 + (post[i] - '0');
                ++i;
            }
            stack2.push(number);
            --i;
        } else if (is_opr(post[i])) {
            int b = stack2.pop();
            int a = stack2.pop();
            switch (post[i]) {
            case '+': stack2.push(a + b); break;
            case '-': stack2.push(a - b); break;
            case '*': stack2.push(a * b); break;
            case '/':
                if (b == 0) return 0;
                stack2.push(a / b);
                break;
            }
        }
    }
    return stack2.pop();
}
