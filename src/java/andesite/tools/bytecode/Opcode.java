package andesite.tools.bytecode;

public enum Opcode {
    // General
    SKIP(0x0000),
    HALT(0x0001),
    DUMP(0x0002),
    PRINT(0x0003),
    EXIT(0x0004),
    ARGS(0x0005),
    NEWTHREAD(0x0006),
    RNEWTHREAD(0x0007),
    GLOAD(0x0117),
    GSTORE(0x0118),
    // References
    NULL(0x0008),
    GETFIELD(0x0009),
    SETFIELD(0x000A),
    GETSTATIC(0x000B),
    SETSTATIC(0x000C),
    INVOKE(0x000D),
    INVOKEVIRTUAL(0x000E),
    INVOKEREFERENCE(0x000F),
    INVOKESTATIC(0x0010),
    INVOKEINTERFACE(0x0011),
    CAST(0x0012),
    RET(0x0013),
    // Constant Pools
    CLOAD_0(0x0014),
    CLOAD_1(0x0015),
    CLOAD_2(0x0016),
    CLOAD_3(0x0017),
    CLOAD(0x0018),
    // Local Variables
    RLOAD_0(0x0019),
    RLOAD_1(0x001A),
    RLOAD_2(0x001B),
    RLOAD_3(0x001C),
    RLOAD(0x001D),
    RSTORE_0(0x001E),
    RSTORE_1(0x001F),
    RSTORE_2(0x0020),
    RSTORE_3(0x0021),
    RSTORE(0x0022),
    I8LOAD(0x0023),
    I8STORE(0x0024),
    I16LOAD(0x0025),
    I16STORE(0x0026),
    I32LOAD(0x0027),
    I32STORE(0x0028),
    I64LOAD(0x0029),
    I64STORE(0x002A),
    U8LOAD(0x002B),
    U8STORE(0x002C),
    U16LOAD(0x002D),
    U16STORE(0x002E),
    U32LOAD(0x002F),
    U32STORE(0x0030),
    U64LOAD(0x0031),
    U64STORE(0x0032),
    F32LOAD(0x0033),
    F32STORE(0x0034),
    F64LOAD(0x0035),
    F64STORE(0x0036),
    BLOAD(0x0037),
    BSTORE(0x0038),
    C16LOAD(0x0039),
    C16STORE(0x003A),
    INCL(0x003B),
    DECR(0x003C),
    // Compare - Numbers
    CMPI8(0x003D),
    CMPI16(0x003E),
    CMPI32(0x003F),
    CMPI64(0x0040),
    CMPU8(0x0041),
    CMPU16(0x0042),
    CMPU32(0x0043),
    CMPU64(0x0044),
    CMPF32(0x0045),
    CMPF64(0x0046),
    // Compare - Other
    CMPSTR(0x0047),
    CMPSTRD(0x0048),
    CMPSTRL(0x0049),
    CMPREF(0x004A),
    CMPARR(0x004B),
    CMPARRL(0x004C),
    CMPBOOL(0x004D),
    // Checking
    ISNAN(0x004E),
    ISOBJ(0x004F),
    ISNULL(0x0050),
    // Stack
    DUP(0x0051),
    SWAP(0x0052),
    POP(0x0053),
    // String
    STRLEN(0x0054),
    STRSUB(0x0055),
    STRCONCAT(0x0056),
    // Array
    ARRNEW(0x0057),
    ARRNEWMULTI(0x0058),
    ARRNEWA(0x0059),
    ARRNEWAMULTI(0x005A),
    ARRLEN(0x005B),
    ARRGET(0x005C),
    ARRSET(0x005D),
    // Control
    JMP(0x005E),
    JMPEQ(0x005F),
    JMPNEQ(0x0060),
    JMPLT(0x0061),
    JMPGT(0x0062),
    JMPLTE(0x0063),
    JMPGTE(0x0064),
    JMPO(0x0065),
    JMPOEQ(0x0066),
    JMPONEQ(0x0067),
    JMPOLT(0x0068),
    JMPOGT(0x0069),
    JMPOLTE(0x006A),
    JMPOGTE(0x006B),
    IFNULL(0x006C),
    IFNOTNULL(0x006D),
    TSWITCH(0x006E),
    LSWITCH(0x006F),
    // Arithmetic
    ADDI8(0x0070),
    SUBI8(0x0071),
    MULI8(0x0072),
    DIVI8(0x0073),
    MODI8(0x0074),
    ADDI16(0x0075),
    SUBI16(0x0076),
    MULI16(0x0077),
    DIVI16(0x0078),
    MODI16(0x0079),
    ADDI32(0x007A),
    SUBI32(0x007B),
    MULI32(0x007C),
    DIVI32(0x007D),
    MODI32(0x007E),
    ADDI64(0x007F),
    SUBI64(0x0080),
    MULI64(0x0081),
    DIVI64(0x0082),
    MODI64(0x0083),
    ADDU8(0x0084),
    SUBU8(0x0085),
    MULU8(0x0086),
    DIVU8(0x0087),
    MODU8(0x0088),
    ADDU16(0x0089),
    SUBU16(0x008A),
    MULU16(0x008B),
    DIVU16(0x008C),
    MODU16(0x008D),
    ADDU32(0x008E),
    SUBU32(0x008F),
    MULU32(0x0090),
    DIVU32(0x0091),
    MODU32(0x0092),
    ADDU64(0x0093),
    SUBU64(0x0094),
    MULU64(0x0095),
    DIVU64(0x0096),
    MODU64(0x0097),
    ADDF32(0x0098),
    SUBF32(0x0099),
    MULF32(0x009A),
    DIVF32(0x009B),
    MODF32(0x009C),
    ADDF64(0x009D),
    SUBF64(0x009E),
    MULF64(0x009F),
    DIVF64(0x00A0),
    MODF64(0x00A1),
    // Conversion
    I8TOI16(0x00A2),
    I8TOI32(0x00A3),
    I8TOI64(0x00A4),
    I8TOF32(0x00A5),
    I8TOF64(0x00A6),
    I16TOI8(0x00A7),
    I16TOI32(0x00A8),
    I16TOI64(0x00A9),
    I16TOF32(0x00AA),
    I16TOF64(0x00AB),
    I32TOI8(0x00AC),
    I32TOI16(0x00AD),
    I32TOI64(0x00AE),
    I32TOF32(0x00AF),
    I32TOF64(0x00B0),
    I64TOI8(0x00B1),
    I64TOI16(0x00B2),
    I64TOI32(0x00B3),
    I64TOF32(0x00B4),
    I64TOF64(0x00B5),
    F32TOI8(0x00B6),
    F32TOI16(0x00B7),
    F32TOI32(0x00B8),
    F32TOI64(0x00B9),
    F32TOF64(0x00BA),
    F64TOI8(0x00BB),
    F64TOI16(0x00BC),
    F64TOI32(0x00BD),
    F64TOI64(0x00BE),
    F64TOF32(0x00BF),
    I32TOC16(0x00C0),
    C16TOI32(0x00C1),
    // Conversion (Unsigned)
    U8TOI8(0x00C2),
    U8TOI16(0x00C3),
    U8TOI32(0x00C4),
    U8TOI64(0x00C5),
    U8TOF32(0x00C6),
    U8TOF64(0x00C7),
    U16TOI8(0x00C8),
    U16TOI16(0x00C9),
    U16TOI32(0x00CA),
    U16TOI64(0x00CB),
    U16TOF32(0x00CC),
    U16TOF64(0x00CD),
    U32TOI8(0x00CE),
    U32TOI16(0x00CF),
    U32TOI32(0x00D0),
    U32TOI64(0x00D1),
    U32TOF32(0x00D2),
    U32TOF64(0x00D3),
    U64TOI8(0x00D4),
    U64TOI16(0x00D5),
    U64TOI32(0x00D6),
    U64TOI64(0x00D7),
    U64TOF32(0x00D8),
    U64TOF64(0x00D9),
    // Negation
    NEGI8(0x00DA),
    NEGI16(0x00DB),
    NEGI32(0x00DC),
    NEGI64(0x00DD),
    NEGU8(0x00DE),
    NEGU16(0x00DF),
    NEGU32(0x00E0),
    NEGU64(0x00E1),
    NEGF32(0x00E2),
    NEGF64(0x00E3),
    // Bitwise
    ANDI8(0x00E4),
    ANDI16(0x00E5),
    ANDI32(0x00E6),
    ANDI64(0x00E7),
    ANDU8(0x00E8),
    ANDU16(0x00E9),
    ANDU32(0x00EA),
    ANDU64(0x00EB),
    ORI8(0x00EC),
    ORI16(0x00ED),
    ORI32(0x00EE),
    ORI64(0x00EF),
    ORU8(0x00F0),
    ORU16(0x00F1),
    ORU32(0x00F2),
    ORU64(0x00F3),
    XORI8(0x00F4),
    XORI16(0x00F5),
    XORI32(0x00F6),
    XORI64(0x00F7),
    XORU8(0x00F8),
    XORU16(0x00F9),
    XORU32(0x00FA),
    XORU64(0x00FB),
    NOTI8(0x00FC),
    NOTI16(0x00FD),
    NOTI32(0x00FE),
    NOTI64(0x00FF),
    NOTU8(0x0100),
    NOTU16(0x0101),
    NOTU32(0x0102),
    NOTU64(0x0103),
    SHLI8(0x0104),
    SHLI16(0x0105),
    SHLI32(0x0106),
    SHLI64(0x0107),
    SHRI8(0x0108),
    SHRI16(0x0109),
    SHRI32(0x010A),
    SHRI64(0x010B),
    SHRU8(0x010C),
    SHRU16(0x010D),
    SHRU32(0x010E),
    SHRU64(0x010F),
    // Object Creation
    OP_NEW(0x0110),
    // Exception Handling
    OP_THROW(0x0111),
    OP_CATCH(0x0112),
    // Function Definition
    DEFUN(0x0113),
    CLOSURE(0x0114),
    // Synchronization
    LOCK(0x0115),
    UNLOCK(0x0116);

    private final int code;

    Opcode(int code) {
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public static Opcode fromCode(int code) {
        for (Opcode op : Opcode.values()) {
            if (op.code == code) {
                return op;
            }
        }
        throw new IllegalArgumentException("Unknown opcode: " + Integer.toHexString(code));
    }

    public byte[] toBytes() {
        return new byte[] {
                (byte)((code >> 8) & 0xFF),
                (byte)(code & 0xFF)
        };
    }
}