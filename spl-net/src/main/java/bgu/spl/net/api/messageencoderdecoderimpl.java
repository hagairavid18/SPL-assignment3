package bgu.spl.net.api;

import bgu.spl.net.Frames.MessageIn;
import bgu.spl.net.Frames.MessageOut;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class MessageEncoderDecoderimpl implements MessageEncoderDecoder {
    private byte[] bytes = new byte[1 << 10];
    private int len = 0;


    @Override
    public String decodeNextByte(byte nextByte) {

        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);

        if (nextByte == '\u0000') return popString();

        pushByte(nextByte);
        return null;
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }

        bytes[len++] = nextByte;
    }

    @Override
    public byte[] encode(Object message) {
        return ((MessageOut)message).encode();
    }

    private String popString() {

        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);

        len = 0;
        return result;
    }

}
