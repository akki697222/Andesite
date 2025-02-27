#include "opcodes.hpp"
#include "vm.hpp"
#include "stack.hpp"
#include "iostream"
#include "vector"
#include "cstdint"

#define ANDESITE_VM_DEBUG

template <typename T>
T getValue(const StackElement &stackElement)
{
    return std::get<T>(stackElement);
}

template <typename T>
class BinaryOperator
{
public:
    static T add(StackElement &a, StackElement &b)
    {
        T b_ = getValue<T>(b);
        T a_ = getValue<T>(a);
        return a_ + b_;
    }
    static T add(StackElement &&a, StackElement &&b)
    {
        return add(a, b);
    }
    static T sub(StackElement &a, StackElement &b)
    {
        T b_ = getValue<T>(b);
        T a_ = getValue<T>(a);
        return a_ - b_;
    }
    static T sub(StackElement &&a, StackElement &&b)
    {
        return sub(a, b);
    }
    static T mul(StackElement &a, StackElement &b)
    {
        T b_ = getValue<T>(b);
        T a_ = getValue<T>(a);
        return a_ * b_;
    }
    static T mul(StackElement &&a, StackElement &&b)
    {
        return mul(a, b);
    }
    static T div(StackElement &a, StackElement &b)
    {
        T b_ = getValue<T>(b);
        T a_ = getValue<T>(a);
        return a_ / b_;
    }
    static T div(StackElement &&a, StackElement &&b)
    {
        return div(a, b);
    }
    static T mod(StackElement &a, StackElement &b)
    {
        T b_ = getValue<T>(b);
        T a_ = getValue<T>(a);
        return a_ % b_;
    }
    static T mod(StackElement &&a, StackElement &&b)
    {
        return mod(a, b);
    }
};

VM_Info VM::step()
{
    state = VM_State::RUNNING;
    Instruction operation = instructions[pc];

    if (pc > instructions.size())
    {
        state = VM_State::EXITED;
    }
    else
    {
        switch (operation.op)
        {
        case Opcode::ipush:
        {
            stack.push(std::get<int64_t>(operation.value));
            break;
        }
        case Opcode::upush:
        {
            stack.push(std::get<uint64_t>(operation.value));
            break;
        }
        case Opcode::fpush:
        {
            stack.push(std::get<double>(operation.value));
            break;
        }
        case Opcode::iadd:
        {
            stack.push(BinaryOperator<int64_t>::add(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::isub:
        {
            stack.push(BinaryOperator<int64_t>::sub(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::imul:
        {
            stack.push(BinaryOperator<int64_t>::mul(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::idiv:
        {
            stack.push(BinaryOperator<int64_t>::div(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::imod:
        {
            stack.push(BinaryOperator<int64_t>::mod(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::uadd:
        {
            stack.push(BinaryOperator<uint64_t>::add(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::usub:
        {
            stack.push(BinaryOperator<uint64_t>::sub(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::umul:
        {
            stack.push(BinaryOperator<uint64_t>::mul(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::udiv:
        {
            stack.push(BinaryOperator<uint64_t>::div(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::umod:
        {
            stack.push(BinaryOperator<uint64_t>::mod(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::fadd:
        {
            stack.push(BinaryOperator<double>::add(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::fsub:
        {
            stack.push(BinaryOperator<double>::sub(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::fmul:
        {
            stack.push(BinaryOperator<double>::mul(stack.pop(), stack.pop()));
            break;
        }
        case Opcode::fdiv:
        {
            stack.push(BinaryOperator<double>::div(stack.pop(), stack.pop()));
            break;
        }
        }
        pc++;

        state = VM_State::STANDBY;
    }

    return VM_Info(
        pc,
        state,
        operation,
        stack,
        this->getMemoryUsage(),
        0);
}

void VM::suspend() {
    state = VM_State::SUSPENDED;
#ifdef ANDESITE_VM_DEBUG
    printStatus();
#endif
}

void VM::resume() {
    state == VM_State::STANDBY;
#ifdef ANDESITE_VM_DEBUG
    std::cout << "VM Resumed." << std::endl;
#endif
}

void VM::printStatus() {
    std::deque<StackElement> e = stack.getAll();
    std::cout << "Current Stack:" << std::endl;
    for (size_t i = 0; i < e.size(); i++)
    {
        std::cout << "stack#" << i << ": ";

        std::visit([](auto &&val)
                   {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_pointer_v<T>) {
                std::cout << static_cast<void*>(val);
            } else {
                std::cout << val;
            } }, e[i]);

        std::cout << std::endl;
    }
}

int VM::execute()
{
    state = VM_State::STANDBY;

    while (state != VM_State::ERROR && state != VM_State::EXITED)
    {
        if (state == VM_State::STANDBY) {
            VM_Info info = step();
        }
    }

#ifdef ANDESITE_VM_DEBUG
    std::cout << "Execution Ended." << std::endl;
    printStatus();
#endif

    return 0;
}