package andesite.tools.bytecode;

public enum DefineTags {
    Function(0x01),
    Class(0x02),
    Interface(0x03);
    private final int value;
    DefineTags(int value) { this.value = value; }
    public int getValue() { return value; }
}
