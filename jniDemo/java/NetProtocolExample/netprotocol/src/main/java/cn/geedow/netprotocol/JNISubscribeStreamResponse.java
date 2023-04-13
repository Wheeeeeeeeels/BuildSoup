package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNISubscribeStreamResponse implements Serializable {
    public String sdp;
    /// transportId 过期，客户端业务 判断code == 
    public int errorCode;

    public String account;
    public int streamType;
    /// alpha
    public int mediaType;  ///0:audio  1:video
    public String transportId;
    

    public JNISubscribeStreamResponse() {
        sdp = "";
        errorCode = -1;
        account = "";
        streamType = 0;
        mediaType = 0;
        transportId = "";
    }
}