#include "vector"
#include "stack.hpp"
#include "opcodes.hpp"
#include "cstdint"

#ifndef ANDESITE_VM
#define ANDESITE_VM

enum class VM_State : uint8_t
{
    STANDBY = 0x01,
    SUSPENDED = 0x02,
    RUNNING = 0x03,
    EXITED = 0x04,
    ERROR = 0xFF,
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
    VM(std::vector<Instruction> &instructions) : instructions(instructions)
    {
        state = VM_State::STANDBY;
    }

    int execute();
    VM_Info step();
    void printStatus();
    void suspend();
    void resume(); 
    size_t getMemoryUsage() const {
        return sizeof(*this);
    }
private:
    int pc = 0;
    VM_State state;
    std::vector<Instruction> instructions;
    Stack stack = Stack();
};

#endif