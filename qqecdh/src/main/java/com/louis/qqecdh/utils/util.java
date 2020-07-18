package com.louis.qqecdh.utils;

public class util {
    public static byte get_char(byte arg1) {
        if(arg1 >= 0x30 && arg1 <= 57) {
            return (byte)(arg1 - 0x30);
        }

        if(arg1 >= 97 && arg1 <= 102) {
            return (byte)(arg1 - 87);
        }

        return arg1 < 65 || arg1 > 70 ? 0 : ((byte)(arg1 - 55));
    }

    public static String buf_to_string(byte[] arg3) {
        if(arg3 == null) {
            return "";
        }

        String v1 = "";
        int v0;
        for(v0 = 0; v0 < arg3.length; ++v0) {
            v1 = v1 + Integer.toHexString(arg3[v0] >> 4 & 15) + Integer.toHexString(arg3[v0] & 15);
        }

        return v1;
    }

    public static byte[] string_to_buf(String arg4) {
        int v0 = 0;
        if(arg4 == null) {
            return new byte[0];
        }

        byte[] v1 = new byte[arg4.length() / 2];
        while(v0 < arg4.length() / 2) {
            v1[v0] = (byte)((get_char(((byte)arg4.charAt(v0 * 2))) << 4) + get_char(((byte)arg4.charAt(v0 * 2 + 1))));
            ++v0;
        }

        return v1;
    }
}
