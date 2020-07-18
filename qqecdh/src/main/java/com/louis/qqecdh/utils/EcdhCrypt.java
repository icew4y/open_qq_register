package com.louis.qqecdh.utils;



import org.bouncycastle.jce.interfaces.ECPrivateKey;

import java.security.*;
import java.security.spec.ECGenParameterSpec;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import javax.crypto.KeyAgreement;

public class EcdhCrypt {
    public static final String DEFAULT_PUB_KEY = "020b03cf3d99541f29ffec281bebbd4ea211292ac1f53d7128";
    public static final String DEFAULT_SHARE_KEY = "4da0f614fc9f29c2054c77048a6566d7";
    public static final String S_PUB_KEY = "04928D8850673088B343264E0C6BACB8496D697799F37211DEB25BB73906CB089FEA9639B4E0260498B51A992D50813DA8";
    public static final String X509_S_PUB_KEY = "3046301006072A8648CE3D020106052B8104001F03320004928D8850673088B343264E0C6BACB8496D697799F37211DEB25BB73906CB089FEA9639B4E0260498B51A992D50813DA8";
    public static byte[] _c_pri_key;
    public static byte[] _c_pub_key;
    private static byte[] _g_share_key;
    private static boolean initFlg;
    public static PrivateKey pkcs8PrivateKey;
    private static boolean userOpenSSLLib;
    public static PublicKey x509PublicKey;

    static {
        EcdhCrypt.initFlg = false;
        EcdhCrypt.userOpenSSLLib = true;
        EcdhCrypt._c_pub_key = new byte[0];
        EcdhCrypt._c_pri_key = new byte[0];
        EcdhCrypt._g_share_key = new byte[0];
    }


    /**
     * 解码PrivateKey
     * @param key
     * @return
     */
    public static PrivateKey getECPrivateKey(byte[] byteKey) {
        try {
           return KeyFactory.getInstance("EC", "BC").generatePrivate(new PKCS8EncodedKeySpec(byteKey));

        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }


    private byte[] calShareKeyByBouncycastle(byte[] arg7, byte[] pri_key) {
        try {
            String v0_2 = "3046301006072A8648CE3D020106052B8104001F03320004";
            if(arg7.length < 30) {
                v0_2 = "302E301006072A8648CE3D020106052B8104001F031A00";
            }

            PublicKey v0_3 = this.constructX509PublicKey(v0_2 + util.buf_to_string(arg7));

            KeyAgreement v2 = KeyAgreement.getInstance("ECDH", "BC");
            //v2.init(EcdhCrypt.pkcs8PrivateKey);
            v2.init(getECPrivateKey(pri_key));
            v2.doPhase(v0_3, true);
            byte[] v2_1 = v2.generateSecret();
            byte[] v0_4 = MD5.toMD5Byte(v2_1);

            return v0_4;
        }
        catch(ExceptionInInitializerError v0_1) {

            return null;
        }
        catch(Exception v0) {

            return null;
        }
    }



    public byte[] calShareKeyMd5ByPeerPublicKey(byte[] arg4, byte[] pri_key) {
        return this.calShareKeyByBouncycastle(arg4, pri_key);
    }

    private PublicKey constructX509PublicKey(String arg4) throws NoSuchProviderException, NoSuchAlgorithmException, InvalidKeySpecException {
        return KeyFactory.getInstance("EC", "BC").generatePublic(new X509EncodedKeySpec(util.string_to_buf(arg4)));
    }

    public byte[] get_c_pub_key() {
        return (byte[])EcdhCrypt._c_pub_key.clone();
    }

    public byte[] get_g_share_key() {
        return (byte[])EcdhCrypt._g_share_key.clone();
    }
    public byte[] get_g_private_key() {
        return (byte[])EcdhCrypt._c_pri_key.clone();
    }
    public int initShareKey() {
        if(EcdhCrypt.initFlg) {
            return 0;
        }

        EcdhCrypt.initFlg = true;

        if(this.initShareKeyByBouncycastle() == 0) {
            EcdhCrypt.userOpenSSLLib = false;
            return 0;
        }

        return this.initShareKeyByDefault();
    }

    private int initShareKeyByBouncycastle() {
        try {
            KeyPairGenerator v1 = KeyPairGenerator.getInstance("EC", "BC");
            v1.initialize(new ECGenParameterSpec("secp192k1"));
            KeyPair v1_1 = v1.genKeyPair();
            PublicKey v2 = v1_1.getPublic();
            byte[] v3 = v2.getEncoded();
            PrivateKey v1_2 = v1_1.getPrivate();
            v1_2.getEncoded();
            PublicKey v4 = this.constructX509PublicKey("3046301006072A8648CE3D020106052B8104001F03320004928D8850673088B343264E0C6BACB8496D697799F37211DEB25BB73906CB089FEA9639B4E0260498B51A992D50813DA8");
            KeyAgreement v5 = KeyAgreement.getInstance("ECDH", "BC");
            v5.init(v1_2);
            v5.doPhase(v4, true);
            EcdhCrypt._c_pri_key = v1_2.getEncoded();
            EcdhCrypt._g_share_key = MD5.toMD5Byte(v5.generateSecret());
            EcdhCrypt._c_pub_key = new byte[49];
            System.arraycopy(((Object)v3), 23, EcdhCrypt._c_pub_key, 0, 49);
            EcdhCrypt.x509PublicKey = v2;
            EcdhCrypt.pkcs8PrivateKey = v1_2;
            return 0;
        }
        catch(ExceptionInInitializerError v0_1) {
            return -1;
        }
        catch(Exception v0) {
            return -2;
        }
    }

    public int initShareKeyByDefault() {
        EcdhCrypt._c_pub_key = new byte[]{2, 11, 3, -49, 61, -103, 84, 0x1F, 41, -1, -20, 40, 27, -21, -67, 78, -94, 17, 41, 42, (byte)0xC1, -11, 61, 0x71, 40};
        EcdhCrypt._g_share_key = new byte[]{77, (byte)0xA0, -10, 20, -4, -97, 41, -62, 5, 76, 0x77, 4, (byte)0x8A, 101, 102, -41};
        return 0;
    }

    public void set_c_pri_key(byte[] arg2) {
        if(arg2 != null) {
            EcdhCrypt._c_pri_key = (byte[])arg2.clone();
            return;
        }

        EcdhCrypt._c_pri_key = new byte[0];
    }

    public void set_c_pub_key(byte[] arg2) {
        if(arg2 != null) {
            EcdhCrypt._c_pub_key = (byte[])arg2.clone();
            return;
        }

        EcdhCrypt._c_pub_key = new byte[0];
    }

    public void set_g_share_key(byte[] arg2) {
        if(arg2 != null) {
            EcdhCrypt._g_share_key = (byte[])arg2.clone();
            return;
        }

        EcdhCrypt._g_share_key = new byte[0];
    }
}

