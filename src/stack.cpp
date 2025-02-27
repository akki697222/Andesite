#include "stack.hpp"
#include "stdexcept"

std::deque<StackElement> Stack::getAll() const {
    return elements;
}

StackElement Stack::pop() {
    if (elements.empty()) throw std::underflow_error("Stack underflow.");
    StackElement before = elements.front();
    elements.pop_front();
    return before;
}

StackElement Stack::get() const {
    if (elements.empty()) throw std::underflow_error("Stack underflow.");
    return elements.front();
}

void Stack::remove() {
    if (!elements.empty()) elements.pop_front();
}

void Stack::push(const StackElement& element) {
    if (elements.size() > 65535) throw std::overflow_error("Stack overflow. (Max. 65535)");
    elements.push_front(element);
}

void Stack::swap() {
    if (elements.size() < 2) throw std::runtime_error("Not enough elements to swap.");
    StackElement one = pop();
    StackElement two = pop();
    push(one);
    push(two);
}