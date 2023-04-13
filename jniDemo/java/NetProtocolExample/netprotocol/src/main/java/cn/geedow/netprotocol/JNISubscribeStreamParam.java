package cn.geedow.netprotocol;

import java.io.Serializable;

public class JNISubscribeStreamParam implements Serializable {
    public String account;
    public int streamType;
    public String sdpOffer;

    /// alpha
    public int mediaType;  ///0:audio  1:video
    public String transportId;

    public JNISubscribeStreamParam() {
        account = "";
        streamType = 0;
        sdpOffer = "";
        mediaType = 1;
        transportId = "";
    }
}