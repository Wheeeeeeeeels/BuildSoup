package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIView implements Serializable {
    public String account;
    public String username;
    public int streamType;
    public JNIRect rect;

    public JNIView() {
        account = "";
        username = "";
        streamType = 0;
        rect = new JNIRect();
    }
}
