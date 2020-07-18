package com.louis.qqecdh.controller;

import com.louis.qqecdh.utils.EcdhCrypt;
import com.louis.qqecdh.utils.util;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.net.URLDecoder;
import java.util.UUID;

@RestController
@RequestMapping("/api")
@Api("组包服务接口")
@Slf4j
public class controller {
    private EcdhCrypt ecdhCrypt = new EcdhCrypt();
    @ApiOperation("调用组包服务")
    @PostMapping("/qqecdh")
    public String qqecdh(@RequestBody String data){
        ecdhCrypt.initShareKey();
        return util.buf_to_string(ecdhCrypt.get_c_pub_key()) + "|" + util.buf_to_string(ecdhCrypt.get_g_share_key()) + "|" + util.buf_to_string(ecdhCrypt.get_g_private_key());
    }

    @ApiOperation("计算sharedkey")
    @PostMapping("/calShareKey")
    public String calShareKey(@RequestBody String data){
        try {
            String d = URLDecoder.decode(data, "utf-8");
            String[] keys = d.split("\\|");
            byte[] shared_key = ecdhCrypt.calShareKeyMd5ByPeerPublicKey(util.string_to_buf(keys[0]), util.string_to_buf(keys[1]));
            return util.buf_to_string(shared_key);
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return "";
    }
}
