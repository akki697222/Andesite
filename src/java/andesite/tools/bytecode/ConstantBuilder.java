package andesite.tools.bytecode;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class ConstantBuilder {
    private ConstantTags tags = null;
    private byte[] value = null;

    public ConstantBuilder tags(ConstantTags tags) {
        this.tags = tags;
        return this;
    }

    public ConstantBuilder value(byte[] value) {
        this.value = value.clone();
        return this;
    }

    public byte[] build() {
        if (tags == null || value == null) {
            throw new IllegalStateException("Both tags and value must be set before calling build().");
        }

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.write(tags.getValue());
            outputStream.write(ByteBuffer.allocate(4).putInt(value.length).array());
            outputStream.write(value);

            return outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}