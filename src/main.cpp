#include "vm.hpp"
#include "opcodes.hpp"
#include "vector"

int main() {
    std::vector<Instruction> instructions = {
        Instruction(Opcode::ipush, static_cast<int64_t>(10)),
        Instruction(Opcode::ipush, static_cast<int64_t>(20)),
        Instruction(Opcode::iadd, static_cast<int64_t>(0)),
        Instruction(Opcode::ipush, static_cast<int64_t>(10)),
        Instruction(Opcode::idiv, static_cast<int64_t>(0))
    };

    VM vm(instructions);
    vm.execute();

    return 0;
}