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

std::string getTypeName(const std::type_info& type, bool useNativeName) {
    std::unordered_map<std::string, std::string> se;

    if (useNativeName) {
        se = {
            {typeid(uint64_t).name(), "uint64_t"},
            {typeid(int64_t).name(), "int64_t"},
            {typeid(double).name(), "double"},
            {typeid(std::string).name(), "std::string"},
            {typeid(uint64_t*).name(), "uint64_t*"},
            {typeid(int64_t*).name(), "int64_t*"},
            {typeid(double*).name(), "double*"},
            {typeid(std::string*).name(), "std::string*"},
        };
    } else {
        se = {
            {typeid(uint64_t).name(), "long"},
            {typeid(int64_t).name(), "int"},
            {typeid(double).name(), "double"},
            {typeid(std::string).name(), "string"},
            {typeid(uint64_t*).name(), "Pointer of long"},
            {typeid(int64_t*).name(), "Pointer of int"},
            {typeid(double*).name(), "Pointer of double"},
            {typeid(std::string).name(), "Pointer of string"},
        };
    }

    auto it = se.find(type.name());
    if (it != se.end()) {
        return it->second;
    } else {
        return std::string("UnknownType(") + type.name() + ")";
    }
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

void VM::switchToCallFrame(VM_CallFrame &frame)
{
    this->stack = frame.stack;
}

void VM::switchToMainStack()
{
    this->stack = this->main;
}

VM_Info VM::step()
{
    state = VM_State::RUNNING;
    Instruction operation = instructions[pc];

    VM_State initialState = VM_State::STANDBY;
    bool isJump = false;

    if (pc >= instructions.size())
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
        case Opcode::spush:
        {
            stack.push(std::get<std::string>(operation.value));
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
        case Opcode::exit:
        {
            initialState = VM_State::EXITED;
            break;
        }
        case Opcode::call:
        {
            uint64_t target_address = std::get<uint64_t>(operation.value);
            VM_CallFrame frame;
            frame.return_address = pc + 1;

            uint64_t argCount = std::get<uint64_t>(stack.pop()); 

            for (uint64_t i = 0; i < argCount; ++i)
            {
                frame.stack.push(stack.pop());
            }

            callstack.push_back(std::move(frame));
            switchToCallFrame(callstack.back());
            pc = target_address;
            isJump = true;
            break;
        }
        case Opcode::ret:
        {
            if (callstack.empty())
            {
                std::cerr << "empty callstack" << std::endl;
                initialState = VM_State::ERROR;
            }
            else
            {
                pc = callstack.back().return_address;
                StackElement e;
                if (stack.getAll().size() > 0)
                {
                    e = stack.pop();
                    switchToMainStack();
                    stack.push(e);
                }
                else
                {
                    switchToMainStack();
                }
                callstack.pop_back();
                isJump = true;
            }
            break;
        }
        }

        if (!isJump)
        {
            pc++;
        }

        state = initialState;
    }

    return VM_Info(
        pc,
        state,
        operation,
        stack,
        this->getMemoryUsage(),
        0);
}

void VM::suspend()
{
    state = VM_State::SUSPENDED;
}

void VM::resume()
{
    state = VM_State::STANDBY;
#ifdef ANDESITE_VM_DEBUG
    std::cout << "VM Resumed." << std::endl;
#endif
}

std::string getNameFromStatus(VM_State status)
{
    switch (status)
    {
    case VM_State::STANDBY:
        return "Stand-by";
    case VM_State::RUNNING:
        return "Running";
    case VM_State::SUSPENDED:
        return "Suspended";
    case VM_State::EXITED:
        return "Exited";
    case VM_State::ERROR:
        return "Error";
    }
    return "Unknown";
}

void VM::printStack(const Stack &s)
{
    std::deque<StackElement> e = s.getAll();
    std::cout << "Stack:" << std::endl;
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
            } 
        }, e[i]);

        std::visit([this](auto&& val) {
            using T = std::decay_t<decltype(val)>;
            std::cout << " (" << getTypeName(typeid(T), flags & VM_NativeTypeNameInDebugOutput) << ")";;
        }, e[i]);

        std::cout << std::endl;
    }
}

void VM::printInfo(const VM_Info &info)
{
    VM::printStack(info.stack);

    std::cout << "Program Counter: " << info.program_counter << std::endl;
    std::cout << "Status: " << getNameFromStatus(info.current_status) << std::endl;
    std::cout << "Used Physical Memory(MB): " << (info.used_physical_memory / 1024) << std::endl;
    std::cout << std::endl;
}

int VM::execute()
{
    state = VM_State::STANDBY;

    while (state != VM_State::ERROR && state != VM_State::EXITED)
    {
        if (state == VM_State::STANDBY)
        {
#ifdef ANDESITE_VM_DEBUG
            printInfo(step());
#else
            step();
#endif
        }
    }

#ifdef ANDESITE_VM_DEBUG
    std::cout << "Execution Ended." << std::endl;
    printStack(stack);
#endif

    return 0;
}