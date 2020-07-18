package com.louis.qqecdh.utils;



import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;

public class MD5 {
    static byte[] PADDING = null;
    static final int S11 = 7;
    static final int S12 = 12;
    static final int S13 = 17;
    static final int S14 = 22;
    static final int S21 = 5;
    static final int S22 = 9;
    static final int S23 = 14;
    static final int S24 = 20;
    static final int S31 = 4;
    static final int S32 = 11;
    static final int S33 = 16;
    static final int S34 = 23;
    static final int S41 = 6;
    static final int S42 = 10;
    static final int S43 = 15;
    static final int S44 = 21;
    private byte[] buffer;
    private long[] count;
    private byte[] digest;
    public String digestHexStr;
    private long[] state;

    static {
        MD5.PADDING = new byte[]{(byte)0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

    public MD5() {
        this.state = new long[4];
        this.count = new long[2];
        this.buffer = new byte[0x40];
        this.digest = new byte[16];
        this.md5Init();
    }

    private void Decode(long[] arg8, byte[] arg9, int arg10) {
        int v0 = 0;
        int v1 = 0;
        while(v0 < arg10) {
            arg8[v1] = MD5.b2iu(arg9[v0]) | MD5.b2iu(arg9[v0 + 1]) << 8 | MD5.b2iu(arg9[v0 + 2]) << 16 | MD5.b2iu(arg9[v0 + 3]) << 24;
            ++v1;
            v0 += 4;
        }
    }

    private void Encode(byte[] arg11, long[] arg12, int arg13) {
        int v0 = 0;
        int v1 = 0;
        while(v0 < arg13) {
            if(v1 >= arg12.length) {
            }

            arg11[v0] = (byte)(((int)(arg12[v1] & 0xFFL)));
            arg11[v0 + 1] = (byte)(((int)(arg12[v1] >>> 8 & 0xFFL)));
            arg11[v0 + 2] = (byte)(((int)(arg12[v1] >>> 16 & 0xFFL)));
            arg11[v0 + 3] = (byte)(((int)(arg12[v1] >>> 24 & 0xFFL)));
            ++v1;
            v0 += 4;
        }
    }

    private long F(long arg6, long arg8, long arg10) {
        return arg6 & arg8 | (-1L ^ arg6) & arg10;
    }

    private long FF(long arg12, long arg14, long arg16, long arg18, long arg20, long arg22, long arg24) {
        long v2 = this.F(arg14, arg16, arg18) + arg20 + arg24 + arg12;
        return ((long)(((int)v2) >>> ((int)(0x20L - arg22)) | ((int)v2) << ((int)arg22))) + arg14;
    }

    private long G(long arg6, long arg8, long arg10) {
        return arg6 & arg10 | (-1L ^ arg10) & arg8;
    }

    private long GG(long arg12, long arg14, long arg16, long arg18, long arg20, long arg22, long arg24) {
        long v2 = this.G(arg14, arg16, arg18) + arg20 + arg24 + arg12;
        return ((long)(((int)v2) >>> ((int)(0x20L - arg22)) | ((int)v2) << ((int)arg22))) + arg14;
    }

    private long H(long arg4, long arg6, long arg8) {
        return arg4 ^ arg6 ^ arg8;
    }

    private long HH(long arg12, long arg14, long arg16, long arg18, long arg20, long arg22, long arg24) {
        long v2 = this.H(arg14, arg16, arg18) + arg20 + arg24 + arg12;
        return ((long)(((int)v2) >>> ((int)(0x20L - arg22)) | ((int)v2) << ((int)arg22))) + arg14;
    }

    private long I(long arg4, long arg6, long arg8) {
        return (-1L ^ arg8 | arg4) ^ arg6;
    }

    private long II(long arg12, long arg14, long arg16, long arg18, long arg20, long arg22, long arg24) {
        long v2 = this.I(arg14, arg16, arg18) + arg20 + arg24 + arg12;
        return ((long)(((int)v2) >>> ((int)(0x20L - arg22)) | ((int)v2) << ((int)arg22))) + arg14;
    }

    public static long b2iu(byte arg2) {
        return arg2 >= 0 ? ((long)arg2) : ((long)(arg2 & 0xFF));
    }

    public static String byteHEX(byte arg4) {
        return new String(new char[]{new char[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}[arg4 >>> 4 & 15], new char[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}[arg4 & 15]});
    }

    public byte[] getMD5(InputStream arg3, long arg4) {
        this.md5Init();
        if(!this.md5Update(arg3, arg4)) {
            return new byte[16];
        }

        this.md5Final();
        return this.digest;
    }

    public byte[] getMD5(byte[] arg5) {
        this.md5Init();
        this.md5Update(new ByteArrayInputStream(arg5), ((long)arg5.length));
        this.md5Final();
        return this.digest;
    }

    public static String getMD5String(byte[] arg10) {
        int v0 = 0;
        char[] v3 = new char[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        try {
            MessageDigest v2 = MessageDigest.getInstance("MD5");
            v2.update(arg10);
            byte[] v4 = v2.digest();
            char[] v5 = new char[0x20];
            int v2_1 = 0;
            while(v0 < 16) {
                int v6 = v4[v0];
                int v7 = v2_1 + 1;
                v5[v2_1] = v3[v6 >>> 4 & 15];
                v2_1 = v7 + 1;
                v5[v7] = v3[v6 & 15];
                ++v0;
            }

            return new String(v5);
        }
        catch(Exception v0_1) {
            v0_1.printStackTrace();
            return null;
        }
    }

    private void md5Final() {
        byte[] v1 = new byte[8];
        this.Encode(v1, this.count, 8);
        int v0 = ((int)(this.count[0] >>> 3)) & 0x3F;
        this.md5Update(MD5.PADDING, v0 >= 56 ? 120 - v0 : 56 - v0);
        this.md5Update(v1, 8);
        this.Encode(this.digest, this.state, 16);
    }

    private void md5Init() {
        this.count[0] = 0L;
        this.count[1] = 0L;
        this.state[0] = 0x67452301L;
        this.state[1] = 0xEFCDAB89L;
        this.state[2] = 0x98BADCFEL;
        this.state[3] = 0x10325476L;
    }

    private void md5Memcpy(byte[] arg4, byte[] arg5, int arg6, int arg7, int arg8) {
        int v0;
        for(v0 = 0; v0 < arg8; ++v0) {
            arg4[arg6 + v0] = arg5[arg7 + v0];
        }
    }

    private void md5Transform(byte[] arg71) {
        long v4 = this.state[0];
        long v6 = this.state[1];
        long v8 = this.state[2];
        long v10 = this.state[3];
        long[] v2 = new long[16];
        this.Decode(v2, arg71, 0x40);
        long v16 = this.FF(v4, v6, v8, v10, v2[0], 7L, 3614090360L);
        long v14 = this.FF(v10, v16, v6, v8, v2[1], 12L, 3905402710L);
        long v12 = this.FF(v8, v14, v16, v6, v2[2], 17L, 0x242070DBL);
        long v22 = this.FF(v6, v12, v14, v16, v2[3], 22L, 3250441966L);
        long v20 = this.FF(v16, v22, v12, v14, v2[4], 7L, 0xF57C0FAFL);
        long v18 = this.FF(v14, v20, v22, v12, v2[5], 12L, 1200080426L);
        long v6_1 = this.FF(v12, v18, v20, v22, v2[6], 17L, 0xA8304613L);
        long v26 = this.FF(v22, v6_1, v18, v20, v2[7], 22L, 0xFD469501L);
        long v24 = this.FF(v20, v26, v6_1, v18, v2[8], 7L, 1770035416L);
        long v22_1 = this.FF(v18, v24, v26, v6_1, v2[9], 12L, 0x8B44F7AFL);
        long v6_2 = this.FF(v6_1, v22_1, v24, v26, v2[10], 17L, 0xFFFF5BB1L);
        long v30 = this.FF(v26, v6_2, v22_1, v24, v2[11], 22L, 2304563134L);
        long v28 = this.FF(v24, v30, v6_2, v22_1, v2[12], 7L, 1804603682L);
        long v26_1 = this.FF(v22_1, v28, v30, v6_2, v2[13], 12L, 0xFD987193L);
        long v6_3 = this.FF(v6_2, v26_1, v28, v30, v2[14], 17L, 2792965006L);
        long v12_1 = this.FF(v30, v6_3, v26_1, v28, v2[15], 22L, 0x49B40821L);
        long v28_1 = this.GG(v28, v12_1, v6_3, v26_1, v2[1], 5L, 0xF61E2562L);
        long v8_1 = this.GG(v26_1, v28_1, v12_1, v6_3, v2[6], 9L, 0xC040B340L);
        long v14_1 = this.GG(v6_3, v8_1, v28_1, v12_1, v2[11], 14L, 0x265E5A51L);
        long v30_1 = this.GG(v12_1, v14_1, v8_1, v28_1, v2[0], 20L, 3921069994L);
        long v10_1 = this.GG(v28_1, v30_1, v14_1, v8_1, v2[5], 5L, 0xD62F105DL);
        long v16_1 = this.GG(v8_1, v10_1, v30_1, v14_1, v2[10], 9L, 38016083L);
        long v32 = this.GG(v14_1, v16_1, v10_1, v30_1, v2[15], 14L, 0xD8A1E681L);
        long v12_2 = this.GG(v30_1, v32, v16_1, v10_1, v2[4], 20L, 0xE7D3FBC8L);
        long v18_1 = this.GG(v10_1, v12_2, v32, v16_1, v2[9], 5L, 0x21E1CDE6L);
        long v34 = this.GG(v16_1, v18_1, v12_2, v32, v2[14], 9L, 0xC33707D6L);
        long v14_2 = this.GG(v32, v34, v18_1, v12_2, v2[3], 14L, 0xF4D50D87L);
        long v20_1 = this.GG(v12_2, v14_2, v34, v18_1, v2[8], 20L, 1163531501L);
        long v36 = this.GG(v18_1, v20_1, v14_2, v34, v2[13], 5L, 0xA9E3E905L);
        long v16_2 = this.GG(v34, v36, v20_1, v14_2, v2[2], 9L, 0xFCEFA3F8L);
        long v22_2 = this.GG(v14_2, v16_2, v36, v20_1, v2[7], 14L, 0x676F02D9L);
        long v38 = this.GG(v20_1, v22_2, v16_2, v36, v2[12], 20L, 0x8D2A4C8AL);
        long v18_2 = this.HH(v36, v38, v22_2, v16_2, v2[5], 4L, 0xFFFA3942L);
        long v24_1 = this.HH(v16_2, v18_2, v38, v22_2, v2[8], 11L, 0x8771F681L);
        long v40 = this.HH(v22_2, v24_1, v18_2, v38, v2[11], 16L, 1839030562L);
        long v20_2 = this.HH(v38, v40, v24_1, v18_2, v2[14], 23L, 0xFDE5380CL);
        long v26_2 = this.HH(v18_2, v20_2, v40, v24_1, v2[1], 4L, 0xA4BEEA44L);
        long v42 = this.HH(v24_1, v26_2, v20_2, v40, v2[4], 11L, 0x4BDECFA9L);
        long v22_3 = this.HH(v40, v42, v26_2, v20_2, v2[7], 16L, 0xF6BB4B60L);
        long v28_2 = this.HH(v20_2, v22_3, v42, v26_2, v2[10], 23L, 0xBEBFBC70L);
        long v44 = this.HH(v26_2, v28_2, v22_3, v42, v2[13], 4L, 0x289B7EC6L);
        long v24_2 = this.HH(v42, v44, v28_2, v22_3, v2[0], 11L, 3936430074L);
        long v30_2 = this.HH(v22_3, v24_2, v44, v28_2, v2[3], 16L, 0xD4EF3085L);
        long v46 = this.HH(v28_2, v30_2, v24_2, v44, v2[6], 23L, 0x4881D05L);
        long v26_3 = this.HH(v44, v46, v30_2, v24_2, v2[9], 4L, 3654602809L);
        long v32_1 = this.HH(v24_2, v26_3, v46, v30_2, v2[12], 11L, 0xE6DB99E5L);
        long v48 = this.HH(v30_2, v32_1, v26_3, v46, v2[15], 16L, 0x1FA27CF8L);
        long v28_3 = this.HH(v46, v48, v32_1, v26_3, v2[2], 23L, 0xC4AC5665L);
        long v34_1 = this.II(v26_3, v28_3, v48, v32_1, v2[0], 6L, 0xF4292244L);
        long v50 = this.II(v32_1, v34_1, v28_3, v48, v2[7], 10L, 0x432AFF97L);
        long v30_3 = this.II(v48, v50, v34_1, v28_3, v2[14], 15L, 0xAB9423A7L);
        long v36_1 = this.II(v28_3, v30_3, v50, v34_1, v2[5], 21L, 0xFC93A039L);
        long v52 = this.II(v34_1, v36_1, v30_3, v50, v2[12], 6L, 1700485571L);
        long v32_2 = this.II(v50, v52, v36_1, v30_3, v2[3], 10L, 0x8F0CCC92L);
        long v38_1 = this.II(v30_3, v32_2, v52, v36_1, v2[10], 15L, 0xFFEFF47DL);
        long v54 = this.II(v36_1, v38_1, v32_2, v52, v2[1], 21L, 2240044497L);
        long v34_2 = this.II(v52, v54, v38_1, v32_2, v2[8], 6L, 0x6FA87E4FL);
        long v40_1 = this.II(v32_2, v34_2, v54, v38_1, v2[15], 10L, 0xFE2CE6E0L);
        long v56 = this.II(v38_1, v40_1, v34_2, v54, v2[6], 15L, 0xA3014314L);
        long v36_2 = this.II(v54, v56, v40_1, v34_2, v2[13], 21L, 0x4E0811A1L);
        long v42_1 = this.II(v34_2, v36_2, v56, v40_1, v2[4], 6L, 0xF7537E82L);
        long v58 = this.II(v40_1, v42_1, v36_2, v56, v2[11], 10L, 0xBD3AF235L);
        long v38_2 = this.II(v56, v58, v42_1, v36_2, v2[2], 15L, 0x2AD7D2BBL);
        long v2_1 = this.II(v36_2, v38_2, v58, v42_1, v2[9], 21L, 0xEB86D391L);
        this.state[0] += v42_1;
        this.state[1] = v2_1 + this.state[1];
        this.state[2] += v38_2;
        this.state[3] += v58;
    }

    private void md5Update(byte[] arg13, int arg14) {
        int v4 = 0;
        byte[] v7 = new byte[0x40];
        int v3 = ((int)(this.count[0] >>> 3)) & 0x3F;
        long[] v0 = this.count;
        long v8 = v0[0] + ((long)(arg14 << 3));
        v0[0] = v8;
        if(v8 < ((long)(arg14 << 3))) {
            ++this.count[1];
        }

        this.count[1] += (long)(arg14 >>> 29);
        int v5 = 0x40 - v3;
        if(arg14 >= v5) {
            this.md5Memcpy(this.buffer, arg13, v3, 0, v5);
            this.md5Transform(this.buffer);
            while(v5 + 0x3F < arg14) {
                this.md5Memcpy(v7, arg13, 0, v5, 0x40);
                this.md5Transform(v7);
                v5 += 0x40;
            }

            v3 = 0;
            v4 = v5;
        }

        this.md5Memcpy(this.buffer, arg13, v3, v4, arg14 - v4);
    }

    private boolean md5Update(InputStream arg13, long arg14) {
        byte[] v7 = new byte[0x40];
        int v3 = ((int)(this.count[0] >>> 3)) & 0x3F;
        long[] v0 = this.count;
        long v8 = v0[0] + (arg14 << 3);
        v0[0] = v8;
        if(v8 < arg14 << 3) {
            ++this.count[1];
        }

        this.count[1] += arg14 >>> 29;
        int v5 = 0x40 - v3;
        int v0_2 = 0;
        if(arg14 >= ((long)v5)) {
            byte[] v2 = new byte[v5];
            try {
                arg13.read(v2, 0, v5);
            }
            catch(Exception v0_1) {
                v0_1.printStackTrace();
                return false;
            }

            this.md5Memcpy(this.buffer, v2, v3, 0, v5);
            this.md5Transform(this.buffer);

            for(v0_2 = v5; ((long)(v0_2 + 0x3F)) < arg14; v0_2 += 0x40) {
                try {
                    arg13.read(v7);
                }
                catch(Exception v0_3) {
                    v0_3.printStackTrace();
                    return false;
                }

                this.md5Transform(v7);
            }

            v3 = 0;
        }
        else {
            v0_2 = 0;
        }

        byte[] v2_1 = new byte[((int)(arg14 - ((long)v0_2)))];
        try {
            arg13.read(v2_1);
        }
        catch(Exception v0_4) {
            v0_4.printStackTrace();
            return false;
        }

        this.md5Memcpy(this.buffer, v2_1, v3, 0, v2_1.length);
        return true;
    }

    public static String toMD5(String arg4) {
        byte[] v0_1;
        try {
            v0_1 = arg4.getBytes("ISO8859_1");
        }
        catch(UnsupportedEncodingException v0) {
            v0_1 = arg4.getBytes();
        }

        byte[] v2 = new MD5().getMD5(v0_1);
        String v1 = "";
        int v0_2;
        for(v0_2 = 0; v0_2 < 16; ++v0_2) {
            v1 = v1 + MD5.byteHEX(v2[v0_2]);
        }

        return v1;
    }

    public static String toMD5(byte[] arg4) {
        byte[] v2 = new MD5().getMD5(arg4);
        String v1 = "";
        int v0;
        for(v0 = 0; v0 < 16; ++v0) {
            v1 = v1 + MD5.byteHEX(v2[v0]);
        }

        return v1;
    }

    public static byte[] toMD5Byte(InputStream arg1, long arg2) {
        return new MD5().getMD5(arg1, arg2);
    }

    public static byte[] toMD5Byte(String arg2) {
        byte[] v0_1;
        try {
            v0_1 = arg2.getBytes("ISO8859_1");
        }
        catch(UnsupportedEncodingException v0) {
            v0_1 = arg2.getBytes();
        }

        return new MD5().getMD5(v0_1);
    }

    public static byte[] toMD5Byte(byte[] arg1) {
        return new MD5().getMD5(arg1);
    }
}

