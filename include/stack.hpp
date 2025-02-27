#include <cstdint>
#include <variant>
#include <deque>

#ifndef ANDESITE_STACK
#define ANDESITE_STACK

using StackElement = std::variant<
    uint64_t, int64_t, double,
    uint64_t*, int64_t*, double*
>;

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
};

#endif