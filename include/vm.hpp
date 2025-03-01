#pragma once

#define VM_DEFAULT_CALLSTACK_SIZE 128
#define VM_WIDE_CALLSTACK_SIZE 1024
#define VM_MAX_STACK_SIZE 65535
#define VM_MAX_CALLFRAME_STACK_SIZE 8192

#include "vector"
#include "stack.hpp"
#include "opcodes.hpp"
#include "cstdint"
#include "memory"
#include "deque"

enum class VM_State : uint8_t
{
    STANDBY = 0x01,
    SUSPENDED = 0x02,
    RUNNING = 0x03,
    EXITED = 0x04,
    ERROR = 0xFF,
};

struct VM_CallFrame {
    uint64_t return_address;
    Stack stack = Stack();
};

enum VM_Flags : uint16_t{
    VM_WideCallStack = 1 << 0,
    VM_Debug = 1 << 1,
    VM_NativeTypeNameInDebugOutput = 1 << 2,
};

struct VM_Info
{
    const int program_counter;
    const VM_State current_status;
    const Instruction instruction_executing;
    const Stack stack;
    const int used_physical_memory;
    const int heap_memory;

public:
    VM_Info(
        int program_counter,
        VM_State &current_status,
        Instruction &instruction_executing,
        Stack &stack,
        int used_physical_memory,
        int heap_memory) : program_counter(program_counter),
                           current_status(current_status),
                           instruction_executing(instruction_executing),
                           stack(stack),
                           used_physical_memory(used_physical_memory),
                           heap_memory(heap_memory) {}
};

class VM
{
public:
    VM(std::vector<Instruction> &instructions, uint16_t flags) : instructions(instructions), flags(flags)
    {
        state = VM_State::STANDBY;
        if (flags & VM_WideCallStack) {
            callstack.resize(1024);
        } else {
            callstack.resize(VM_DEFAULT_CALLSTACK_SIZE);
        }
    }

    int execute();
    VM_Info step();
    void printStack(const Stack &s);
    void printInfo(const VM_Info &info);
    void suspend();
    void resume(); 
    void switchToCallFrame(VM_CallFrame& frame);
    void switchToMainStack();
    size_t getMemoryUsage() const {
        return sizeof(*this);
    }
private:
    int pc = 0;
    VM_State state;
    std::vector<Instruction> instructions;
    std::vector<VM_CallFrame> callstack;
    Stack main = Stack();
    Stack stack = main;
    uint16_t flags;
};