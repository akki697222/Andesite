package andesite;

import andesite.tools.bytecode.*;

import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.HexFormat;

public class Main {
    public static void main(String[] args) {
        BytecodeBuilder builder = new BytecodeBuilder();

        builder.addConstant(new ConstantBuilder()
                .value("Hello, World!".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.STRING)
                .build())
                .addConstant(new ConstantBuilder()
                .value(new byte[]{0x00, 0x03, 0x00, 0x06})
                .tags(ConstantTags.REFERENCE)
                .build())
                .addConstant(new ConstantBuilder()
                .value(new byte[]{0x00, 0x04, 0x00, 0x05})
                .tags(ConstantTags.REFERENCE)
                .build())
                .addConstant(new ConstantBuilder()
                .value("std".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addConstant(new ConstantBuilder()
                .value("io".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addConstant(new ConstantBuilder()
                .value("println".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addConstant(new ConstantBuilder()
                .value(new byte[]{0x00, 0x08})
                .tags(ConstantTags.REFERENCE)
                .build())
                .addConstant(new ConstantBuilder()
                .value("test".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addConstant(new ConstantBuilder()
                .value(new byte[]{0x00, 0x0A})
                .tags(ConstantTags.REFERENCE)
                .build())
                .addConstant(new ConstantBuilder()
                .value("main".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addConstant(new ConstantBuilder()
                .value(new byte[]{0x00, 0x0C})
                .tags(ConstantTags.TYPE)
                .build())
                .addConstant(new ConstantBuilder()
                .value("string[]".getBytes(StandardCharsets.UTF_8))
                .tags(ConstantTags.IDENTIFIER)
                .build())
                .addImport("std#_GLOBAL$std".getBytes(StandardCharsets.UTF_8));

        byte[] mainFunctionCode;

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.writeBytes(Opcode.INVOKEREFERENCE.toBytes());
            outputStream.write(7);
            outputStream.writeBytes(Opcode.INVOKESTATIC.toBytes());
            outputStream.write(2);
            outputStream.writeBytes(Opcode.NULL.toBytes());
            outputStream.writeBytes(Opcode.RET.toBytes());
            mainFunctionCode = outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        builder.addDefine(new DefineBuilder.FunctionDefineBuilder()
                .args(new byte[]{0x00, 0x0B})
                .name(10)
                .code(mainFunctionCode)
                .build());

        byte[] testFunctionCode;

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.writeBytes(Opcode.CLOAD_1.toBytes());
            outputStream.writeBytes(Opcode.RET.toBytes());
            testFunctionCode = outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        builder.addDefine(new DefineBuilder.FunctionDefineBuilder()
                .args(new byte[]{})
                .name(8)
                .code(testFunctionCode)
                .build());

        byte[] initCode;

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.writeBytes(Opcode.ARGS.toBytes());
            outputStream.writeBytes(Opcode.INVOKEREFERENCE.toBytes());
            outputStream.write(10);
            outputStream.writeBytes(Opcode.EXIT.toBytes());
            initCode = outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        builder.setInit(builder.createInit(initCode));

        displayHexEditor(builder.build());
        System.out.println("Raw: " + Arrays.toString(builder.build()));

        try (FileOutputStream outputStream = new FileOutputStream("test.andesite")) {
            outputStream.write(builder.build());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void displayHexEditor(byte[] byteData) {
        for (int i = 0; i < byteData.length; i += 16) {
            // 行番号を表示（8桁の16進数）
            System.out.printf("%08x  ", i);

            // 16進数部分を表示
            for (int j = 0; j < 16; j++) {
                if (i + j < byteData.length) {
                    System.out.printf("%02x ", byteData[i + j] & 0xFF);
                } else {
                    System.out.print("   ");
                }
            }

            // ASCII部分を表示（表示可能な文字のみ、否则は`.`を表示）
            System.out.print("  ");
            for (int j = 0; j < 16; j++) {
                if (i + j < byteData.length) {
                    int b = byteData[i + j] & 0xFF;
                    if (b >= 32 && b <= 126) {
                        System.out.print((char) b);
                    } else {
                        System.out.print(".");
                    }
                }
            }
            System.out.println();
        }
    }
}
