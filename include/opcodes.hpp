#pragma once

#include "cstdint"
#include "stack.hpp"

enum class Opcode : uint16_t {
    nop = 0x0000,
    ipush = 0x0001,
    upush = 0x0002,
    fpush = 0x0003,
    ppush = 0x0004, //pointer
    spush = 0x0005,
    pop = 0x0006,
    dup = 0x0007,
    pcall = 0x0008,
    call = 0x0009,
    swap = 0x000A,
    ret = 0x000B,
    def = 0x000C,
    dcall = 0x000D,
    _new = 0x000E,
    getf = 0x000F,
    setf = 0x0010,
    inv = 0x0011,
    alloc = 0x0012,
    free = 0x0013,
    lstore = 0x0014, //local
    lload = 0x0015,
    gstore = 0x0016, //global
    gload = 0x0017,
    iadd = 0x0018,
    isub = 0x0019,
    imul = 0x001A,
    idiv = 0x001B,
    imod = 0x001C,
    fadd = 0x001D,
    fsub = 0x001E,
    fmul = 0x001F,
    fdiv = 0x0020,
    uadd = 0x0021,
    usub = 0x0022,
    umul = 0x0023,
    udiv = 0x0024,
    umod = 0x0025,
    exit = 0x0026,
    native = 0x0027,
};

struct Instruction {
    static inline const StackElement ZERO = static_cast<int64_t>(0);
    public:
        Opcode op;
        StackElement value;

        explicit Instruction(Opcode op, StackElement value): op(op), value(value) {}
};