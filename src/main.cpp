#include "vm.hpp"
#include "opcodes.hpp"
#include "vector"

int main() {
    /*
        ipush 1
        ipush 2
        upush 2
        call 5
        exit
        iadd
        ret
    */

    std::vector<Instruction> instructions = {
        Instruction(Opcode::ipush, static_cast<int64_t>(1)),
        Instruction(Opcode::ipush, static_cast<int64_t>(2)),
        Instruction(Opcode::upush, static_cast<uint64_t>(2)),
        Instruction(Opcode::call, static_cast<uint64_t>(5)),
        Instruction(Opcode::exit, 0),
        Instruction(Opcode::iadd, 0),
        Instruction(Opcode::ret, 0)
    };

    VM vm(instructions, VM_Debug | VM_NativeTypeNameInDebugOutput);
    vm.execute();

    return 0;
}