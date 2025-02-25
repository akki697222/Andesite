package andesite.tools.bytecode;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class DefineBuilder {
    private DefineTags tags;
    private byte[] payload;

    public DefineBuilder tags(DefineTags tags) {
        this.tags = tags;
        return this;
    }

    public DefineBuilder payload(byte[] payload) {
        this.payload = payload;
        return this;
    }

    public byte[] build() {
        if (tags == null || payload == null) {
            throw new IllegalStateException("Both tags and payload must be set before calling build().");
        }

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.write(tags.getValue());
            outputStream.write(payload.length);
            outputStream.writeBytes(payload);

            return outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static class FunctionDefineBuilder {
        private byte[] code;
        private int name;
        private byte[] args;

        public FunctionDefineBuilder args(byte[] args) {
            this.args = args;
            return this;
        }

        public FunctionDefineBuilder code(byte[] code) {
            this.code = code;
            return this;
        }

        /**
         * Name from constant pool index.
         */
        public FunctionDefineBuilder name(int name) {
            this.name = name;
            return this;
        }

        public byte[] build() {
            if (code == null) {
                throw new IllegalStateException("Value must be set before calling build().");
            }

            try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
                outputStream.writeBytes(ByteBuffer.allocate(4).putInt(name).array());
                outputStream.writeBytes(args);
                outputStream.write(args.length);
                outputStream.writeBytes(ByteBuffer.allocate(4).putInt(code.length).array());
                outputStream.writeBytes(code);

                return outputStream.toByteArray();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
