package andesite.tools.bytecode;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class BytecodeBuilder {
    private static final byte[] MAGIC_NUMBER = {0x12, 0x34, 0x56, 0x78};
    private static final int MAJOR_VERSION = 1;
    private static final int MINOR_VERSION = 0;
    private final List<byte[]> constantPool = new ArrayList<>();
    private final List<byte[]> imports = new ArrayList<>();
    private final List<byte[]> defines = new ArrayList<>();
    private byte[] init;

    public BytecodeBuilder addConstant(byte[] constant) {
        constantPool.add(constant);
        return this;
    }

    public BytecodeBuilder addImport(byte[] importBytes) {
        imports.add(importBytes);
        return this;
    }

    public BytecodeBuilder addDefine(byte[] define) {
        defines.add(define);
        return this;
    }

    public BytecodeBuilder setInit(byte[] init) {
        this.init = init;
        return this;
    }

    public byte[] createInit(byte[] code) {
        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.write(ByteBuffer.allocate(4).putInt(code.length).array());
            outputStream.writeBytes(code);
            return outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public byte[] build() {
        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.writeBytes(MAGIC_NUMBER);
            outputStream.writeBytes(ByteBuffer.allocate(4).putInt(MAJOR_VERSION).array());
            outputStream.writeBytes(ByteBuffer.allocate(4).putInt(MINOR_VERSION).array());

            //Write Constant pool
            outputStream.write(0x01);

            int size = 0;
            for (byte[] bytes : constantPool) {
                size = size + bytes.length;
            }

            outputStream.writeBytes(ByteBuffer.allocate(4).putInt(size).array());
            outputStream.writeBytes(ByteBuffer.allocate(4).putInt(constantPool.size()).array());

            for (byte[] constant : constantPool) {
                outputStream.write(constant);
            }

            //Write Imports
            outputStream.write(0x02);

            for (byte[] importByte : imports) {
                outputStream.writeBytes((ByteBuffer.allocate(4).putInt(importByte.length).array()));
                outputStream.writeBytes(importByte);
            }

            //Write Defines
            outputStream.write(0x03);

            for (byte[] define : defines) {
                outputStream.writeBytes(define);
            }

            outputStream.write(0x04);
            outputStream.writeBytes(init);

            return outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}