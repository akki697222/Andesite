#pragma once

#include <cstdint>
#include <variant>
#include <deque>
#include <unordered_map>
#include <string>

using StackElement = std::variant<
    uint64_t, int64_t, double, std::string,
    uint64_t*, int64_t*, double*, std::string*
>;

static const StackElement STACK_ELEMENT_ZERO = 0;

class Stack {
    public:
        Stack() {};
    
        std::deque<StackElement> getAll() const;
        StackElement pop();
        StackElement get() const;
        void remove();
        void push(const StackElement& element);
        void swap();
    private:
        std::deque<StackElement> elements;
        uint32_t maxsize;
};