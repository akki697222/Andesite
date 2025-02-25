package andesite.tools.bytecode;

public enum ConstantTags {
    IDENTIFIER(0x0F),
    REFERENCE(0x01),
    STRING(0x02),
    UNICODE(0x03),
    BOOL(0x04),
    CHAR(0x05),
    TYPE(0x06),
    i8(0x10),
    i16(0x11),
    i32(0x12),
    i64(0x13),
    f32(0x14),
    f64(0x15),
    u8(0x16),
    u16(0x17),
    u32(0x18),
    u64(0x19);
    private final int value;
    ConstantTags(int value) { this.value = value; }
    public int getValue() { return value; }
}