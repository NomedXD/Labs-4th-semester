package com.example.lab2;

public class StreamEncryption {
    public static byte[] generateKey(int userKey, int tactCount) {
        byte[] result = new byte[tactCount / 8]; // массив байтов(биты результирующего ключа)
        byte highBit = 0; // старший выдвигаемый бит
        byte xorResult = 0; // результат xor
        for (int i = 0; i < tactCount; ++i) { // цикл по количеству битов в исходных данных
            highBit = (byte)((userKey >>> 28) & 1);
            result[i / 8] <<= 1;
            result[i / 8] |= highBit;
            xorResult = (byte)( ((userKey >>> 28) ^ // Обратная связь
                    (userKey >>> 1)) & 1 );
            userKey <<= 1; // Сдвиг регистра
            userKey |= xorResult; // Запись полученного бита в конец
        }
        return result;
    }

    public static byte[] transform(byte[] bytesArrayM, byte[] generatedKey) {
        byte[] bytesArrayC = new byte[bytesArrayM.length];
        for (int i = 0; i < bytesArrayC.length; ++i) {
            bytesArrayC[i] = (byte)(bytesArrayM[i] ^ generatedKey[i]);
        }
        return bytesArrayC;
    }
}
